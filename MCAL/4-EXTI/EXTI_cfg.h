#ifndef EXTI_CFG_H
#define EXTI_CFG_H

/*Configure the Sense CTRl Option for INT0 Channel , Options :
 * 																1-EXTI_LOW_LEVEL
 * 																2-EXTI_ON_CHANGE
 * 																3-EXTI_FALLING_EDGE
 * 																4-EXTI_RISING_EDGE
 * */
#define INT0_SENSE_CTRL			EXTI_FALLING_EDGE

/*Configure the Sense CTRl Option for INT0 Channel , Options :
 * 																1-EXTI_LOW_LEVEL
 * 																2-EXTI_ON_CHANGE
 * 																3-EXTI_FALLING_EDGE
 * 																4-EXTI_RISING_EDGE
 * */
#define INT1_SENSE_CTRL			EXTI_FALLING_EDGE



/*Configure the Sense CTRl Option for INT0 Channel , Options :
 *
 * 																1-EXTI_FALLING_EDGE
 * 																2-EXTI_RISSING_EDGE
 * */
#define INT2_SENSE_CTRL			EXTI_FALLING_EDGE



/*Configure the initial state of INT0 Channel , options are :
 * 																1-ENABLED
 * 																2-DISABLED

 * */
#define INT0_INIT_STATE 		ENABLED

/*Configure the initial state of INT1 Channel , options are :
 * 																1-ENABLED
 * 																2-DISABLED

 * */
#define INT1_INIT_STATE 		ENABLED

/*Configure the initial state of INT2 Channel , options are :
 * 																1-ENABLED
 * 																2-DISABLED

 * */
#define INT2_INIT_STATE 		DISABLED










#endif /*EXTI_CFG_H*/
