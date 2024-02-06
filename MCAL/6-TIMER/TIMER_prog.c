#include"STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "TIMER_interface.h"
#include "TIMER_privat.h"
#include "TIMER_cfg.h"
#include "TIMER_reg.h"


static void (*TIMER0_2_ptrFunc[2])(void)={NULL};

static void (*TIMER1_PtrFunc[4])(void)={NULL};



uint8 TIMER0_u8Init(const Timer0_2_cfg_t *Copy_PtrTimer0Cfg)
{
	uint8 Local_u8ErrorState=OK;

	/*Check On Ptr*/

	if(Copy_PtrTimer0Cfg!=NULL)
	{
		switch(Copy_PtrTimer0Cfg->WfGen_mode)
		{
		case T0_2Normal: CLR_BIT(TCCR0,TCCR0_WGM00);CLR_BIT(TCCR0,TCCR0_WGM01);break;
		case T0_2Phase_Correct: SET_BIT(TCCR0,TCCR0_WGM00);CLR_BIT(TCCR0,TCCR0_WGM01);break;
		case T0_2CTC: CLR_BIT(TCCR0,TCCR0_WGM00);SET_BIT(TCCR0,TCCR0_WGM01);break;
		case T0_2Fast_PMW: SET_BIT(TCCR0,TCCR0_WGM00);SET_BIT(TCCR0,TCCR0_WGM01);break;
		default: Local_u8ErrorState=NOK;break;
		}

		switch(Copy_PtrTimer0Cfg->CompareMode)
		{
		case T0_2Disconnected_NonPWM: CLR_BIT(TCCR0,TCCR0_COM00);CLR_BIT(TCCR0,TCCR0_COM01);break;
		case T0_2Toggle_NonPWM: SET_BIT(TCCR0,TCCR0_COM00);CLR_BIT(TCCR0,TCCR0_COM01);break;
		case T0_2Clear_NonPWM: CLR_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break;
		case T0_2Set_NonPWM: SET_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break;

		case T0_2Disconnected_Fast: CLR_BIT(TCCR0,TCCR0_COM00);CLR_BIT(TCCR0,TCCR0_COM01);break;
		case T0_2ClearOnCom_SetOnTop_Fast: CLR_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break;
		case T0_2SetOnCom_ClearOnTop_Fast: SET_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break;

		case T0_2Disconnected_Phase: CLR_BIT(TCCR0,TCCR0_COM00);CLR_BIT(TCCR0,TCCR0_COM01);break;
		case T0_2ClearUpCounting_SetDownCounting_Phase: CLR_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break;
		case T0_2SetUpCounting_ClearDownCounting_Phase: SET_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);break;

		default: Local_u8ErrorState=NOK;break;
		}

		if((((Copy_PtrTimer0Cfg->Clk_Prescalar)>=Timer_STOP) && ((Copy_PtrTimer0Cfg->Clk_Prescalar)<=Timer_SCALLER_EXTERNAL_CLK_RISING)))
		{
			/*Assign Value into register */
			TCCR0 &= 0xF8 ; TCCR0 |= Copy_PtrTimer0Cfg->Clk_Prescalar;
		}
		else
		{
			/*Error*/
			Local_u8ErrorState=NOK;
		}

	}
	else
	{

		Local_u8ErrorState=NULL_PTR_ERR;
	}




	return Local_u8ErrorState;



}

void TIMER0_vSetPreloadValue(uint8 Copy_u8Val)
{
	TCNT0 = Copy_u8Val;
}
void TIMER0_vSetCompareValue(uint16 Copy_u16Val)
{
	OCR0 = Copy_u16Val;
}



uint8 TIMERS_vSetCallBack(Timer_Interrupts_t Copy_IntType, void (*Copy_vPtrCallBackFunc)(void))
{
	uint8 Local_u8ErrorState=OK;
	if(Copy_vPtrCallBackFunc!=NULL)
	{
		switch(Copy_IntType)
		{
		case T0_Com_Int : TIMER0_2_ptrFunc[1]=Copy_vPtrCallBackFunc; break;
		case T0_Ovf_Int : TIMER0_2_ptrFunc[0]=Copy_vPtrCallBackFunc; break;
		case T1_IC_Int  : TIMER1_PtrFunc[0]=Copy_vPtrCallBackFunc; break;
		case T1_ComA_Int: TIMER1_PtrFunc[1]=Copy_vPtrCallBackFunc; break;
		case T1_ComB_Int: TIMER1_PtrFunc[2]=Copy_vPtrCallBackFunc; break;
		case T1_Ovf_Int : TIMER1_PtrFunc[3]=Copy_vPtrCallBackFunc; break;
		case T2_Com_Int : TIMER0_2_ptrFunc[1]=Copy_vPtrCallBackFunc; break;
		case T2_Ovf_Int : TIMER0_2_ptrFunc[0]=Copy_vPtrCallBackFunc; break;

		default:Local_u8ErrorState=NOK;

		}

	}
	else
	{
		Local_u8ErrorState=NULL_PTR_ERR;
	}

	return Local_u8ErrorState;

}

