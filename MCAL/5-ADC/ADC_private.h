#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H


#define AREF 			    1u
#define AVCC 		        2u
#define INTERNAL_2650mv     3u

#define TEN_BITS    	    1u
#define EIGHT_BITS		    2u

#define ENABLE 	            1u
#define DISABLE	 		    2u

#define DIVISION_BY_2       1u
#define DIVISION_BY_4       2u
#define DIVISION_BY_8       3u
#define DIVISION_BY_16      4u
#define DIVISION_BY_32      5u
#define DIVISION_BY_64      6u
#define DIVISION_BY_128     7u

#define PRESCALER_BIT_MASK  0b11111000

#define PRESCALER_BIT_POS   0u

#define Channel_BIT_MASK    0b11100000

#define IDLE				0u
#define BUSY				1u










#endif
