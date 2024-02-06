#ifndef ADC_CFG_H
#define ADC_CFG_H

/*
configuration the reference volt options
 	 	 	 	 	 	 	 	 	 	 	 	1-AREF
  		     	 	 	 	 	 	 	 	 	2-AVCC
         	 	 	 	 	 	 	 	 	 	3-INTERNAL_2650mv
*/
#define ADC_u8RefVolt   AVCC



/*configuration for Resolution
 * 								1-TEN_BITS
 * 								2-EIGHT_BITS
 * */

#define ADC_u8Resolution  TEN_BITS



/*configuration for interrupt enable
 * 									1-ENABLE
 * 									2-DISABLE
 * */

#define ADC_u8INT_ENABLE  DISABLE



/*configuration for ADC_AutoTriggerMode
 * 									1-ENABLE
 * 									2-DISABLE
 * */
#define ADC_AutoTriggerMode		DISABLE
/*configuration for prescaler clk
 *
 * 						1-DIVISION_BY_2
 *						2-DIVISION_BY_4
 *						3-DIVISION_BY_8
 *						4-DIVISION_BY_16
 *						5-DIVISION_BY_32
 *						6-DIVISION_BY_64
 *						7-DIVISION_BY_128
 *
 * */

#define ADC_u8PRESCALER   DIVISION_BY_128

#define ADC_u32TIMEOUT		50000u

#endif
