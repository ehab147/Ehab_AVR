
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "ADC_interface.h"
#include "ADC_reg.h"
#include "ADC_private.h"
#include "ADC_cfg.h"




static uint16* ADC_pu16Result= NULL;

static void (*ADC_pvCallBackNotificationFunc)(void)= NULL;

static uint8 ADC_u8BusyFlag = IDLE ;


void ADC_INIT(void)
{
	/*SSet Reference voltage*/
#if ADC_u8RefVolt == AREF
	CLR_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif ADC_u8RefVolt == AVCC

	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif ADC_u8RefVolt ==  INTERNAL_2650mv

	SET_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);
#else
#error Wrong ADC_u8RefVolt configuration

#endif

	/*Set ADC resolution*/
#if ADC_u8Resolution == EIGHT_BITS
	SET_BIT(ADMUX,ADMUX_ADLAR);
#elif ADC_u8Resolution == TEN_BITS

	CLR_BIT(ADMUX,ADMUX_ADLAR);
#else
#error Wrong ADC_u8Resolution configuration
#endif

	/*Auto Trigger Mode*/
#if ADC_AutoTriggerMode == ENABLE
	SET_BIT(ADCSRA,ADCSRA_ADATE);
#elif ADC_AutoTriggerMode == DISABLE
	CLR_BIT(ADCSRA,ADCSRA_ADATE);
#else
#error Wrong ADC_AutoTriggerMode configuration
#endif


	/*Interrupt Enable*/
#if ADC_u8INT_ENABLE == ENABLE
	SET_BIT(ADCSRA,ADCSRA_ADIE);

#elif ADC_u8INT_ENABLE == DISABLE
	CLR_BIT(ADCSRA,ADCSRA_ADIE);

#else
#error Wrong ADC_u8INT_ENABLE configuration
#endif

	/*assign Prescaler value*/
	ADCSRA &= PRESCALER_BIT_MASK;  //0b11111000

	ADCSRA |= (ADC_u8PRESCALER << PRESCALER_BIT_POS);

	/*Enable ADC*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);

}





uint8 ADC_u8StartConversionSync(uint8 Copy_u8Channel,uint16*Copy_pu16Result)
{
	uint8 Local_u8ErrorState=OK;

	uint32 Local_u32Counter=0u;


	if(Copy_pu16Result!=NULL)
	{
		/*check if ADC is IDLE*/
		if(ADC_u8BusyFlag == IDLE)
		{
			/*ADC is now Busy*/
			ADC_u8BusyFlag = BUSY ;

			/*set the input channel*/
			ADMUX &= Channel_BIT_MASK; /*clear the channel selection bits*/
			ADMUX |= Copy_u8Channel;

		/*	Start Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);


			/*polling on flag (with blocking) on condition that timerout is not passed yet*/
			while((GET_BIT(ADCSRA,ADCSRA_ADIF)==0u) && (Local_u32Counter < ADC_u32TIMEOUT))
			{
				Local_u32Counter++;
			}

			if(Local_u32Counter == ADC_u32TIMEOUT)
			{
				/*TimeOut has passed without the flag being raised*/
				Local_u8ErrorState=TIMEOUT_ERR;
			}
			else
			{
				/*Flag is raised before timeout*/
				/*put Flag to 1 again*/
				SET_BIT(ADCSRA,ADCSRA_ADIF);

#if ADC_u8Resolution == EIGHT_BITS
				*Copy_pu16Result= ADCH;
#elif ADC_u8Resolution == TEN_BITS
				*Copy_pu16Result= ADC;
#endif


			}

			/*ADC is now IDLE*/
			ADC_u8BusyFlag=IDLE;

		}
		else
		{
			/*ADC is busy ,update error state*/
			Local_u8ErrorState = BUSY_ERR ;
		}

	}
	else
	{
		Local_u8ErrorState=NULL_PTR_ERR ;
	}


	return Local_u8ErrorState;
}





uint8 ADC_u8StartConversionASync(uint8 Copy_u8Channel,uint16*Copy_pu16Result, void(*Copy_pvNotificationFunction)(void) )
{
	uint8 Local_u8ErrorState=OK;

	if( (Copy_pu16Result != NULL) && (Copy_pvNotificationFunction != NULL) )
	{
		/*check if ADC is IDLE*/
		if(ADC_u8BusyFlag == IDLE)
		{
			ADC_u8BusyFlag=BUSY;

			/*Convert the local adc result into global*/
			ADC_pu16Result=Copy_pu16Result;
			/*Convert the local adc call back into global*/
			ADC_pvCallBackNotificationFunc=Copy_pvNotificationFunction;

			/*set the input channel*/
			ADMUX &= Channel_BIT_MASK; /*clear the channel selection bits*/
			ADMUX |= Copy_u8Channel;

			/*Start Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Enable ADC conversion complete interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			Local_u8ErrorState= BUSY_ERR;
		}



	}
	else
	{
		Local_u8ErrorState =NULL_PTR_ERR;
	}


	return Local_u8ErrorState ;

}






/*ADC conversion complete ISR*/

 __attribute__((signal)) void __vector_16(void);

void __vector_16(void)
{
	/*Read the result*/
#if ADC_u8Resolution == EIGHT_BITS
	*ADC_pu16Result= ADCH;
#elif ADC_u8Resolution == TEN_BITS
	*ADC_pu16Result= ADC;
#endif

	/*Disable Conversion complete interrupt*/
	CLR_BIT(ADCSRA,ADCSRA_ADIE);

	/*ADC is now idle*/
	ADC_u8BusyFlag=IDLE;

	/*Invoke the call back notification function*/
	if(ADC_pvCallBackNotificationFunc != NULL)
	{
		ADC_pvCallBackNotificationFunc();

	}
	else
	{
		/*Do nothing*/
	}


}







