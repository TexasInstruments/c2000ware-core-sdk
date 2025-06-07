//#############################################################################
//
// FILE:   clb_ex32_lp589x_api.c
//
// TITLE:  Simple APIs for configuring the LP5891 LED driver.
//
//#############################################################################
// $TI Release: $
// 
// 
// C2000Ware v5.05.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

//
// Included Files
//
#include <clb_ex32_ccsi_hal.h>
#include <clb_ex32_ccsi_socket.h>
#include <clb_ex32_lp5891.h>
#include <clb_ex32_lp589x_api.h>

//
// Globals
//
uint16_t vsyncDone;
uint16_t data[MAX_DATA_LENGTH];

/* Function Name: setData
 *
 * Purpose: Set data send buffer.
 *
 * Parameters:
 * data -> The pointer of data send buffer.
 * high, mid, low -> Data bytes, MSB first.
 * bias -> Bias in the date send buffer.
 *
 */
void setData(uint16_t *data, uint16_t high, uint16_t mid, uint16_t low, uint16_t bias)
{
    data[0 + bias] = high;
    data[1 + bias] = mid;
    data[2 + bias] = low;
}

/* Function Name: LED_Set_Chip_Index
 *
 * Purpose: Set Chip Index.
 *
 * Parameters:
 *
 */
void LED_Set_Chip_Index(unsigned int checkResponse)
{
    uint16_t data_int[1] = {0x0000};

    CCSI_write(W_CHIP_INDEX, data_int, 0, checkResponse);
}

/* Function Name: LED_Write_RGB_Custom_ALL
 *
 * Purpose: Send RGB data to all LED drivers.
 *
 * Parameters:
 * r_value -> Brightness for red-channels
 * g_value -> Brightness for green-channels
 * b_value -> Brightness for blue-channels
 *
 */
void LED_Write_RGB_Custom_ALL(uint16_t r_value, uint16_t g_value, uint16_t b_value)
{
    uint16_t line_idx = 0;
    uint16_t ch_idx = 0;
    uint16_t chip_idx = 0;

    for(line_idx = 0; line_idx < TOTAL_SCAN_LINES; line_idx++){
        for(ch_idx = 0 ; ch_idx < RGB_CHANNEL_CNT ; ch_idx++){
            for(chip_idx = 0; chip_idx < CASCADED_UNITS; chip_idx++){
                // Ensure there are different data in case transmission efficiency is fast enough to overwrite before all data is sent
                setData(&data[0],
                        b_value,   // B
                        g_value,   // G
                        r_value,   // R
                        (chip_idx << 1) + chip_idx);
            }
            CCSI_write(W_SRAM, &data[0], (CASCADED_UNITS << 1) + CASCADED_UNITS, FALSE);
        }
    }
}

/* Function Name: LED_Write_Black_ALL
 *
 * Purpose: Set all channels to off
 *
 * Parameters:
 *
 */
void LED_Write_Black_ALL(void)
{
    LED_Write_RGB_Custom_ALL(0x0000, 0x0000, 0x0000);
}

/* Function Name: LED_Write_White_ALL
 *
 * Purpose: Set all channels to maximum brightness
 *
 * Parameters:
 *
 */
void LED_Write_White_ALL(void)
{
    LED_Write_RGB_Custom_ALL(0xFFFF, 0xFFFF, 0xFFFF);
}

/* Function Name: LED_Write_Red_ALL
 *
 * Purpose: Set all red-channels to maximum brightness
 *
 * Parameters:
 *
 */
void LED_Write_Red_ALL(void)
{
    LED_Write_RGB_Custom_ALL(0xFFFF, 0x0000, 0x0000);
}

/* Function Name: LED_Write_Green_ALL
 *
 * Purpose: Set all green-channels to maximum brightness
 *
 * Parameters:
 *
 */
void LED_Write_Green_ALL(void)
{
    LED_Write_RGB_Custom_ALL(0x0000, 0xFFFF, 0x0000);
}

/* Function Name: LED_Write_Blue_ALL
 *
 * Purpose: Set all blue-channels to maximum brightness
 *
 * Parameters:
 *
 */
void LED_Write_Blue_ALL(void)
{
    LED_Write_RGB_Custom_ALL(0x0000, 0x0000, 0xFFFF);
}

/* Function Name: LED_Write_Reg_Broadcast
 *
 * Purpose: Send same data to all FC register(s) in the chain.
 *
 * Parameters:
 * fc_reg -> First FC register to be written.
 * dataBytes -> Data bytes, MSB first.
 * length -> Length of data bytes.
 *
 */
void LED_Write_Reg_Broadcast(uint16_t fc_reg, uint16_t data2, uint16_t data1, uint16_t data0, unsigned int checkResponse)
{
    uint16_t data_int[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    
    setData(data_int, data2, data1, data0, 0);
    CCSI_write(fc_reg, data_int, 3, checkResponse);
}

/* Function Name: sendSYNCinternal
 *
 * Purpose: Send VSYNC command to display next frame.
 *
 * Parameters:
 * waitForINT -> When TRUE wait for interrupt before sending VSYNC command
 *
 */
void sendSYNCinternal(unsigned int waitForINT)
{
    uint16_t data_int[1] = {0x00};
    uint16_t vsync_local = 0;

    // VSYNC needs to be send before next frame data can be send
    if(waitForINT == TRUE) {
        while(!vsync_local) {
            vsync_local = vsyncDone;
        }
    }

    // SYNC display at a fixed FPS
    CCSI_write_sync(W_VSYNC, data_int, 0);

    // Send simultaneous VSYNC
    CCSI_HAL_clbSyncTransferStart();

    // Wait for CLB to finish any ongoing transfer
    while(clbXmtDone == 0){}

    // Reset VSYNC
    vsyncDone = 0;
}

/* Function Name: sendSYNC
 *
 * Purpose: Send VSYNC command but wait for interrupt to control timing.
 *
 * Parameters:
 *
 */
void sendSYNC()
{
    sendSYNCinternal(TRUE);
}

/* Function Name: sendSYNCnoWait
 *
 * Purpose: Send VSYNC command directly.
 *
 * Parameters:
 *
 */
void sendSYNCnoWait()
{
    sendSYNCinternal(FALSE);
}

//
// End of File
//
