/**
 * @file      PY32F002B_EmdedFire_Core_Board.c
 * @author    Ferdinand Clasquin (fclasquin@gmail.com)
 * @brief     This file provides set of firmware functions to manage Leds, 
 *            push-button available on the Core Board.
 * @version   1.0
 * @date      2025-10-17
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

/* Includes ------------------------------------------------------------------*/
#include "PY32F002B_EmbedFire_Core_Board.h"

/**
  * @}
  */
/** @defgroup PY32F002B_EMBEDFIRE_LOW_LEVEL_Private_Variables LOW LEVEL Private Variables
  * @{
  */

#ifdef HAL_UART_MODULE_ENABLED
UART_HandleTypeDef DebugUartHandle;
#endif

GPIO_TypeDef* LED_PORT[LEDn] = {LED2_GPIO_PORT,
                                LED3_GPIO_PORT,
                                LED4_GPIO_PORT};

const uint16_t LED_PIN[LEDn] = {LED2_PIN,
                                LED3_PIN,
                                LED4_PIN};

GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {BUTTON1_USER_GPIO_PORT, 
                                      BUTTON2_USER_GPIO_PORT};

const uint16_t BUTTON_PIN[BUTTONn] = {BUTTON1_USER_PIN, 
                                      BUTTON2_USER_PIN};

const uint8_t BUTTON_IRQn[BUTTONn] = {BUTTON1_USER_EXTI_IRQn,
                                      BUTTON2_USER_EXTI_IRQn};

/** @addtogroup PY32F002B_EMBEDFIRE_Exported_Functions
  * @{
  */

/**
  * @brief  This method returns the PY32F002B EMBEDFIRE BSP Driver revision.
  * @retval version : 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t BSP_GetVersion(void)
{
  return __PY32F002B_EMBEDFIRE_BSP_VERSION;
}

/** @addtogroup LED_Functions
  * @{
  */

/**
  * @brief  Configures LED GPIO.
  * @param  Led Specifies the Led to be configured.
  *         This parameter can be one of following parameters:
  *     @arg  LED2
  *     @arg  LED3
  *     @arg  LED4
  * @retval None
  */
void BSP_LED_Init(Led_TypeDef Led)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  /* Enable the GPIO_LED Clock */
  LEDx_GPIO_CLK_ENABLE(Led);

  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.Pin = LED_PIN[Led];
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  HAL_GPIO_Init(LED_PORT[Led], &GPIO_InitStruct);
  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_SET);
}

/**
  * @brief  DeInitialize LED GPIO.
  * @param  Led Specifies the Led to be deconfigured.
  *         This parameter can be one of the following values:
  *     @arg  LED2
  *     @arg  LED3
  *     @arg  LED4
  * @note   BSP_LED_DeInit() does not disable the GPIO clock
  * @retval None
  */
void BSP_LED_DeInit(Led_TypeDef Led)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  /* Turn off LED */
  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_RESET);
  /* DeInit the GPIO_LED pin */
  GPIO_InitStruct.Pin = LED_PIN[Led];
  HAL_GPIO_DeInit(LED_PORT[Led], GPIO_InitStruct.Pin);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led Specifies the Led to be set on.
  *         This parameter can be one of following parameters:
  *     @arg  LED2
  *     @arg  LED3
  *     @arg  LED4
  * @retval None
  */
void BSP_LED_On(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_RESET);
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led Specifies the Led to be set off.
  *         This parameter can be one of following parameters:
  *     @arg  LED2
  *     @arg  LED3
  *     @arg  LED4
  * @retval None
  */
void BSP_LED_Off(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_SET);
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led Specifies the Led to be toggled.
  *         This parameter can be one of following parameters:
  *     @arg  LED2
  *     @arg  LED3
  *     @arg  LED4
  * @retval None
  */
void BSP_LED_Toggle(Led_TypeDef Led)
{
  HAL_GPIO_TogglePin(LED_PORT[Led], LED_PIN[Led]);
}

/**
  * @brief  Get the state of the selected LED.
  * @param  Led LED to get its state
  *         This parameter can be one of following parameters:
  *     @arg  LED2
  *     @arg  LED3
  *     @arg  LED4
  * @retval LED status
  */
int32_t BSP_LED_GetState (Led_TypeDef Led)
{
  int32_t ret;

  if((Led != LED2) && (Led != LED3) && (Led != LED4))
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    ret = (int32_t)HAL_GPIO_ReadPin (LED_PORT [Led], LED_PIN [Led]);
  }

  return ret;
}

