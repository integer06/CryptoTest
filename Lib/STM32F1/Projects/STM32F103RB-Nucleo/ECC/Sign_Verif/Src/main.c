/**
  ******************************************************************************
  * @file    ECC/Sign_Verif/Src/main.c
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
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/******************************************************************************/
/******** Parameters for Elliptic Curve P-192 SHA-256 from FIPS 186-3**********/
/******************************************************************************/
/* Private variables ---------------------------------------------------------*/
const uint8_t InputMessage_192[] =
  {
    0x5c, 0x86, 0x8f, 0xed, 0xb8, 0x02, 0x69, 0x79, 0xeb, 0xd2, 0x6f, 0x1b, 0xa0,
    0x7c, 0x27, 0xee, 0xdf, 0x4f, 0xf6, 0xd1, 0x04, 0x43, 0x50, 0x5a, 0x96, 0xec,
    0xaf, 0x21, 0xba, 0x8c, 0x4f, 0x09, 0x37, 0xb3, 0xcd, 0x23, 0xff, 0xdc, 0x3d,
    0xd4, 0x29, 0xd4, 0xcd, 0x19, 0x05, 0xfb, 0x8d, 0xbc, 0xce, 0xef, 0xf1, 0x35,
    0x00, 0x20, 0xe1, 0x8b, 0x58, 0xd2, 0xba, 0x70, 0x88, 0x7b, 0xaa, 0x3a, 0x9b,
    0x78, 0x3a, 0xd3, 0x0d, 0x3f, 0xbf, 0x21, 0x03, 0x31, 0xcd, 0xd7, 0xdf, 0x8d,
    0x77, 0xde, 0xfa, 0x39, 0x8c, 0xda, 0xcd, 0xfc, 0x2e, 0x35, 0x9c, 0x7b, 0xa4,
    0xca, 0xe4, 0x6b, 0xb7, 0x44, 0x01, 0xde, 0xb4, 0x17, 0xf8, 0xb9, 0x12, 0xa1,
    0xaa, 0x96, 0x6a, 0xee, 0xba, 0x9c, 0x39, 0xc7, 0xdd, 0x22, 0x47, 0x9a, 0xe2,
    0xb3, 0x07, 0x19, 0xdc, 0xa2, 0xf2, 0x20, 0x6c, 0x5e, 0xb4, 0xb7
  };

const uint8_t P_192_a[] =
  {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC
  };

/* coefficient b */
const uint8_t P_192_b[] =
  {
    0x64, 0x21, 0x05, 0x19, 0xE5, 0x9C, 0x80, 0xE7, 0x0F, 0xA7, 0xE9, 0xAB, 0x72,
    0x24, 0x30, 0x49, 0xFE, 0xB8, 0xDE, 0xEC, 0xC1, 0x46, 0xB9, 0xB1
  };

/* prime modulus p*/
const uint8_t P_192_p[] =
  {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
  };

/* order n*/
const uint8_t P_192_n[] =
  {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x99,
    0xDE, 0xF8, 0x36, 0x14, 0x6B, 0xC9, 0xB1, 0xB4, 0xD2, 0x28, 0x31
  };

/* base point Gx*/
const uint8_t P_192_Gx[] =
  {
    0x18, 0x8D, 0xA8, 0x0E, 0xB0, 0x30, 0x90, 0xF6, 0x7C, 0xBF, 0x20, 0xEB, 0x43,
    0xA1, 0x88, 0x00, 0xF4, 0xFF, 0x0A, 0xFD, 0x82, 0xFF, 0x10, 0x12
  };

/* base point Gy*/
const uint8_t P_192_Gy[] =
  {
    0x07, 0x19, 0x2B, 0x95, 0xFF, 0xC8, 0xDA, 0x78, 0x63, 0x10, 0x11, 0xED, 0x6B,
    0x24, 0xCD, 0xD5, 0x73, 0xF9, 0x77, 0xA1, 0x1E, 0x79, 0x48, 0x11
  };

