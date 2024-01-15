#ifndef EXTI_reg_H
#define EXTI_reg_H



#define GICR 		 *((volatile uint8 *)0x5B)  /*General interrupt control register */
#define GICR_INT1  	 7u
#define GICR_INT0  	 6u
#define GICR_INT2  	 5u


#define MCUCR	 	  *((volatile uint8 *)0x55)	 /*MCU control register */

#define MCUCR_ISC00   0u                         /*Int0 sense control bit0*/
#define MCUCR_ISC01   1u                         /*Int0 sense control bit1*/
#define MCUCR_ISC10   2u                         /*Int1 sense control bit0*/
#define MCUCR_ISC11   3u                         /*Int1 sense control bit1*/


#define MCUCSR  		*((volatile uint8 *)0x54)   /*MCU Control and status register */
#define MCUCSR_ISC2		6u							/*Int2 sense control bit */



#endif /*EXTI_reg_H*/
