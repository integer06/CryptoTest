/**
  ******************************************************************************
  * @file    AES/AES128_CFB/Src/main.c
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32_Crypto_Examples
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/
#define PLAINTEXT_LENGTH 16
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const uint8_t Plaintext[PLAINTEXT_LENGTH] =
  {
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
    0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a
  };

/* Key to be used for AES encryption/decryption */
uint8_t Key[CRL_AES128_KEY] =
  {
    0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
    0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
  };

/* Initialization Vector, used only in non-ECB modes */
uint8_t IV[CRL_AES_BLOCK] =
  {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
  };


/* Buffer to store the output data */
uint8_t OutputMessage[PLAINTEXT_LENGTH];

/* Size of the output data */
uint32_t OutputMessageLength = 0;

const uint8_t Expected_Ciphertext[PLAINTEXT_LENGTH] =
  {
    0x3b, 0x3f, 0xd9, 0x2e, 0xb7, 0x2d, 0xad, 0x20,
    0x33, 0x34, 0x49, 0xf8, 0xe8, 0x3c, 0xfb, 0x4a
  };



/* Private function prototypes -----------------------------------------------*/
int32_t STM32_AES_CFB_Encrypt(uint8_t*  InputMessage,
                              uint32_t  InputMessageLength,
                              uint8_t  *AES128_Key,
                              uint8_t  *InitializationVector,
                              uint32_t  IvLength,
                              uint8_t  *OutputMessage,
                              uint32_t *OutputMessageLength);

int32_t STM32_AES_CFB_Decrypt(uint8_t*  InputMessage,
                              uint32_t  InputMessageLength,
                              uint8_t  *AES128_Key,
                              uint8_t  *InitializationVector,
                              uint32_t  IvLength,
                              uint8_t  *OutputMessage,
                              uint32_t *OutputMessageLength);

TestStatus Buffercmp(const uint8_t* pBuffer,
                     uint8_t* pBuffer1,
                     uint16_t BufferLength);

static void SystemClock_Config(void);
static void Led_Config(void);
static void Led_Toggle( __IO uint32_t toggle_delay);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  int32_t status = AES_SUCCESS;

  /* STM32F103xB HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure the system clock to 64 MHz */
  SystemClock_Config();

  /* Configure the green led */
  Led_Config();

  /* Toggle the green led three times before starting the algorithm */
  Led_Toggle(500);


  /* Enable CRC clock */
  __CRC_CLK_ENABLE();

  /* Encrypt DATA with AES in CFB mode */
  status = STM32_AES_CFB_Encrypt( (uint8_t *) Plaintext, PLAINTEXT_LENGTH, Key, IV, sizeof(IV), OutputMessage,
                                  &OutputMessageLength);
  if (status == AES_SUCCESS)
  {
    if (Buffercmp(Expected_Ciphertext, OutputMessage, PLAINTEXT_LENGTH) == PASSED)
    {
      /* add application traitment in case of AES CFB encryption is passed */

    }
    else
    {

      Error_Handler();

    }
  }
  else
  {
    /* In case of encryption not success the possible values of status:
     * AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_OPERATION
     */

    Error_Handler();

  }

  /* Decrypt DATA with AES in CFB mode */
  status = STM32_AES_CFB_Decrypt( (uint8_t *) Expected_Ciphertext, PLAINTEXT_LENGTH, Key, IV, sizeof(IV), OutputMessage,
                                  &OutputMessageLength);
  if (status == AES_SUCCESS)
  {
    if (Buffercmp(Plaintext, OutputMessage, PLAINTEXT_LENGTH) == PASSED)
    {
      /* add application traitment in case of AES CFB decryption is passed */

    }
    else
    {

      Error_Handler();

    }
  }
  else
  {
    /* In case of decryption not success the possible values of status:
     * AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_OPERATION
     */

    Error_Handler();

  }

  /* Turn on the green led in case of AES CFB operations are successful*/
  HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_SET);
  while (1)
  {}
}

/**
  * @brief  AES CFB Encryption example.
  * @param  InputMessage: pointer to input message to be encrypted.
  * @param  InputMessageLength: input data message length in byte.
  * @param  AES128_Key: pointer to the AES key to be used in the operation
  * @param  InitializationVector: pointer to the Initialization Vector (IV)
  * @param  IvLength: IV length in bytes.
  * @param  OutputMessage: pointer to output parameter that will handle the encrypted message
  * @param  OutputMessageLength: pointer to encrypted message length.
  * @retval error status: can be AES_SUCCESS if success or one of
  *         AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_OPERATION
  *         if error occured.
  */
int32_t STM32_AES_CFB_Encrypt(uint8_t* InputMessage,
                              uint32_t InputMessageLength,
                              uint8_t  *AES128_Key,
                              uint8_t  *InitializationVector,
                              uint32_t  IvLength,
                              uint8_t  *OutputMessage,
                              uint32_t *OutputMessageLength)
{
  AESECBctx_stt AESctx;

  uint32_t error_status = AES_SUCCESS;

  int32_t outputLength = 0;

  /* Set flag field to default value */
  AESctx.mFlags = E_SK_DEFAULT;

  /* Set key size to 16 (corresponding to AES-128) */
  AESctx.mKeySize = 16;

  /* Set iv size field to IvLength*/
  AESctx.mIvSize = IvLength;

  /* Initialize the operation, by passing the key.*/
  error_status = AES_CFB_Encrypt_Init(&AESctx, AES128_Key, InitializationVector );

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Encrypt Data */
    error_status = AES_CFB_Encrypt_Append(&AESctx,
                                          InputMessage,
                                          InputMessageLength,
                                          OutputMessage,
                                          &outputLength);

    if (error_status == AES_SUCCESS)
    {
      /* Write the number of data written*/
      *OutputMessageLength = outputLength;
      /* Do the Finalization */
      error_status = AES_CFB_Encrypt_Finish(&AESctx, OutputMessage + *OutputMessageLength, &outputLength);
      /* Add data written to the information to be returned */
      *OutputMessageLength += outputLength;
    }
  }

  return error_status;
}