/* ECSA public key */
/* pub_x*/
const uint8_t pub_x_192[] =
  {
    0x9b, 0xf1, 0x2d, 0x71, 0x74, 0xb7, 0x70, 0x8a, 0x07, 0x6a, 0x38, 0xbc, 0x80,
    0xaa, 0x28, 0x66, 0x2f, 0x25, 0x1e, 0x2e, 0xd8, 0xd4, 0x14, 0xdc
  };

/* pub_y */
const uint8_t pub_y_192[] =
  {
    0x48, 0x54, 0xc8, 0xd0, 0x7d, 0xfc, 0x08, 0x82, 0x4e, 0x9e, 0x47, 0x1c, 0xa2,
    0xfe, 0xdc, 0xfc, 0xff, 0x3d, 0xdc, 0xb0, 0x11, 0x57, 0x34, 0x98
  };

/* ECDSA signature of SHA-256("....") */
/* sign_r */
const uint8_t sign_r_192[] =
  {
    0x35, 0x4a, 0xba, 0xec, 0xf4, 0x36, 0x1f, 0xea, 0x90, 0xc2, 0x9b, 0x91, 0x99,
    0x88, 0x2e, 0xdf, 0x85, 0x73, 0xe6, 0x86, 0xa8, 0x13, 0xef, 0xf8
  };

/* sign_s */
const uint8_t sign_s_192[] =
  {
    0x80, 0xf5, 0x00, 0x00, 0xac, 0x86, 0x11, 0x1c, 0x9b, 0x30, 0x47, 0x38, 0x5a,
    0x15, 0xd7, 0x8e, 0x63, 0x2c, 0x58, 0xb7, 0x94, 0x9e, 0x82, 0xc1
  };

/******************************************************************************/
/********* Parameters for Elliptic Curve P-256 SHA-256 from FIPS 186-3*********/
/******************************************************************************/
/* Private variables ---------------------------------------------------------*/
const uint8_t InputMessage_256[] =
  {
    0x59, 0x05, 0x23, 0x88, 0x77, 0xc7, 0x74, 0x21, 0xf7, 0x3e, 0x43, 0xee, 0x3d,
    0xa6, 0xf2, 0xd9, 0xe2, 0xcc, 0xad, 0x5f, 0xc9, 0x42, 0xdc, 0xec, 0x0c, 0xbd,
    0x25, 0x48, 0x29, 0x35, 0xfa, 0xaf, 0x41, 0x69, 0x83, 0xfe, 0x16, 0x5b, 0x1a,
    0x04, 0x5e, 0xe2, 0xbc, 0xd2, 0xe6, 0xdc, 0xa3, 0xbd, 0xf4, 0x6c, 0x43, 0x10,
    0xa7, 0x46, 0x1f, 0x9a, 0x37, 0x96, 0x0c, 0xa6, 0x72, 0xd3, 0xfe, 0xb5, 0x47,
    0x3e, 0x25, 0x36, 0x05, 0xfb, 0x1d, 0xdf, 0xd2, 0x80, 0x65, 0xb5, 0x3c, 0xb5,
    0x85, 0x8a, 0x8a, 0xd2, 0x81, 0x75, 0xbf, 0x9b, 0xd3, 0x86, 0xa5, 0xe4, 0x71,
    0xea, 0x7a, 0x65, 0xc1, 0x7c, 0xc9, 0x34, 0xa9, 0xd7, 0x91, 0xe9, 0x14, 0x91,
    0xeb, 0x37, 0x54, 0xd0, 0x37, 0x99, 0x79, 0x0f, 0xe2, 0xd3, 0x08, 0xd1, 0x61,
    0x46, 0xd5, 0xc9, 0xb0, 0xd0, 0xde, 0xbd, 0x97, 0xd7, 0x9c, 0xe8
  };

const uint8_t P_256_a[] =
  {
    0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC
  };
