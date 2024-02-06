#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

typedef enum{
	T0_2Normal=0u,
	T0_2CTC,
	T0_2Fast_PMW,
	T0_2Phase_Correct,
}Timer0_2_WfGenMode_t;

typedef enum{
	T0_2Disconnected_NonPWM=0u,
	T0_2Toggle_NonPWM,
	T0_2Clear_NonPWM,
	T0_2Set_NonPWM,
	T0_2Disconnected_Fast,
	T0_2ClearOnCom_SetOnTop_Fast,
	T0_2SetOnCom_ClearOnTop_Fast,
	T0_2Disconnected_Phase,
	T0_2ClearUpCounting_SetDownCounting_Phase,
	T0_2SetUpCounting_ClearDownCounting_Phase,
}Timer0_2_CompareOutputMode_t;

typedef enum{
	Timer_STOP=0u,
	Timer_SCALER_1,
	Timer_SCALER_8,
	Timer_SCALER_64,
	Timer_SCALER_256,
	Timer_SCALER_1024,
	Timer_SCALLER_EXTERNALl_CLK_FALLING,
	Timer_SCALLER_EXTERNAL_CLK_RISING,
}Timer_ClkSelect_t;


typedef enum{
	T0_Com_Int=0u,
	T0_Ovf_Int,
	T1_IC_Int,
	T1_ComA_Int,
	T1_ComB_Int,
	T1_Ovf_Int,
	T2_Com_Int,
	T2_Ovf_Int,


}Timer_Interrupts_t;

typedef struct{
	Timer0_2_WfGenMode_t  WfGen_mode;
	Timer0_2_CompareOutputMode_t  CompareMode;
	Timer_ClkSelect_t  Clk_Prescalar;

}Timer0_2_cfg_t;



uint8 TIMER0_u8Init(const Timer0_2_cfg_t *Copy_PtrTimer0Cfg);

void TIMER0_vSetPreloadValue(uint8 Copy_u8Val);
void TIMER0_vSetCompareValue(uint16 Copy_u16Val);



uint8 TIMERS_vSetCallBack(Timer_Interrupts_t Copy_IntType, void (*Copy_vPtrCallBackFunc)(void));
uint8 TIMERS_u8IntEnable(Timer_Interrupts_t Copy_IntType);
uint8 TIMERS_u8IntDisable(Timer_Interrupts_t Copy_IntType);

/////////////////////////////////////////////////////////////////Timer 1 Functions /////////////////////////////////////////////

typedef enum
{
	T1_COM_Disconnected_NonPWM=0u,
	T1_COM_Toggle_NonPWM,
	T1_COM_Clear_NonPWM,
	T1_COM_Set_NonPWM,

	T1_COM_Disconnected_FastPWM,
	T1_COM_Toggle_OC1A_M15_FastPWM,
	T1_COM_Clear_OC1A_OC1B_FastPWM,
	T1_COM_Set_OC1A_OC1B_FastPWM,

	T1_COM_Disconnected_PhasePWM,
	T1_COM_Toggle_OC1A_M9_M14_PhasePWM,
	T1_COM_Clear_OC1A_OC1B_UP_PhasePWM,
	T1_COM_Set_OC1A_OC1B_UP_PhasePWM,

}Timer1_COM_Config_t;






typedef enum
{
  M0_Normal=0u,
  M1_PWM_Phase_Correct_8_bit,
  M2_PWM_Phase_Correct_9_bit,
  M3_PWM_Phase_Correct_10_bit,
  M4_CTC,
  M5_Fast_PWM_8_bit,
  M6_Fast_PWM_9_bit,
  M7_Fast_PWM_10_bit,
  M8_PWM_Phase_and_Frequency_Correct,
  M9_PWM_Phase_and_Frequency_Correct,
  M10_PWM_Phase_Correct,
  M11_PWM_Phase_Correct,
  M12_CTC,
  M13_Reserved,
  M14_Fast_PWM,
  M15_Fast_PWM,



}Timer1_WGM_t;


typedef struct
{
	Timer1_WGM_t Mode_WGM_t;
	Timer1_COM_Config_t COM_Mode_t;
	Timer_ClkSelect_t  Clk_Select_t ;

}Timer1_Config_t;


typedef enum
{
	ICU_FALLING_EDGE=0u,
	ICU_RISSING_EDGE=1u,
}TIMER1_ICU_Config_t;

uint8 TIMER1_u8Init(const Timer1_Config_t *Copy_PtrTimer1_cfg);

void TIMER1_vGetTimerReading(uint16*Copy_pu16Val);
void TIMER1_vSetTimerReading(uint16 Copy_pu16Val);
void TIMER1_vSetTopVal(uint16 Copy_u16Val);

void TIMER1_vSetComVal_ChannelA(uint16 Copy_u16Val);

void TIMER1_vSetComVal_ChannelB(uint16 Copy_u16Val);

void TIMER1_vICR(uint16 Copy_u16Val);

uint8 TIMER1_ICU(TIMER1_ICU_Config_t Trigger_Type);

void TIMER1_ICU_GetReading(uint16 * Copy_pu16Value);




/*

uint8 TIMER2_u8Init(const Timer0_2_cfg_t *Timer2_cfg);



uint8 TIMERO u8SetCallBack<Timer0_2_Interrupts_t Copy_Timer_Int, void(*Copy_pvCallBackFunc) (void));
void TIMER1_voidSetTopVal(uint16 Copy_u16Val);
void TIMER1_voidSetComVal(uint16 Copy_u16Val);

uint8 TIMERO_u8SetComNonPWM_Mode(Timer0_2_Com_NonPWM_t Mode);
uint8 TIMER0_u8SetComFastPWM_Mode(Timer0_2_Com_FastPWM_t Mode);
uint8 TIMER0_u8SetComPhaseCorPWM_Mode(Timer0_2_Com_PhaseCorPWM_t Mode);

uint8 TIMER1_u8SetComNonPWM_Mode(Timer1_Com_NonPWM_t Mode);
uint8 TIMER1_u8SetComFastPWM_Mode(Timer1_Com_FastPWM_t Mode);
uint8 TIMER1_u8SetComPhaseCorPWM_Mode(Timer1_Com_PhaseCorPWM_t Mode);

uint8 TIMER1_u8SetCallBack(Timer1_Interrupts_t Copy_Timer_Int, void(*Copy_pvCallBackFunc)(void));

uint8 TIMER2_u8SetComNonPWM_Mode(Timer0_2_Com_NonPWM_t Mode);
uint8 TIMER2_u8SetComFastPWM_Mode(Timer0_2_Com_FastPWM_t Mode);
uint8 TIMER2 u8SetComPhaseCorPWM Mode(Timer0 2 Com PhaseCorPWM t Mode):

void TIMER0
*/



#endif /*TIMER_INTERFACE_H*/
