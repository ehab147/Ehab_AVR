#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#include "STD_TYPES.h"


void ADC_INIT(void);


uint8 ADC_u8StartConversionSync(uint8 Copy_u8Channel,uint16*Copy_pu16Result);



uint8 ADC_u8StartConversionASync(uint8 Copy_u8Channel,uint16*Copy_pu16Result,void(*Copy_pvNotificationFunction)(void));














#endif
