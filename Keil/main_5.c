#include <LPC213x.h>

#define ADC_WR    (1 << 6)    // P0.6
#define MOTOR     (1 << 7)    // P0.7
#define ADC_RD    (1 << 8)    // P0.8
#define ADC_INTR  (1 << 9)    // P0.9
#define BUZZER    (1 << 10)   // P0.10

#define OVERLOAD_THRESHOLD 150


void delay_ms(unsigned int ms)
{
    unsigned int i, j;

    for(i = 0; i < ms; i++)
        for(j = 0; j < 6000; j++);
}


/* ================= UART0 ================= */

void UART0_Init(void)
{
    PINSEL0 &= ~0x0000000F;
    PINSEL0 |=  0x00000005;

    VPBDIV = 0x01;        // PCLK = 12 MHz

    U0LCR = 0x83;

    U0DLL = 78;           // 9600 baud
    U0DLM = 0;

    U0LCR = 0x03;
}


void UART0_SendChar(char ch)
{
    while(!(U0LSR & 0x20));

    U0THR = ch;
}


void UART0_SendString(char *str)
{
    while(*str)
    {
        UART0_SendChar(*str);
        str++;
    }
}


void UART0_SendNumber(unsigned int num)
{
    if(num >= 100)
    {
        UART0_SendChar((num / 100) + '0');

        num = num % 100;

        UART0_SendChar((num / 10) + '0');
        UART0_SendChar((num % 10) + '0');
    }
    else if(num >= 10)
    {
        UART0_SendChar((num / 10) + '0');
        UART0_SendChar((num % 10) + '0');
    }
    else
    {
        UART0_SendChar(num + '0');
    }
}


/* ================= ADC0804 ================= */

void ADC0804_Init(void)
{
    /* WR and RD as outputs */
    IO0DIR |= ADC_WR | ADC_RD;

    /* INTR as input */
    IO0DIR &= ~ADC_INTR;

    /* P1.16 - P1.23 as input */
    IO1DIR &= ~(0xFF << 16);

    /* WR and RD initially HIGH */
    IO0SET = ADC_WR | ADC_RD;
}


unsigned char ADC0804_Read(void)
{
    unsigned int value;

    /* Start conversion */
    IO0CLR = ADC_WR;
    delay_ms(1);
    IO0SET = ADC_WR;

    /* Wait for conversion complete */
    while(IO0PIN & ADC_INTR);

    /* Enable data output */
    IO0CLR = ADC_RD;

    delay_ms(1);

    /* Read ADC data */
    value = (IO1PIN >> 16) & 0xFF;

    /* Disable data output */
    IO0SET = ADC_RD;

    return (unsigned char)value;
}

unsigned int ADC_To_Load(unsigned char adc)
{
    unsigned int load;

    load = ((unsigned long)adc * 1000) / 255;

    return load;
}


/* ================= MOTOR + BUZZER ================= */

void Output_Init(void)
{
    IO0DIR |= MOTOR | BUZZER;

    /* Initially motor OFF, buzzer OFF */
    IO0CLR = MOTOR | BUZZER;
}


int main(void)
{
    unsigned char load_value;
		unsigned int load_kg;

    UART0_Init();
    ADC0804_Init();
    Output_Init();
	

    UART0_SendString("\r\n");
    UART0_SendString("LIFT OVERLOAD DETECTOR\r\n");

    while(1)
    {
        load_value = ADC0804_Read();

				load_kg = ADC_To_Load(load_value);

				UART0_SendString("Lift Load = ");
				UART0_SendNumber(load_kg);
				UART0_SendString(" kg");

        if(load_kg >= 600)
				{
						IO0CLR = MOTOR;
						IO0SET = BUZZER;

						UART0_SendString(" -> OVERLOAD!\r\n");
				}
				else
				{
						IO0SET = MOTOR;
						IO0CLR = BUZZER;

						UART0_SendString(" -> NORMAL\r\n");
				}
        delay_ms(100);
    }
}