uint8 TIMERS_u8IntEnable(Timer_Interrupts_t Copy_IntType)
{
	uint8 Local_u8ErrorState=OK;


	switch(Copy_IntType)
	{
	case T0_Com_Int : SET_BIT(TIMSK,TIMSK_OCIE0) ;break;
	case T0_Ovf_Int : SET_BIT(TIMSK,TIMSK_TOIE0) ;break;

	case T1_IC_Int  : SET_BIT(TIMSK,TIMSK_TICIE1) ;break;
	case T1_ComA_Int: SET_BIT(TIMSK,TIMSK_OCIE1A) ;break;
	case T1_ComB_Int: SET_BIT(TIMSK,TIMSK_OCIE1B);break;
	case T1_Ovf_Int : SET_BIT(TIMSK,TIMSK_TOIE1) ;break;

	case T2_Com_Int : SET_BIT(TIMSK,TIMSK_TOIE2) ;break;
	case T2_Ovf_Int : SET_BIT(TIMSK,TIMSK_TOIE2) ;break;
	default : Local_u8ErrorState=NOK;

	}

	return Local_u8ErrorState;
}


uint8 TIMERS_u8IntDisable(Timer_Interrupts_t Copy_IntType)
{
	uint8 Local_u8ErrorState=OK;


	switch(Copy_IntType)
	{
	case T0_Com_Int : CLR_BIT(TIMSK,TIMSK_TOIE0) ;break;
	case T0_Ovf_Int : CLR_BIT(TIMSK,TIMSK_OCIE0) ;break;

	case T1_IC_Int  : CLR_BIT(TIMSK,TIMSK_TICIE1) ;break;
	case T1_ComA_Int: CLR_BIT(TIMSK,TIMSK_OCIE1A) ;break;
	case T1_ComB_Int: CLR_BIT(TIMSK,TIMSK_OCIE1B);break;
	case T1_Ovf_Int : CLR_BIT(TIMSK,TIMSK_TOIE1) ;break;

	case T2_Com_Int : CLR_BIT(TIMSK,TIMSK_TOIE2) ;break;
	case T2_Ovf_Int : CLR_BIT(TIMSK,TIMSK_TOIE2) ;break;

	default : Local_u8ErrorState=NOK;

	}

	return Local_u8ErrorState;
}


void TIMER1_vGetTimerReading(uint16*Copy_pu16Val)
{

	*Copy_pu16Val=TCNT1;
}

void TIMER1_vSetTimerReading(uint16 Copy_u16Val)
{
	TCNT1=Copy_u16Val;
}




