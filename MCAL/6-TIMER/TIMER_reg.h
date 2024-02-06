#ifndef TIMER_REG_H
#define TIMER_REG_H


#define TCCR0   *((volatile uint8*)0x53)

#define TCCR0_CS00	 0u
#define TCCR0_CS01 	 1u
#define TCCR0_CS02	 2u
#define TCCR0_WGM01  3u
#define TCCR0_COM00  4u
#define TCCR0_COM01	 5u
#define TCCR0_WGM00	 6u
#define TCCR0_FOC0	 7u


#define TCNT0   *((volatile uint8*)0x52)

#define OCR0   *((volatile uint8*)0x5C)

#define TIMSK   *((volatile uint8*)0x59)

#define TIMSK_TOIE0    0u
#define TIMSK_OCIE0    1u
#define TIMSK_TOIE1    2u
#define TIMSK_OCIE1B   3u
#define TIMSK_OCIE1A   4u
#define TIMSK_TICIE1   5u
#define TIMSK_TOIE2    6u
#define TIMSK_OCIE2    7u

#define TIFR   *((volatile uint8*)0x58)

#define TIFR_TOV0      0u
#define TIFR_OCF0      1u
#define TIFR_TOV1      2u
#define TIFR_OCF1B     3u
#define TIFR_OCF1A     4u
#define TIFR_ICF1      5u
#define TIFR_TOV2      6u
#define TIFR_OCF2      7u



/***************************************Timer 1 **************************************************/


#define ICR1      	(*(volatile unsigned short*)0x46)
#define ICR1L     	(*(volatile unsigned char*)0x46)
#define ICR1H     	(*(volatile unsigned char*)0x47)

#define OCR1B     	(*(volatile unsigned short*)0x48)
#define OCR1BL    	(*(volatile unsigned char*)0x48)
#define OCR1BH      (*(volatile unsigned char*)0x49)

#define OCR1A     	(*(volatile unsigned short*)0x4A)
#define OCR1AL    	(*(volatile unsigned char*)0x4A)
#define OCR1AH      (*(volatile unsigned char*)0x4B)

#define TCNT1       (*(volatile unsigned short*)0x4C)
#define TCNT1L    	(*(volatile unsigned char*)0x4C)
#define TCNT1H    	(*(volatile unsigned char*)0x4D)

#define TCCR1B      (*(volatile unsigned char*)0x4E)
#define TCCR1B_CS10   0u
#define TCCR1B_CS11   1u
#define TCCR1B_CS12   2u
#define TCCR1B_WGM12  3u
#define TCCR1B_WGM13  4u
#define TCCR1B_ICES1  6u
#define TCCR1B_CNC1   7u

#define TCCR1A      (*(volatile unsigned char*)0x4F)
#define TCCR1A_WGM10   0u
#define TCCR1A_WGM11   1u
#define TCCR1A_FOC1B   2u
#define TCCR1A_FOC1A   3u
#define TCCR1A_COM1B0  4u
#define TCCR1A_COM1B1  5u
#define TCCR1A_COM1A0  6u
#define TCCR1A_COM1A1  7u



#endif /*TIMER_REG_H*/