/* coefficient b */
const uint8_t P_256_b[] =
  {
    0x5a, 0xc6, 0x35, 0xd8, 0xaa, 0x3a, 0x93, 0xe7, 0xb3, 0xeb, 0xbd, 0x55, 0x76,
    0x98, 0x86, 0xbc, 0x65, 0x1d, 0x06, 0xb0, 0xcc, 0x53, 0xb0, 0xf6, 0x3b, 0xce,
    0x3c, 0x3e, 0x27, 0xd2, 0x60, 0x4b
  };

/* prime modulus p*/
const uint8_t P_256_p[] =
  {
    0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
  };

/* order n*/
const uint8_t P_256_n[] =
  {
    0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xBC, 0xE6, 0xFA, 0xAD, 0xA7, 0x17, 0x9E, 0x84, 0xF3, 0xB9,
    0xCA, 0xC2, 0xFC, 0x63, 0x25, 0x51
  };

/* base point Gx*/
const uint8_t P_256_Gx[] =
  {
    0x6B, 0x17, 0xD1, 0xF2, 0xE1, 0x2C, 0x42, 0x47, 0xF8, 0xBC, 0xE6, 0xE5, 0x63,
    0xA4, 0x40, 0xF2, 0x77, 0x03, 0x7D, 0x81, 0x2D, 0xEB, 0x33, 0xA0, 0xF4, 0xA1,
    0x39, 0x45, 0xD8, 0x98, 0xC2, 0x96
  };

/* base point Gy*/
const uint8_t P_256_Gy[] =
  {
    0x4F, 0xE3, 0x42, 0xE2, 0xFE, 0x1A, 0x7F, 0x9B, 0x8E, 0xE7, 0xEB, 0x4A, 0x7C,
    0x0F, 0x9E, 0x16, 0x2B, 0xCE, 0x33, 0x57, 0x6B, 0x31, 0x5E, 0xCE, 0xCB, 0xB6,
    0x40, 0x68, 0x37, 0xBF, 0x51, 0xF5
  };

/* ECSA public key */
/* pub_x */
const uint8_t pub_x_256[] =
  {
    0x1c, 0xcb, 0xe9, 0x1c, 0x07, 0x5f, 0xc7, 0xf4, 0xf0, 0x33, 0xbf, 0xa2, 0x48,
    0xdb, 0x8f, 0xcc, 0xd3, 0x56, 0x5d, 0xe9, 0x4b, 0xbf, 0xb1, 0x2f, 0x3c, 0x59,
    0xff, 0x46, 0xc2, 0x71, 0xbf, 0x83
  };

/* pub_y */
const uint8_t pub_y_256[] =
  {
    0xce, 0x40, 0x14, 0xc6, 0x88, 0x11, 0xf9, 0xa2, 0x1a, 0x1f, 0xdb, 0x2c, 0x0e,
    0x61, 0x13, 0xe0, 0x6d, 0xb7, 0xca, 0x93, 0xb7, 0x40, 0x4e, 0x78, 0xdc, 0x7c,
    0xcd, 0x5c, 0xa8, 0x9a, 0x4c, 0xa9
  };

/* ECDSA signature of SHA-256("....") */
/* sign_r */
const uint8_t sign_r_256[] =
  {
    0xf3, 0xac, 0x80, 0x61, 0xb5, 0x14, 0x79, 0x5b, 0x88, 0x43, 0xe3, 0xd6, 0x62,
    0x95, 0x27, 0xed, 0x2a, 0xfd, 0x6b, 0x1f, 0x6a, 0x55, 0x5a, 0x7a, 0xca, 0xbb,
    0x5e, 0x6f, 0x79, 0xc8, 0xc2, 0xac
  };

/* sign_s */
const uint8_t sign_s_256[] =
  {
    0x8b, 0xf7, 0x78, 0x19, 0xca, 0x05, 0xa6, 0xb2, 0x78, 0x6c, 0x76, 0x26, 0x2b,
    0xf7, 0x37, 0x1c, 0xef, 0x97, 0xb2, 0x18, 0xe9, 0x6f, 0x17, 0x5a, 0x3c, 0xcd,
    0xda, 0x2a, 0xcc, 0x05, 0x89, 0x03
  };