uint8 TIMER1_u8Init(const Timer1_Config_t *Copy_PtrTimer1_cfg)
{

	uint8 Local_u8ErrorState=OK;

	/*Check On Ptr*/

	if(Copy_PtrTimer1_cfg!=NULL)
	{
		switch(Copy_PtrTimer1_cfg->Mode_WGM_t)
		{
		case M0_Normal: 						 CLR_BIT(TCCR1B,TCCR1B_WGM13);CLR_BIT(TCCR1B,TCCR1B_WGM12);CLR_BIT(TCCR1A,TCCR1A_WGM11);CLR_BIT(TCCR1A,TCCR1A_WGM10);break;
		case M1_PWM_Phase_Correct_8_bit:         CLR_BIT(TCCR1B,TCCR1B_WGM13);CLR_BIT(TCCR1B,TCCR1B_WGM12);CLR_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1A,TCCR1A_WGM10);break;
		case M2_PWM_Phase_Correct_9_bit:         CLR_BIT(TCCR1B,TCCR1B_WGM13);CLR_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1A,TCCR1A_WGM11);CLR_BIT(TCCR1A,TCCR1A_WGM10);break;
		case M3_PWM_Phase_Correct_10_bit:        CLR_BIT(TCCR1B,TCCR1B_WGM13);CLR_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1A,TCCR1A_WGM10);break;
		case M4_CTC:						     CLR_BIT(TCCR1B,TCCR1B_WGM13);SET_BIT(TCCR1B,TCCR1B_WGM12);CLR_BIT(TCCR1A,TCCR1A_WGM11);CLR_BIT(TCCR1A,TCCR1A_WGM10);break;
		case M5_Fast_PWM_8_bit:			    	 CLR_BIT(TCCR1B,TCCR1B_WGM13);SET_BIT(TCCR1B,TCCR1B_WGM12);CLR_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1A,TCCR1A_WGM10);break;
		case M6_Fast_PWM_9_bit: 				 CLR_BIT(TCCR1B,TCCR1B_WGM13);SET_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1A,TCCR1A_WGM11);CLR_BIT(TCCR1A,TCCR1A_WGM10);break;
		case M7_Fast_PWM_10_bit: 				 CLR_BIT(TCCR1B,TCCR1B_WGM13);SET_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1A,TCCR1A_WGM10);break;
		case M8_PWM_Phase_and_Frequency_Correct: SET_BIT(TCCR1B,TCCR1B_WGM13);CLR_BIT(TCCR1B,TCCR1B_WGM12);CLR_BIT(TCCR1A,TCCR1A_WGM11);CLR_BIT(TCCR1A,TCCR1A_WGM10);break;
		case M9_PWM_Phase_and_Frequency_Correct: SET_BIT(TCCR1B,TCCR1B_WGM13);CLR_BIT(TCCR1B,TCCR1B_WGM12);CLR_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1A,TCCR1A_WGM10);break;
		case M10_PWM_Phase_Correct:   			 SET_BIT(TCCR1B,TCCR1B_WGM13);CLR_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1A,TCCR1A_WGM11);CLR_BIT(TCCR1A,TCCR1A_WGM10);break;
		case M11_PWM_Phase_Correct:				 SET_BIT(TCCR1B,TCCR1B_WGM13);CLR_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1A,TCCR1A_WGM10);break;
		case M12_CTC:							 SET_BIT(TCCR1B,TCCR1B_WGM13);SET_BIT(TCCR1B,TCCR1B_WGM12);CLR_BIT(TCCR1A,TCCR1A_WGM11);CLR_BIT(TCCR1A,TCCR1A_WGM10);break;
		case M14_Fast_PWM:						 SET_BIT(TCCR1B,TCCR1B_WGM13);SET_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1A,TCCR1A_WGM11);CLR_BIT(TCCR1A,TCCR1A_WGM10);break;
		case M15_Fast_PWM:						 SET_BIT(TCCR1B,TCCR1B_WGM13);SET_BIT(TCCR1B,TCCR1B_WGM12);SET_BIT(TCCR1A,TCCR1A_WGM11);SET_BIT(TCCR1A,TCCR1A_WGM10);break;

		default: Local_u8ErrorState=NOK;break;
		}

		switch(Copy_PtrTimer1_cfg->COM_Mode_t)
		{
		case T1_COM_Disconnected_NonPWM:      	    CLR_BIT(TCCR1A,TCCR1A_COM1A1);CLR_BIT(TCCR1A,TCCR1A_COM1B0);break;
		case T1_COM_Toggle_NonPWM:                	CLR_BIT(TCCR1A,TCCR1A_COM1A1);SET_BIT(TCCR1A,TCCR1A_COM1B0);break;
		case T1_COM_Clear_NonPWM:                 	SET_BIT(TCCR1A,TCCR1A_COM1A1);CLR_BIT(TCCR1A,TCCR1A_COM1B0);break;
		case T1_COM_Set_NonPWM:                   	SET_BIT(TCCR1A,TCCR1A_COM1A1);SET_BIT(TCCR1A,TCCR1A_COM1B0);break;
		case T1_COM_Disconnected_FastPWM:         	CLR_BIT(TCCR1A,TCCR1A_COM1A1);CLR_BIT(TCCR1A,TCCR1A_COM1B0);break;
		case T1_COM_Toggle_OC1A_M15_FastPWM:      	CLR_BIT(TCCR1A,TCCR1A_COM1A1);SET_BIT(TCCR1A,TCCR1A_COM1B0);break;
		case T1_COM_Clear_OC1A_OC1B_FastPWM:      	SET_BIT(TCCR1A,TCCR1A_COM1A1);CLR_BIT(TCCR1A,TCCR1A_COM1B0);break;
		case T1_COM_Set_OC1A_OC1B_FastPWM:          SET_BIT(TCCR1A,TCCR1A_COM1A1);SET_BIT(TCCR1A,TCCR1A_COM1B0);break;
        case T1_COM_Disconnected_PhasePWM:          CLR_BIT(TCCR1A,TCCR1A_COM1A1);CLR_BIT(TCCR1A,TCCR1A_COM1B0);break;
		case T1_COM_Toggle_OC1A_M9_M14_PhasePWM:    CLR_BIT(TCCR1A,TCCR1A_COM1A1);SET_BIT(TCCR1A,TCCR1A_COM1B0);break;
		case T1_COM_Clear_OC1A_OC1B_UP_PhasePWM:    SET_BIT(TCCR1A,TCCR1A_COM1A1);CLR_BIT(TCCR1A,TCCR1A_COM1B0);break;
		case T1_COM_Set_OC1A_OC1B_UP_PhasePWM:      SET_BIT(TCCR1A,TCCR1A_COM1A1);SET_BIT(TCCR1A,TCCR1A_COM1B0);break;

		default: Local_u8ErrorState=NOK;break;
		}

		if((((Copy_PtrTimer1_cfg->Clk_Select_t)>=Timer_STOP) && ((Copy_PtrTimer1_cfg->Clk_Select_t)<=Timer_SCALLER_EXTERNAL_CLK_RISING)))
		{
			/*Assign Value into register */
			TCCR1B &= 0xF8 ; TCCR1B |= Copy_PtrTimer1_cfg->Clk_Select_t;
		}
		else
		{
			/*Error*/
			Local_u8ErrorState=NOK;
		}

	}
	else
	{

		Local_u8ErrorState=NULL_PTR_ERR;
	}

	return Local_u8ErrorState;

}


