/**
 * @file      PY32F002B_EmbedFire_Core_Board.h
 * @author    Ferdinand Clasquin (fclasquin@gmail.com)
 * @brief     This file provides set of firmware functions to manage Leds, 
 *            push-button available on the Core Board.
 * @version   1.0
 * @date      2025-10-16
 * 
 * @copyright Copyright (c) 2025
 * 
 ******************************************************************************
 * @attention EmbedFire
 *
 * <h2><center>&copy; Copyright (c) Dongguan EmbedFire Electronic Technology Co., Ltd
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by Puya under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 ******************************************************************************
 * @attention Puya Semiconductor Co.
 *
 * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by Puya under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 * @attention STMicroelectronics
 *
 * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#ifndef PY32F002B_EmbedFire_Core_Board_H
#define PY32F002B_EmbedFire_Core_Board_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx_hal.h"

/** @addtogroup BSP
  * @{
  */

/** @defgroup py32f002b_EmbedFire_Code_Board
  * @brief This section contains the exported types, contants and functions
  *        required to use the EmbedFire Core Board PY32F002BF15U board.
  * @{
  */

/** @defgroup py32f002b_EmbedFire_Code_Board_Exported_Types Exported Types
  * @{
  */
typedef enum
{
  /* LED 2 GPIO PORT a/b/c GPIO PIN n */
  LED2 = 0,
  /* Alias Name LED_GREEN */
  LED_GREEN = LED2,
  /* LED 3 GPIO PORT a/b/c GPIO PIN n */
  LED3 = 1,
  /* Alias Name LED_ORANGE */
  LED_ORANGE = LED3,
  /* LED 4 GPIO PORT a/b/c GPIO PIN n */
  LED4 = 2,
  /* Alias Name LED_BLUE */
  LED_BLUE = LED4,
  LEDn
}Led_TypeDef;

typedef enum
{
  USER_BUTTON1 = 0,
  /* Alias Name KEY1 as on Board */
  KEY1 = USER_BUTTON1,
  USER_BUTTON2 = 1,
  /* Alias Name KEY2 as on Board */
  KEY2 = USER_BUTTON2,
  USER_BUTTONn 
}Button_TypeDef

typedef enum
{
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
}ButtonMode_TypeDef;

/**
  * @brief PY32F002B EMBEDFIRE BSP Driver version number
  */
#define PY32F002B_EMBEDFIRE_BSP_VERSION_MAIN   (0x01U) /*!< [31:24] main version */
#define PY32F002B_EMBEDFIRE_BSP_VERSION_SUB1   (0x00U) /*!< [23:16] sub1 version */
#define PY32F002B_EMBEDFIRE_BSP_VERSION_SUB2   (0x00U) /*!< [15:8]  sub2 version */
#define PY32F002B_EMBEDFIRE_BSP_VERSION_RC     (0x01U) /*!< [7:0]  release candidate */
#define PY32F002B_EMBEDFIRE_BSP_VERSION        ((PY32F002B_EMBEDFIRE_BSP_VERSION_MAIN << 24)\
                                              |(PY32F002B_EMBEDFIRE_BSP_VERSION_SUB1 << 16)\
                                              |(PY32F002B_EMBEDFIRE_BSP_VERSION_SUB2 << 8 )\
                                              |(PY32F002B_EMBEDFIRE_BSP_VERSION_RC))

/** @defgroup PY32F002B_EMBEDFIRE_LOW_LEVEL_LED LOW LEVEL LED
  * @{
  */
#define LEDn                                    3U

#define LED2_PIN                                GPIO_PIN_1
#define LED2_GPIO_PORT                          GPIOA
#define LED3_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOA_CLK_ENABLE()
#define LED2_GPIO_CLK_DISABLE()                 __HAL_RCC_GPIOA_CLK_DISABLE()

#define LED3_PIN                                GPIO_PIN_2
#define LED3_GPIO_PORT                          GPIOA
#define LED3_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOA_CLK_ENABLE()
#define LED3_GPIO_CLK_DISABLE()                 __HAL_RCC_GPIOA_CLK_DISABLE()

#define LED4_PIN                                GPIO_PIN_3
#define LED4_GPIO_PORT                          GPIOA
#define LED4_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOA_CLK_ENABLE()
#define LED4_GPIO_CLK_DISABLE()                 __HAL_RCC_GPIOA_CLK_DISABLE()

#define LEDx_GPIO_CLK_ENABLE(__INDEX__)         do { if((__INDEX__) == 0) { LED2_GPIO_CLK_ENABLE(); } else if((__INDEX__) == 1) { LED3_GPIO_CLK_ENABLE(); } else { LED4_GPIO_CLK_ENABLE(); } } while(0)
#define LEDx_GPIO_CLK_DISABLE(__INDEX__)        do { if((__INDEX__) == 0) { LED2_GPIO_CLK_DISABLE(); } else if((__INDEX__) == 1) { LED3_GPIO_CLK_DISABLE(); } else { LED4_GPIO_CLK_DISABLE(); } } while(0)

/**
  * @}
  */

/** @defgroup PY32F002B_EMBEDFIRE_LOW_LEVEL_BUTTON LOW LEVEL BUTTON
  * @{
  */
/* Button state */
#define BUTTON_RELEASED                    0U
#define BUTTON_PRESSED                     1U
#define BUTTONn                            2U

/**
 * @brief Key push-button
 */
