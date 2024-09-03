/*
 * Copyright (c) 2020 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
 
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

//
// Extract and grab a u16 number's bytes values
//
void u16toBytes(uint16_t u16, uint16_t* byteArray)
{
    uint16_t *bytePtr = &u16;
    byteArray[0] = (*bytePtr & 0x00FF);
    byteArray[1] = (*bytePtr >> 8);
}

//
// Extract and grab a i16 number's bytes values
//
void i16toBytes(int16_t i16, uint16_t* byteArray)
{
    uint16_t *bytePtr = (uint16_t *)&i16;
    byteArray[0] = (*bytePtr & 0x00FF);
    byteArray[1] = (*bytePtr >> 8);
}

//
// Extract and grab a u32 number's bytes values
//
void u32toBytes(uint32_t u32, uint16_t* byteArray)
{
    uint16_t *bytePtr = (uint16_t *)&u32;
    byteArray[0] = (*bytePtr & 0x00FF);
    byteArray[1] = (*bytePtr >> 8);
    bytePtr += 1;
    byteArray[2] = (*bytePtr & 0x00FF);
    byteArray[3] = (*bytePtr >> 8);
}

//
// Extract and grab a i32 number's bytes values
//
void i32toBytes(int32_t i32, uint16_t* byteArray)
{
    uint16_t *bytePtr = (uint16_t *)&i32;
    byteArray[0] = (*bytePtr & 0x00FF);
    byteArray[1] = (*bytePtr >> 8);
    bytePtr += 1;
    byteArray[2] = (*bytePtr & 0x00FF);
    byteArray[3] = (*bytePtr >> 8);
}

//
// Extract and grab a f32 number's bytes values
//
void f32toBytes(float f32, uint16_t* byteArray)
{
    uint16_t *bytePtr = (uint16_t *)&f32;
    byteArray[0] = (*bytePtr & 0x00FF);
    byteArray[1] = (*bytePtr >> 8);
    bytePtr += 1;
    byteArray[2] = (*bytePtr & 0x00FF);
    byteArray[3] = (*bytePtr >> 8);
}

//
// 10 to the power of "pow"
//
uint32_t tenToPow(uint32_t pow)
{
    uint32_t result = 1;
    for (; pow > 0; pow--)
    {
        result = result * 10;
    }
    return result;
}

//
// Converts a int number into a string
//
void itoa(int32_t value, char *result)
{
    char *ptr = result, *ptr1 = result, tmp_char;
    uint32_t tmp_value;

    tmp_value = labs(value);
    do {
        *ptr++ = "0123456789"[tmp_value % 10];
        tmp_value /= 10;
    } while (tmp_value);

    // Apply negative sign
    if (value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--   = *ptr1;
        *ptr1++  = tmp_char;
    }
}

//
// Converts an unsigned number into a string
//
void utoa(uint32_t value, char *result)
{
    char *ptr = result, *ptr1 = result, tmp_char;
    do {
        *ptr++ = "0123456789"[value % 10];
        value /= 10;
    } while (value);

    *ptr-- = '\0';

    //
    // Reverse
    //
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--   = *ptr1;
        *ptr1++  = tmp_char;
    }
}

//
// Converts a float number into a string
//
void ftoa(float value, char* result, int numDecimal)
{
    uint16_t ipartLen;
    uint16_t fpartNumDig = 0;
    uint16_t fpartZeroPadI = 0;
    uint16_t fpartZeroPadCount = 0;
    uint32_t tens = 1;

    //
    // Extract integer part
    //
    int32_t ipart = (int32_t)value;

    //
    // Extract floating part
    //
    float fpart = value - (float)ipart;
    if (fpart < 0){
        fpart = -1.0*fpart;
    }

    uint32_t fpartUint = fpart * (float)tenToPow(numDecimal);

    for (fpartNumDig = 0; fpartNumDig <= numDecimal; fpartNumDig++)
    {
        if (!(fpartUint/tens))
        {
            break;
        }
        tens *= 10;
    }
    fpartZeroPadCount = numDecimal - fpartNumDig;

    // convert integer part to string
    itoa(ipart, result);
    ipartLen = strlen(result);

    // check for display option after point
    if (numDecimal != 0) {
        result[ipartLen] = '.'; // add dot
        for (fpartZeroPadI = 0; fpartZeroPadI < fpartZeroPadCount; fpartZeroPadI++)
        {
            result[++ipartLen] = '0';
        }
        if (fpartNumDig){
            utoa(fpartUint, result + ipartLen + 1);
        }
    }
}