void TIMER1_vSetTopVal(uint16 Copy_u16Val)
{
	TCNT1= Copy_u16Val;
}

void TIMER1_vSetComVal_ChannelA(uint16 Copy_u16Val)
{
	OCR1A=Copy_u16Val;

}

void TIMER1_vSetComVal_ChannelB(uint16 Copy_u16Val)
{
	OCR1B=Copy_u16Val;
}

void TIMER1_vICR(uint16 Copy_u16Val)
{
	ICR1=Copy_u16Val;
}

uint8 TIMER1_ICU(TIMER1_ICU_Config_t Trigger_Type)
{
	uint8 Local_u8ErrorState=OK;
	/*activate noise cancellation */
	SET_BIT(TCCR1B,TCCR1B_CNC1);

	switch(Trigger_Type)
	{
	case ICU_FALLING_EDGE: CLR_BIT(TCCR1B,TCCR1B_ICES1);  break;
	case ICU_RISSING_EDGE: SET_BIT(TCCR1B,TCCR1B_ICES1);  break;
	default:Local_u8ErrorState=NOK;break;
	}

	return Local_u8ErrorState;
}



void TIMER1_ICU_GetReading(uint16 * Copy_pu16Value)
{
	*Copy_pu16Value=ICR1;
}



/*ISR FOr Timer0 Ovf*/
__attribute__((signal)) void __vector_11(void);
void __vector_11(void)
{
	if(TIMER0_2_ptrFunc[0]!=NULL)
	{
		TIMER0_2_ptrFunc[0]();
	}
	else
	{

	}

}


/*ISR FOr Timer0 COM*/
__attribute__((signal)) void __vector_10(void);
void __vector_10(void)
{
	if(TIMER0_2_ptrFunc[1]!=NULL)
	{
		TIMER0_2_ptrFunc[1]();
	}
	else
	{

	}

}

/*ISR FOr Timer1 ICU*/

__attribute__((signal)) void __vector_6(void);
void __vector_6(void)
{
	if(TIMER1_PtrFunc[0]!=NULL)
	{
		TIMER1_PtrFunc[0]();
	}
	else
	{

	}

}


/*ISR FOr Timer1 OVF*/

__attribute__((signal)) void __vector_8(void);
void __vector_8(void)
{
	if(TIMER1_PtrFunc[3]!=NULL)
	{
		TIMER1_PtrFunc[3]();
	}
	else
	{

	}

}
