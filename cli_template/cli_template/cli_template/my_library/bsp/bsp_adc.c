/*
 * bsp_adc.c
 *
 * Created: 11/6/2021 11:45:22 PM
 *  Author: phuoc
 */ 

#include "bsp_adc.h"

void bsp_adc_init(void)
{
	sbi(DDRB, 0);
	sbi(DDRB, 1);
	sbi(PORTB, 0);
	sbi(PORTB, 1);
	// thanh ghi ADMUX
	ADMUX |= (1<<REFS0); // dien ap: AVCC, ADCL chua 8 bit thap
	// thanh ghi ADCSRA
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(ADPS0); // cho phep ADC, chia 128
}
uint16_t bsp_adc_read(uint8_t channel)
{
	ADMUX &= 0xE0;
	ADMUX |= channel;
	_delay_ms(2);
	ADCSRA |= (1<<ADSC); // cho phep bat dau chuyen doi
	while(ADIF==0);
	ADCSRA |= (1<<ADIF);
	return ADCW;
}