/**
  * @brief  Configures button GPIO and EXTI Line.
  * @param  Button Button to be configured
  *         This parameter can be one of the following values:
  *         @arg  BUTTON_USER1: Wakeup Push Button 1
  *         @arg  BUTTON_USER2: Wakeup Push Button 2
  * @param  ButtonMode Button mode
  *         This parameter can be one of the following values:
  *         @arg  BUTTON_MODE_GPIO: Button will be used as simple IO
  *         @arg  BUTTON_MODE_EXTI: Button will be connected to EXTI line
  *                                    with interrupt generation capability
  */
void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Enable the BUTTON clock */
  BUTTONx_GPIO_CLK_ENABLE(Button);

  GPIO_InitStruct.Pin = BUTTON_PIN [Button];
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  if(ButtonMode == BUTTON_MODE_GPIO)
  {
    /* Configure Button pin as input */
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    
	  HAL_GPIO_Init(BUTTON_PORT [Button], &GPIO_InitStruct);
  }
  
  if(ButtonMode == BUTTON_MODE_EXTI)
  {
    /* Configure Button pin as input with External interrupt */
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	  HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);

    /* Enable and set Button EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(BUTTON_IRQn[Button]), 0x0F, 0x00);
    HAL_NVIC_EnableIRQ(((IRQn_Type)(BUTTON_IRQn[Button]));
  }
}

/**
  * @brief  Push Button DeInit.
  * @param  Button Button to be configured
  *         This parameter can be one of the following values:
  *         @arg  BUTTON_USER1: Wakeup Push Button 1
  *         @arg  BUTTON_USER2: Wakeup Push Button 2
  * @note PB DeInit does not disable the GPIO clock
  */
void BSP_PB_DeInit(Button_TypeDef Button)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  GPIO_InitStruct.Pin = BUTTON_PIN[Button];
  HAL_NVIC_DisableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
  HAL_GPIO_DeInit(BUTTON_PORT[Button], GPIO_InitStruct.Pin);
}

/**
  * @brief  Returns the selected button state.
  * @param  Button Button to be checked
  *         This parameter can be one of the following values:
  *         @arg  BUTTON_USER1: Wakeup Push Button 1
  *         @arg  BUTTON_USER2: Wakeup Push Button 2
  * @retval The Button GPIO pin value (GPIO_PIN_RESET = button pressed)
  */
int32_t BSP_PB_GetState(Button_TypeDef Button)
{
  return (HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]) == GPIO_PIN_RESET);
  /* return HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]); */
}

#ifdef HAL_UART_MODULE_ENABLED
/**
  * @brief  DEBUG_USART GPIO Config,Mode Config,115200 8-N-1
  * @param  None
  * @retval None
  */
void BSP_USART_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  DEBUG_USART_CLK_ENABLE();

  DebugUartHandle.Instance          = DEBUG_USART;

  DebugUartHandle.Init.BaudRate     = DEBUG_USART_BAUDRATE;
  DebugUartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
  DebugUartHandle.Init.StopBits     = UART_STOPBITS_1;
  DebugUartHandle.Init.Parity       = UART_PARITY_NONE;
  DebugUartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  DebugUartHandle.Init.Mode         = UART_MODE_TX_RX;

  HAL_UART_Init(&DebugUartHandle);

  DEBUG_USART_RX_GPIO_CLK_ENABLE();
  DEBUG_USART_TX_GPIO_CLK_ENABLE();

  /**USART1 GPIO Configuration
    PA2     ------> USART1_TX
    PA3     ------> USART1_RX
    */
  GPIO_InitStruct.Pin = DEBUG_USART_TX_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = DEBUG_USART_TX_AF;
  HAL_GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = DEBUG_USART_RX_PIN;
  GPIO_InitStruct.Alternate = DEBUG_USART_RX_AF;

  HAL_GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStruct);

  /* ENABLE NVIC */
  HAL_NVIC_SetPriority(DEBUG_USART_IRQ,0,1);
  HAL_NVIC_EnableIRQ(DEBUG_USART_IRQ );
}

#if (defined (__CC_ARM)) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
/**
  * @brief  writes a character to the usart
  * @param  ch
  *         *f
  * @retval the character
  */
int fputc(int ch, FILE *f)
{
  /* Send a byte to USART */
  HAL_UART_Transmit(&DebugUartHandle, (uint8_t *)&ch, 1, 1000);

  return (ch);
}

/**
  * @brief  get a character from the usart
  * @param  *f
  * @retval a character
  */
int fgetc(FILE *f)
{
  int ch;
  HAL_UART_Receive(&DebugUartHandle, (uint8_t *)&ch, 1, 1000);
  return (ch);
}

#elif defined(__ICCARM__)
/**
  * @brief  writes a character to the usart
  * @param  ch
  *         *f
  * @retval the character
  */
int putchar(int ch)
{
  /* Send a byte to USART */
  HAL_UART_Transmit(&DebugUartHandle, (uint8_t *)&ch, 1, 1000);

  return (ch);
}
#endif

#endif
/**
  * @}
  */

/** EOF **/