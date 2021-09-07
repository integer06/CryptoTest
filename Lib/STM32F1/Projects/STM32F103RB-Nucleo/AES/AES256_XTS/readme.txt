/**
  @page AES256_XTS  AES algorithm in XTS mode

  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    AES/AES256_XTS/readme.txt 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Description of the "AES256 XTS modes" example.
  ******************************************************************************
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
   @endverbatim

@par Example Description
This example describes how to use the STM32 Cryptographic Library AES algorithm
and the different steps (Initialization/Append data/Finalization) to perform AES
256 bits Encryption/Decryption processes for XTS mode.

This example is split into two parts:
The first part is to:
1 - Encrypt DATA in XTS mode 
2 - Compare between the encrypted data and expected encrypted data 

AES algorithm routines can return AES_SUCCESS in case of successful encryption 
operations or one of the following error codes in case of fail:

  - AES_ERR_BAD_OPERATION
  - AES_ERR_BAD_CONTEXT
  - AES_ERR_BAD_PARAMETER
  - AES_ERR_BAD_INPUT_SIZE 

The second part is to:
1 - Decrypt DATA in XTS mode
2 - Compare between the decrypted data and expected decrypted data 

AES algorithm routines can return AES_SUCCESS in case of successful decryption 
operations or one of the following error codes in case of fail:

  - AES_ERR_BAD_OPERATION
  - AES_ERR_BAD_CONTEXT
  - AES_ERR_BAD_PARAMETER
  - AES_ERR_BAD_INPUT_SIZE.  

The green LED will be toggled three times each 500 milliseconds before starting 
the AES XTS algorithms operations.    
In case of successful Encryption and Decryption operations the green led will 
be turned on and in case of fail it will be toggled each 250 milliseconds in an 
infinity loop. 

  IEEE vectors examples for XTS are taken from:
	"IEEE P1619�/D16 Standard for Cryptographic Protection of Data on 
	 Block-Oriented Storage Devices "
	Available at:
	http://grouper.ieee.org/groups/1619/email/pdf00086.pdf


@par Directory contents 

  - AES/AES256_XTS/Inc/stm32f0xx_hal_conf.h    HAL configuration file        
  - AES/AES256_XTS/Inc/stm32f0xx_it.h          Interrupt handlers header file
  - AES/AES256_XTS/Inc/main.h                  Header for main.c module      
  - AES/AES256_XTS/Src/stm32f0xx_it.c          Interrupt handlers            
  - AES/AES256_XTS/Src/main.c                  Main program                  
  - AES/AES256_XTS/Src/system_stm32f1xx.c      STM32F1xx system source file  


@par Hardware and Software environment

  - This example runs on STM32F103RB devices.
    
  - This example has been tested with STM32F103RB-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */