#include<avr/io.h>
#define F_CPU 8000000
#include<util/delay.h>
#include<lcdavr.h>
#include<stdio.h>

void adc_init()
{
	ADMUX = 0B01000000;//for vcc +5v aNd vref =5v| ADC0 is selected for displaying
	ADCSRA = ((1<<ADEN) | (1<<ADPS2)| (1<<ADPS1)| (1<<ADPS0));
	}
unsigned int adc_read(unsigned char channel)
{	
	
	
	ADCSRA |= (1<<ADSC);//for starting the conversion
	while(!(ADCSRA & (1<<ADIF)));//for progress report //for converting the data

	ADCSRA |= (1<<ADIF);//for updating the data the data and previous task is done
	return ADC;
}

int main()
{

	unsigned char i[5];
	unsigned int value;
	DDRB = 0XFF;
	DDRC=0xff;
	lcd_init();
	adc_init();
while(1)
{
    value=adc_read(0);//0th pin is used 0f adc channel
	lcd_clear();
	lcd_command(0x80);
	sprintf(i,"%d",value);//convrets adc value to i's data type
	lcd_string("adc value:     ");
	lcd_command(0x8b);
	lcd_string(i);
	lcd_command(0x8e);
	lcd_string("mv");
	_delay_ms(100);
	if((value>=0)&&(value<=56))
	{
	   PORTC=(1<<PC1);
	   }

     else if((value>=199)&&(value<=308))
		{
		      PORTC=(1<<PC0);
			  }

			  else
			  {
			         PORTC=0x00;
					 }

}
	return 0;
}