/******************************************************************************/
/*********** Parameters for Elliptic Curve P-384 SHA-256 from FIPS 186-3*******/
/******************************************************************************/
/* Private variables ---------------------------------------------------------*/
const uint8_t InputMessage_384[] =
  {
    0x66, 0x3b, 0x12, 0xeb, 0xf4, 0x4b, 0x7e, 0xd3, 0x87, 0x2b, 0x38, 0x54, 0x77,
    0x38, 0x1f, 0x4b, 0x11, 0xad, 0xeb, 0x0a, 0xec, 0x9e, 0x0e, 0x24, 0x78, 0x77,
    0x63, 0x13, 0xd5, 0x36, 0x37, 0x6d, 0xc8, 0xfd, 0x5f, 0x3c, 0x71, 0x5b, 0xb6,
    0xdd, 0xf3, 0x2c, 0x01, 0xee, 0x1d, 0x6f, 0x8b, 0x73, 0x17, 0x85, 0x73, 0x2c,
    0x0d, 0x84, 0x41, 0xdf, 0x63, 0x6d, 0x81, 0x45, 0x57, 0x7e, 0x7b, 0x31, 0x38,
    0xe4, 0x3c, 0x32, 0xa6, 0x1b, 0xc1, 0x24, 0x2e, 0x0e, 0x73, 0xd6, 0x2d, 0x62,
    0x4c, 0xdc, 0x92, 0x48, 0x56, 0x07, 0x6b, 0xdb, 0xbf, 0x1e, 0xc0, 0x4a, 0xd4,
    0x42, 0x07, 0x32, 0xef, 0x0c, 0x53, 0xd4, 0x24, 0x79, 0xa0, 0x82, 0x35, 0xfc,
    0xfc, 0x4d, 0xb4, 0xd8, 0x69, 0xc4, 0xeb, 0x28, 0x28, 0xc7, 0x39, 0x28, 0xcd,
    0xc3, 0xe3, 0x75, 0x83, 0x62, 0xd1, 0xb7, 0x70, 0x80, 0x99, 0x97
  };

const uint8_t P_384_a[] =
  {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFC
  };

/* coefficient b */
const uint8_t P_384_b[] =
  {
    0xb3, 0x31, 0x2f, 0xa7, 0xe2, 0x3e, 0xe7, 0xe4, 0x98, 0x8e, 0x05, 0x6b, 0xe3,
    0xf8, 0x2d, 0x19, 0x18, 0x1d, 0x9c, 0x6e, 0xfe, 0x81, 0x41, 0x12, 0x03, 0x14,
    0x08, 0x8f, 0x50, 0x13, 0x87, 0x5a, 0xc6, 0x56, 0x39, 0x8d, 0x8a, 0x2e, 0xd1,
    0x9d, 0x2a, 0x85, 0xc8, 0xed, 0xd3, 0xec, 0x2a, 0xef
  };

/* prime modulus p*/
const uint8_t P_384_p[] =
  {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
  };
/* order n*/
const uint8_t P_384_n[] =
  {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC7, 0x63,
    0x4D, 0x81, 0xF4, 0x37, 0x2D, 0xDF, 0x58, 0x1A, 0x0D, 0xB2, 0x48, 0xB0, 0xA7,
    0x7A, 0xEC, 0xEC, 0x19, 0x6A, 0xCC, 0xC5, 0x29, 0x73
  };

/* base point Gx*/
const uint8_t P_384_Gx[] =
  {
    0xAA, 0x87, 0xCA, 0x22, 0xBE, 0x8B, 0x05, 0x37, 0x8E, 0xB1, 0xC7, 0x1E, 0xF3,
    0x20, 0xAD, 0x74, 0x6E, 0x1D, 0x3B, 0x62, 0x8B, 0xA7, 0x9B, 0x98, 0x59, 0xF7,
    0x41, 0xE0, 0x82, 0x54, 0x2A, 0x38, 0x55, 0x02, 0xF2, 0x5D, 0xBF, 0x55, 0x29,
    0x6C, 0x3A, 0x54, 0x5E, 0x38, 0x72, 0x76, 0x0A, 0xB7
  };

