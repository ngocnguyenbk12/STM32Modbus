#include "main.h"
#include "stm32f407xx.h"


#define AC_ONOFF_STATE_ADDR     5000
#define AC_TEMP_VALUE_ADDR      35000

#define GPIO_0_ADDR             5002
#define GPIO_1_ADDR             5003
#define GPIO_2_ADDR             5004
#define GPIO_3_ADDR             5005
#define GPIO_4_ADDR             5006

#define GPIO_0_PIN             GPIO_PIN_10
#define GPIO_1_PIN             GPIO_PIN_9
#define GPIO_2_PIN             GPIO_PIN_8
#define GPIO_3_PIN             GPIO_PIN_7
#define GPIO_4_PIN             GPIO_PIN_6

#define GPIO_PORT               GPIOA