/**
  * @brief  AES CFB Decryption example.
  * @param  InputMessage: pointer to input message to be decrypted.
  * @param  InputMessageLength: input data message length in byte.
  * @param  AES128_Key: pointer to the AES key to be used in the operation
  * @param  InitializationVector: pointer to the Initialization Vector (IV)
  * @param  IvLength: IV length in bytes.
  * @param  OutputMessage: pointer to output parameter that will handle the decrypted message
  * @param  OutputMessageLength: pointer to decrypted message length.
  * @retval error status: can be AES_SUCCESS if success or one of
  *         AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_OPERATION
  *         if error occured.
  */
int32_t STM32_AES_CFB_Decrypt(uint8_t* InputMessage,
                              uint32_t InputMessageLength,
                              uint8_t  *AES128_Key,
                              uint8_t  *InitializationVector,
                              uint32_t  IvLength,
                              uint8_t  *OutputMessage,
                              uint32_t *OutputMessageLength)
{
  AESECBctx_stt AESctx;

  uint32_t error_status = AES_SUCCESS;

  int32_t outputLength = 0;

  /* Set flag field to default value */
  AESctx.mFlags = E_SK_DEFAULT;

  /* Set key size to 16 (corresponding to AES-128) */
  AESctx.mKeySize = 16;

  /* Set iv size field to IvLength*/
  AESctx.mIvSize = IvLength;

  /* Initialize the operation, by passing the key. */
  error_status = AES_CFB_Decrypt_Init(&AESctx, AES128_Key, InitializationVector );

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Decrypt Data */
    error_status = AES_CFB_Decrypt_Append(&AESctx,
                                          InputMessage,
                                          InputMessageLength,
                                          OutputMessage,
                                          &outputLength);
    if (error_status == AES_SUCCESS)
    {
      /* Write the number of data written*/
      *OutputMessageLength = outputLength;
      /* Do the Finalization */
      error_status = AES_CFB_Decrypt_Finish(&AESctx, OutputMessage + *OutputMessageLength, &outputLength);
      /* Add data written to the information to be returned */
      *OutputMessageLength += outputLength;
    }
  }

  return error_status;
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer, pBuffer1: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer identical to pBuffer1
  *         FAILED: pBuffer differs from pBuffer1
  */
TestStatus Buffercmp(const uint8_t* pBuffer, uint8_t* pBuffer1, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer != *pBuffer1)
    {
      return FAILED;
    }

    pBuffer++;
    pBuffer1++;
  }

  return PASSED;
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 64000000
  *            HCLK(Hz)                       = 64000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            PLLMUL                         = 16
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef clkinitstruct = {0};
  RCC_OscInitTypeDef oscinitstruct = {0};
  
  /* Configure PLL ------------------------------------------------------*/
  /* PLL configuration: PLLCLK = (HSI / 2) * PLLMUL = (8 / 2) * 16 = 64 MHz */
  /* PREDIV1 configuration: PREDIV1CLK = PLLCLK / HSEPredivValue = 64 / 1 = 64 MHz */
  /* Enable HSI and activate PLL with HSi_DIV2 as source */
  oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSI;
  oscinitstruct.HSEState        = RCC_HSE_OFF;
  oscinitstruct.LSEState        = RCC_LSE_OFF;
  oscinitstruct.HSIState        = RCC_HSI_ON;
  oscinitstruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  oscinitstruct.HSEPredivValue    = RCC_HSE_PREDIV_DIV1;
  oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
  oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSI_DIV2;
  oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&oscinitstruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
  clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }
}

/**
  * @brief  Configures the green led.
  * @param  None
  * @retval None
  */
static void Led_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
    /* -1- Enable each GPIO Clock (to be able to program the configuration registers) */
  LED2_GPIO_CLK_ENABLE();

  /* -2- Configure IOs in output push-pull mode to drive external LEDs */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Pin = LED2_PIN;
  HAL_GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);
  
}

/**
  * @brief  Toggles the green Led.
  * @param  None
  * @retval None
  */
static void Led_Toggle( __IO uint32_t toggle_delay)
{
      HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
      HAL_Delay(toggle_delay);      
      HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
      HAL_Delay(toggle_delay);
      HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
      HAL_Delay(toggle_delay);
      HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
      HAL_Delay(toggle_delay);
      HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
      HAL_Delay(toggle_delay);
      HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while (1)
  {
    HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
    HAL_Delay(250);
    HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
    HAL_Delay(250);
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif


/**
  * @}
  */


/******************* (C) COPYRIGHT 2015 STMicroeleCCMonics *****END OF FILE****/