/* base point Gy*/
const uint8_t P_384_Gy[] =
  {
    0x36, 0x17, 0xDE, 0x4A, 0x96, 0x26, 0x2C, 0x6F, 0x5D, 0x9E, 0x98, 0xBF, 0x92,
    0x92, 0xDC, 0x29, 0xF8, 0xF4, 0x1D, 0xBD, 0x28, 0x9A, 0x14, 0x7C, 0xE9, 0xDA,
    0x31, 0x13, 0xB5, 0xF0, 0xB8, 0xC0, 0x0A, 0x60, 0xB1, 0xCE, 0x1D, 0x7E, 0x81,
    0x9D, 0x7A, 0x43, 0x1D, 0x7C, 0x90, 0xEA, 0x0E, 0x5F
  };

/* ECSA public key */
/* pub_x */
const uint8_t pub_x_384[] =
  {
    0x04, 0x00, 0x19, 0x3b, 0x21, 0xf0, 0x7c, 0xd0, 0x59, 0x82, 0x6e, 0x94, 0x53,
    0xd3, 0xe9, 0x6d, 0xd1, 0x45, 0x04, 0x1c, 0x97, 0xd4, 0x9f, 0xf6, 0xb7, 0x04,
    0x7f, 0x86, 0xbb, 0x0b, 0x04, 0x39, 0xe9, 0x09, 0x27, 0x4c, 0xb9, 0xc2, 0x82,
    0xbf, 0xab, 0x88, 0x67, 0x4c, 0x07, 0x65, 0xbc, 0x75
  };

/* pub_y */
const uint8_t pub_y_384[] =
  {
    0xf7, 0x0d, 0x89, 0xc5, 0x2a, 0xcb, 0xc7, 0x04, 0x68, 0xd2, 0xc5, 0xae, 0x75,
    0xc7, 0x6d, 0x7f, 0x69, 0xb7, 0x6a, 0xf6, 0x2d, 0xcf, 0x95, 0xe9, 0x9e, 0xba,
    0x5d, 0xd1, 0x1a, 0xdf, 0x8f, 0x42, 0xec, 0x9a, 0x42, 0x5b, 0x0c, 0x5e, 0xc9,
    0x8e, 0x2f, 0x23, 0x4a, 0x92, 0x6b, 0x82, 0xa1, 0x47
  };

/* ECDSA signature of SHA-256("....") */
/* sign_r */
const uint8_t sign_r_384[] =
  {
    0xb1, 0x1d, 0xb0, 0x0c, 0xda, 0xf5, 0x32, 0x86, 0xd4, 0x48, 0x3f, 0x38, 0xcd,
    0x02, 0x78, 0x59, 0x48, 0x47, 0x7e, 0xd7, 0xeb, 0xc2, 0xad, 0x60, 0x90, 0x54,
    0x55, 0x1d, 0xa0, 0xab, 0x03, 0x59, 0x97, 0x8c, 0x61, 0x85, 0x17, 0x88, 0xaa,
    0x2e, 0xc3, 0x26, 0x79, 0x46, 0xd4, 0x40, 0xe8, 0x78
  };

/* sign_s */
const uint8_t sign_s_384[] =
  {
    0x16, 0x00, 0x78, 0x73, 0xc5, 0xb0, 0x60, 0x4c, 0xe6, 0x81, 0x12, 0xa8, 0xfe,
    0xe9, 0x73, 0xe8, 0xe2, 0xb6, 0xe3, 0x31, 0x9c, 0x68, 0x3a, 0x76, 0x2f, 0xf5,
    0x06, 0x5a, 0x07, 0x65, 0x12, 0xd7, 0xc9, 0x8b, 0x27, 0xe7, 0x4b, 0x78, 0x87,
    0x67, 0x10, 0x48, 0xac, 0x02, 0x7d, 0xf8, 0xcb, 0xf2
  };

/* Private function prototypes -----------------------------------------------*/
int32_t STM32_SHA256_HASH_DigestCompute(uint8_t* InputMessage,
                                        uint32_t InputMessageLength,
                                        uint8_t *MessageDigest,
                                        int32_t* MessageDigestLength);

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

  int32_t status = HASH_SUCCESS;

  ECDSAsignature_stt *sign = NULL;

  uint32_t InputLength = NULL;

  __IO int32_t param_ecc_counter = 0x00;

  const uint8_t * pub_x;
  const uint8_t * pub_y;
  const uint8_t * sign_r;
  const uint8_t * sign_s;
  const uint8_t * InputMessage;
  int32_t pub_x_size = 0x00;
  int32_t pub_y_size = 0x00;
  int32_t sign_r_size = 0x00;
  int32_t sign_s_size = 0x00;

  uint8_t MessageDigest[CRL_SHA256_SIZE];
  int32_t MessageDigestLength = 0;

  /* Proceed with ECC signature generation */
  EC_stt EC_st;

  /* structure to store the preallocated buffer for computation*/
  membuf_stt Crypto_Buffer;

  /* Actual preallocated buffer */
  uint8_t preallocated_buffer[3584];

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

  /* Toggle the green led before starting the algorithm */
  Led_Toggle(500);

  /* Enable CRC clock */
  __CRC_CLK_ENABLE();

  for (param_ecc_counter = 0; param_ecc_counter < 3; param_ecc_counter++)
  {
    switch (param_ecc_counter)
    {
      case 0:
        /* Initialize the ECC curve structure, with all the parameters */
        EC_st.pmA = P_192_a;
        EC_st.pmB = P_192_b;
        EC_st.pmP = P_192_p;
        EC_st.pmN = P_192_n;
        EC_st.pmGx = P_192_Gx;
        EC_st.pmGy = P_192_Gy;
        EC_st.mAsize = sizeof(P_192_a);
        EC_st.mBsize = sizeof(P_192_b);
        EC_st.mNsize = sizeof(P_192_n);
        EC_st.mPsize = sizeof(P_192_p);
        EC_st.mGxsize = sizeof(P_192_Gx);
        EC_st.mGysize = sizeof(P_192_Gy);
        pub_x = pub_x_192;
        pub_y = pub_y_192;
        sign_r = sign_r_192;
        sign_s = sign_s_192;
        InputMessage =  InputMessage_192;
        pub_x_size = sizeof(pub_x_192);
        pub_y_size = sizeof(pub_y_192);
        sign_r_size = sizeof(sign_r_192);
        sign_s_size = sizeof(sign_s_192);
        InputLength = sizeof(InputMessage_192);
        break;

      case 1:
        /* Initialize the ECC curve structure, with all the parameters */
        EC_st.pmA = P_256_a;
        EC_st.pmB = P_256_b;
        EC_st.pmP = P_256_p;
        EC_st.pmN = P_256_n;
        EC_st.pmGx = P_256_Gx;
        EC_st.pmGy = P_256_Gy;
        EC_st.mAsize = sizeof(P_256_a);
        EC_st.mBsize = sizeof(P_256_b);
        EC_st.mNsize = sizeof(P_256_n);
        EC_st.mPsize = sizeof(P_256_p);
        EC_st.mGxsize = sizeof(P_256_Gx);
        EC_st.mGysize = sizeof(P_256_Gy);
        pub_x = pub_x_256;
        pub_y = pub_y_256;
        sign_r = sign_r_256;
        sign_s = sign_s_256;
        InputMessage =  InputMessage_256;
        pub_x_size = sizeof(pub_x_256);
        pub_y_size = sizeof(pub_y_256);
        sign_r_size = sizeof(sign_r_256);
        sign_s_size = sizeof(sign_s_256);
        InputLength = sizeof(InputMessage_256);
        break;

      case 2:
        /* Initialize the ECC curve structure, with all the parameters */
        EC_st.pmA = P_384_a;
        EC_st.pmB = P_384_b;
        EC_st.pmP = P_384_p;
        EC_st.pmN = P_384_n;
        EC_st.pmGx = P_384_Gx;
        EC_st.pmGy = P_384_Gy;
        EC_st.mAsize = sizeof(P_384_a);
        EC_st.mBsize = sizeof(P_384_b);
        EC_st.mNsize = sizeof(P_384_n);
        EC_st.mPsize = sizeof(P_384_p);
        EC_st.mGxsize = sizeof(P_384_Gx);
        EC_st.mGysize = sizeof(P_384_Gy);
        pub_x = pub_x_384;
        pub_y = pub_y_384;
        sign_r = sign_r_384;
        sign_s = sign_s_384;
        InputMessage =  InputMessage_384;
        pub_x_size = sizeof(pub_x_384);
        pub_y_size = sizeof(pub_y_384);
        sign_r_size = sizeof(sign_r_384);
        sign_s_size = sizeof(sign_s_384);
        InputLength = sizeof(InputMessage_384);
        break;

      default:
        continue;
    }

    /* First hash the message to have a valid digest that will be signed through ECDSA */
    status = STM32_SHA256_HASH_DigestCompute((uint8_t*)InputMessage,
             InputLength,
             (uint8_t*)MessageDigest,

             &MessageDigestLength);
    if (status == HASH_SUCCESS)
    {
      /* We prepare the memory buffer strucure */
      Crypto_Buffer.pmBuf =  preallocated_buffer;
      Crypto_Buffer.mUsed = 0;
      Crypto_Buffer.mSize = sizeof(preallocated_buffer);

      /* Init the Elliptic Curve, passing the required memory */
      /* Note: This is not a temporary buffer, the memory inside EC_stt_buf is linked to EC_st *
         As long as there's need to use EC_st the content of EC_stt_buf should not be altered */
      status = ECCinitEC(&EC_st, &Crypto_Buffer );

      if (status == ECC_SUCCESS)
      {
        /* EC is initialized, now prepare to import the public key. First, allocate a point */
        ECpoint_stt *PubKey = NULL;

        status = ECCinitPoint(&PubKey, &EC_st, &Crypto_Buffer);

        if (status == ECC_SUCCESS)
        {
          /* Point is initialized, now import the public key */
          ECCsetPointCoordinate(PubKey, E_ECC_POINT_COORDINATE_X, pub_x, pub_x_size);
          ECCsetPointCoordinate(PubKey, E_ECC_POINT_COORDINATE_Y, pub_y, pub_y_size);

          /* Try to validate the Public Key. */
          status = ECCvalidatePubKey(PubKey, &EC_st, &Crypto_Buffer);
          if (status == ECC_SUCCESS)
          {

            /* Public Key is validated, Initialize the signature object */
            status = ECDSAinitSign(&sign, &EC_st, &Crypto_Buffer);

            if (status == ECC_SUCCESS)
            {
              ECDSAverifyCtx_stt verctx;

              /* Import the signature values */
              ECDSAsetSignature(sign, E_ECDSA_SIGNATURE_R_VALUE, sign_r, sign_r_size);
              ECDSAsetSignature(sign, E_ECDSA_SIGNATURE_S_VALUE, sign_s, sign_s_size);

              /* Prepare the structure for the ECDSA signature verification */
              verctx.pmEC = &EC_st;
              verctx.pmPubKey = PubKey;

              /* Verify it */
              status = ECDSAverify(MessageDigest, MessageDigestLength, sign, &verctx, &Crypto_Buffer);

              if (status == SIGNATURE_VALID )
              {
                /* Signature has been validated, free our ECC objects */
                ECDSAfreeSign(&sign, &Crypto_Buffer);
                ECCfreePoint(&PubKey, &Crypto_Buffer);
                ECCfreeEC(&EC_st, &Crypto_Buffer);


              }
              else
              {

                /* In case of ECC verification is not valid. Possible return values are:
                 * MATH_ERR_INTERNAL, ECC_ERR_BAD_PARAMETER, ECC_ERR_BAD_CONTEXT, 
                 * ECC_ERR_MISSING_EC_PARAMETER, MATH_ERR_BIGNUM_OVERFLOW, SIGNATURE_INVALID
                 */

                Error_Handler();

              }
            }
            else
            {
              /* In case of ECC signature is not valid. Possible return values are:
               * ECC_ERR_BAD_PARAMETER, ECC_ERR_BAD_CONTEXT, ECC_ERR_MISSING_EC_PARAMETER
               * MATH_ERR_INTERNAL, MATH_ERR_BIGNUM_OVERFLOW, RNG_ERR_INTERNAL, RNG_ERR_UNINIT_STATE           
               */

              Error_Handler();
            }
          }
          else
          {
            /* In case of corrupted pub key or b parameter:
             * ECC_ERR_BAD_PARAMETER, ECC_ERR_BAD_CONTEXT, ECC_ERR_BAD_PUBLIC_KEY, 
             * ERR_MEMORY_FAIL, ECC_ERR_MISSING_EC_PARAMETER            
             */

            Error_Handler();

          }

        }
        else
        {
          /* In case of ECC initialize PubKey is failed. Possible return values are :
           * ECC_ERR_BAD_PARAMETER, ECC_ERR_BAD_CONTEXT, ERR_MEMORY_FAIL
           */

          Error_Handler();
        }
      }
      else
      {
        /* In case of Init the Elliptic Curve is failed. Possible return values are:
         * ECC_ERR_BAD_PARAMETER, ECC_ERR_BAD_CONTEXT, ERR_MEMORY_FAIL, MATH_ERR_INTERNAL
         */

        Error_Handler();
      }
    }
    else
    {

      /* In case of hash not success possible values of status:
       * HASH_ERR_BAD_PARAMETER, HASH_ERR_BAD_CONTEXT, HASH_ERR_BAD_OPERATION
       */

      Error_Handler();
    }
  }

  /* Turn on the green led in case of ECC Signature Verification operations are successful */
  HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_SET);
  while (1)
  {}


}

