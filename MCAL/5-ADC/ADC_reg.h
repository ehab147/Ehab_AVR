#ifndef ADC_REG_H
#define ADC_REG_H



#define ADMUX      	    *((volatile uint8*) 0x27)		/*ADC Multiplixer selection register*/
#define ADMUX_REFS1	    7u                              /*Reference selection bit1*/
#define ADMUX_REFS0	    6u                              /*Reference selection bit0*/
#define ADMUX_ADLAR	    5u                              /*LEFT Adjust result*/
													
#define ADCSRA      	*((volatile uint8*) 0x26)       /*ADC control and status register*/
#define ADCSRA_ADEN		7u                              /*Enable*/
#define ADCSRA_ADSC		6u                              /*start conversion*/
#define ADCSRA_ADATE	5u                              /*auto trigger enable*/
#define ADCSRA_ADIF		4u                              /*interrupt flag (conversion complete flag)*/
#define ADCSRA_ADIE		3u                              /*Interrupt Enable*/
														
#define ADCH			*((volatile uint8*) 0x25)       /*ADC Data High Register*/
#define ADCL			*((volatile uint8*) 0x24)       /*ADC Data LOW Register*/
													
#define ADC     		*((volatile uint16*) 0x24)     

















#endif