#define BUTTON_USER1_PIN                       GPIO_PIN_1
#define BUTTON_USER1_GPIO_PORT                 GPIOB
#define BUTTON_USER1_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOC_CLK_ENABLE()
#define BUTTON_USER1_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOC_CLK_DISABLE()
#define BUTTON_USER1_EXTI_IRQn                 EXTI15_10_IRQn
#define BUTTON_USER1_EXTI_LINE                 EXTI_LINE_1

#define BUTTON_USER2_PIN                       GPIO_PIN_2
#define BUTTON_USER2_GPIO_PORT                 GPIOB
#define BUTTON_USER2_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOC_CLK_ENABLE()
#define BUTTON_USER2_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOC_CLK_DISABLE()
#define BUTTON_USER2_EXTI_IRQn                 EXTI15_10_IRQn
#define BUTTON_USER2_EXTI_LINE                 EXTI_LINE_2

/* Button Aliases*/
#define KEY1_PIN                               BUTTON_USER1_PIN
#define KEY1_GPIO_PORT                         BUTTON_USER1_GPIO_PORT
#define KEY1_GPIO_CLK_ENABLE()                 BUTTON_USER1_GPIO_CLK_ENABLE()
#define KEY1_GPIO_CLK_DISABLE()                BUTTON_USER1_GPIO_CLK_DISABLE()
#define KEY1_EXTI_IRQn                         BUTTON_USER1_EXTI_IRQn
#define KEY1_EXTI_LINE                         BUTTON_USER1_EXTI_LINE

#define KEY2_PIN                               BUTTON_USER2_PIN
#define KEY2_GPIO_PORT                         BUTTON_USER2_GPIO_PORT
#define KEY2_GPIO_CLK_ENABLE()                 BUTTON_USER2_GPIO_CLK_ENABLE()
#define KEY2_GPIO_CLK_DISABLE()                BUTTON_USER2_GPIO_CLK_DISABLE()
#define KEY2_EXTI_IRQn                         BUTTON_USER2_EXTI_IRQn
#define KEY2_EXTI_LINE                         BUTTON_USER2_EXTI_LINE

#define BUTTONx_GPIO_CLK_ENABLE(__INDEX__)     do { if((__INDEX__) == 0) { BUTTON_USER1_GPIO_CLK_ENABLE(); } else { BUTTON_USER2_GPIO_CLK_ENABLE(); } } while(0)
#define BUTTONx_GPIO_CLK_DISABLE(__INDEX__)    do { if((__INDEX__) == 0) { BUTTON_USER1_GPIO_CLK_DISABLE(); } else { BUTTON_USER2_GPIO_CLK_DISABLE(); } } while(0)

/**
  * @}
  */

#ifdef HAL_UART_MODULE_ENABLED
/* debug printf redirect config */
#define DEBUG_USART_BAUDRATE                    115200

#define DEBUG_USART                             USART1
#define DEBUG_USART_CLK_ENABLE()                do { \
                                                     __IO uint32_t tmpreg = 0x00U; \
                                                     SET_BIT(RCC->APBENR2, RCC_APBENR2_USART1EN);\
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->APBENR2, RCC_APBENR2_USART1EN);\
                                                     UNUSED(tmpreg); \
                                                   } while(0U)

#define __GPIOB_CLK_ENABLE()                    do { \
                                                     __IO uint32_t tmpreg = 0x00U; \
                                                     SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN);\
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN);\
                                                     UNUSED(tmpreg); \
                                                   } while(0U)

#define DEBUG_USART_RX_GPIO_PORT                GPIOB
#define DEBUG_USART_RX_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOB_CLK_ENABLE()
#define DEBUG_USART_RX_PIN                      GPIO_PIN_5
#define DEBUG_USART_RX_AF                       GPIO_AF1_USART1

#define DEBUG_USART_TX_GPIO_PORT                GPIOB
#define DEBUG_USART_TX_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOB_CLK_ENABLE()
#define DEBUG_USART_TX_PIN                      GPIO_PIN_4
#define DEBUG_USART_TX_AF                       GPIO_AF1_USART1

#define DEBUG_USART_IRQHandler                  USART1_IRQHandler
#define DEBUG_USART_IRQ                         USART1_IRQn

#else

#define DEBUG_USART_TX_GPIO_PORT                GPIOB
#define DEBUG_USART_TX_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOB_CLK_ENABLE()
#define DEBUG_USART_TX_PIN                      GPIO_PIN_4
#endif
/************************************************************/

#ifdef HAL_UART_MODULE_ENABLED
extern UART_HandleTypeDef DebugUartHandle;
#endif

/**
  * @}
  */

/** @defgroup PY32F002B_EMBEDFIRE_LOW_LEVEL_Exported_Functions Prototypes LOW LEVEL
  * @{
  */
int32_t  BSP_GetVersion(void);

void     BSP_LED_Init(Led_TypeDef Led);
void     BSP_LED_DeInit(Led_TypeDef Led);
void     BSP_LED_On(Led_TypeDef Led);
void     BSP_LED_Off(Led_TypeDef Led);
void     BSP_LED_Toggle(Led_TypeDef Led);
int32_t  BSP_LED_GetState (Led_TypeDef Led);

void     BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
void     BSP_PB_DeInit(Button_TypeDef Button);
int32_t  BSP_PB_GetState(Button_TypeDef Button);

void     BSP_PB_IRQHandler(Button_TypeDef Button);
void     BSP_PB_Callback(Button_TypeDef Button);

void     BSP_USART_Config(void);
#define  DEBUG_USART_Config   BSP_USART_Config

/**
  * @}
  */

#ifdef __cplusplus
}
#endif
/** EOF **/