/**
  * @brief  SHA256 HASH digest compute example.
  * @param  InputMessage: pointer to input message to be hashed.
  * @param  InputMessageLength: input data message length in byte.
  * @param  MessageDigest: pointer to output parameter that will handle message digest
  * @param  MessageDigestLength: pointer to output digest length.
  * @retval error status: can be HASH_SUCCESS if success or one of
  *         HASH_ERR_BAD_PARAMETER, HASH_ERR_BAD_CONTEXT,
  *         HASH_ERR_BAD_OPERATION if error occured.
  */
int32_t STM32_SHA256_HASH_DigestCompute(uint8_t* InputMessage, uint32_t InputMessageLength,
                                        uint8_t *MessageDigest, int32_t* MessageDigestLength)
{
  SHA256ctx_stt P_pSHA256ctx;
  uint32_t error_status = HASH_SUCCESS;

  /* Set the size of the desired hash digest */
  P_pSHA256ctx.mTagSize = CRL_SHA256_SIZE;

  /* Set flag field to default value */
  P_pSHA256ctx.mFlags = E_HASH_DEFAULT;

  error_status = SHA256_Init(&P_pSHA256ctx);

  /* check for initialization errors */
  if (error_status == HASH_SUCCESS)
  {
    /* Add data to be hashed */
    error_status = SHA256_Append(&P_pSHA256ctx,
                                 InputMessage,
                                 InputMessageLength);

    if (error_status == HASH_SUCCESS)
    {
      /* retrieve */
      error_status = SHA256_Finish(&P_pSHA256ctx, MessageDigest, MessageDigestLength);
    }
  }

  return error_status;
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
