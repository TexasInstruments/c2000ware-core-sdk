//###########################################################################
//
// FILE:   boostxl_afe031_F2837xD_Sci.c
//
// TITLE:  F2837xD SCI Initialization & Support Functions.
//
//###########################################################################
//
// 
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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
//###########################################################################

//
// Included Files
//
#include "F28x_Project.h"
#include "boostxl_afe031_F2837xD_Sci.h"

//
// Version information string returned by "vi" command
//
#define VERSION_INFO "F2837xD v19.02.00\0"

//
// Globals
//
char cmdBuf[] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
int cmdIdx = 0;
int cmdInit = 1;

//
// scia_fifo_init - Initialize the SCI FIFO
//
void scia_fifo_init()
{
    SciaRegs.SCIFFTX.all = 0xE040;
    SciaRegs.SCIFFRX.all = 0x2044;
    SciaRegs.SCIFFCT.all = 0x0;
}

//
// scia_gpio_init - Initialize the SCI GPIO
//
void scia_gpio_init()
{
   EALLOW;
   GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 3;
   GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 3;
   GpioCtrlRegs.GPBGMUX1.bit.GPIO42 = 3;
   GpioCtrlRegs.GPBGMUX1.bit.GPIO43 = 3;
   EDIS;
}

//
//  scia_port_init - Initialize the SCI Port
//
void scia_port_init()
{
    //
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function
    //

    SciaRegs.SCICCR.all = 0x0007;   // 1 stop bit,  No loopback
                                    // No parity,8 char bits,
                                    // async mode, idle-line protocol
    SciaRegs.SCICTL1.all = 0x0003;  // enable TX, RX, internal SCICLK,
                                    // Disable RX ERR, SLEEP, TXWAKE
    SciaRegs.SCICTL2.all = 0x0003;
    SciaRegs.SCICTL2.bit.TXINTENA = 1;
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1;
    //
    // 230400 baud @LSPCLK = 50MHz (200 MHz SYSCLK)
    //
    SciaRegs.SCIHBAUD.all = 0;
    SciaRegs.SCILBAUD.all = 53;
    SciaRegs.SCICTL1.all = 0x0023;  // Relinquish SCI from Reset
}

//
//  scia_port_init - Initialize SCIA GPIO, FIFO and Port
//
void scia_init()
{
    scia_gpio_init();
    scia_fifo_init();
    scia_port_init();
    scia_cmd_reset();
    scia_msg(">> \0");
}

//
// scia_xmit - Transmit a character from the SCI
//
void scia_xmit(int a)
{
    while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}
    SciaRegs.SCITXBUF.all =a;
}

//
// scia_msg - Transmit message via SCIA
//
void scia_msg(char *msg)
{
    int i = 0;
    while(msg[i] != '\0')
    {
        scia_xmit(msg[i]);
        i++;
    }
}

//
// scia_service - SCIA service routine
//
void scia_service()
{
    if (cmdInit)
    {
		//
        // IMPORTANT: Wait a second to ensure
        // host PC has enumerated the LaunchPad
        // COM port before SCI is initialized!
        //
        DELAY_US(1000000);
        scia_init();
        cmdInit = 0;
    }

    while(SciaRegs.SCIFFRX.bit.RXFFST != 0)
    {
        int reset = 0;
        long num = 0;
        char c = SciaRegs.SCIRXBUF.all;
        if (c == 0x0d)
        {
            //Parse and service command
            int command = scia_cmd_parser(cmdBuf, &num);
            switch (command)
            {
                case CMD_GET_VER_INFO:
                    scia_msg("\r\n\0");
                    scia_msg(VERSION_INFO);
                    scia_msg(" Serial Terminal\r\n>> \0");
                    break;
                case CMD_SET_MARK_GAIN:
                    GAIN_MARK_x1024 = num;
                    scia_msg("\r\nACK\r\n>> \0");
                    break;
                case CMD_GET_MARK_GAIN:
                    scia_msg("\r\n\0");
                    scia_msg(scia_num2str(GAIN_MARK_x1024));
                    scia_msg("\r\n>> \0");
                    break;
                case CMD_GET_SPACE_GAIN:
                    scia_msg("\r\n\0");
                    scia_msg(scia_num2str(GAIN_SPACE_x1024));
                    scia_msg("\r\n>> \0");
                    break;
                case CMD_SET_SPACE_GAIN:
                    GAIN_SPACE_x1024 = num;
                    scia_msg("\r\nACK\r\n>> \0");
                    break;
                case CMD_GET_DAC_OFFSET:
                    scia_msg("\r\n\0");
                    scia_msg(scia_num2str(DAC_CODE_OFFSET));
                    scia_msg("\r\n>> \0");
                    break;
                case CMD_SET_DAC_OFFSET:
                    DAC_CODE_OFFSET = num;
                    scia_msg("\r\nACK\r\n>> \0");
                    break;
                case CMD_GET_CURRENT_CNT:
                    scia_msg("\r\n\0");
                    scia_msg(scia_num2str(intCurrent));
                    scia_msg("\r\n>> \0");
                    break;
                case CMD_SET_CURRENT_CNT:
                    intCurrent = num;
                    scia_msg("\r\nACK\r\n>> \0");
                    break;
                case CMD_GET_THERMAL_CNT:
                    scia_msg("\r\n\0");
                    scia_msg(scia_num2str(intThermal));
                    scia_msg("\r\n>> \0");
                    break;
                case CMD_SET_THERMAL_CNT:
                    intThermal = num;
                    scia_msg("\r\nACK\r\n>> \0");
                    break;
                case CMD_GET_USER_TM:
                    scia_msg("\r\n\0");
                    scia_msg(scia_num2str(tmUser));
                    scia_msg("\r\n>> \0");
                    break;
                case CMD_SET_USER_TM:
                    tmUser = num;
                    scia_msg("\r\nACK\r\n>> \0");
                    break;
                case CMD_GET_HELP:
                    scia_msg("\r\n\0");
                    scia_msg("Get Command Help: h or ?\r\n\0");
                    scia_msg("Get Version Info: v\r\n\0");
                    scia_msg("Get Mark Gain: m\r\n\0");
                    scia_msg("Set Mark Gain: m=value\r\n\0");
                    scia_msg("Get Space Gain: s\r\n\0");
                    scia_msg("Set Space Gain: s=value\r\n\0");
                    scia_msg("Get DAC Offset: o\r\n\0");
                    scia_msg("Set DAC Offset: o=value\r\n\0");
                    scia_msg("Get Overcurrent Count: c\r\n\0");
                    scia_msg("Set Overcurrent Count: c=value\r\n\0");
                    scia_msg("Get Thermal Shutdown Count: t\r\n\0");
                    scia_msg("Set Thermal Shutdown Count: t=value\r\n\0");
                    scia_msg("Get User Test Mode: u\r\n\0");
                    scia_msg("Set User Test Mode: u=value\r\n\0");
                    scia_msg("Value  Test Mode\r\n\0");
                    scia_msg("  0    W1,W1,W1 (SunSpec Permission to Operate)\r\n\0");
                    scia_msg("  1    W0,W0,W0 (SunSpec Accelerated Shutdown)\r\n\0");
                    scia_msg("  2    Continuous Mark\r\n\0");
                    scia_msg("  3    Continuous Space\r\n\0");
                    scia_msg("  4    Continuous W1\r\n\0");
                    scia_msg("  5    Continuous W0\r\n\0");
                    scia_msg("  6    Power Amp Shutdown\r\n\0");
                    scia_msg("  7    Power Amp Enable\r\n\0");
                    scia_msg(">> \0");
                    break;
                default:
                    scia_msg("\r\nNAK\r\n>> \0");
                    break;
            }
            reset = 1;
        }
        else if (cmdIdx >= sizeof(cmdBuf))
        {
            reset = 1;
        }
        else
        {
            cmdBuf[cmdIdx++] = c;
        }
        if (reset)
        {
            scia_cmd_reset();
        }
    }
}

//
// scia_cmd_reset - Reset command buffer
//
void scia_cmd_reset()
{
    for (cmdIdx = 0; cmdIdx < sizeof(cmdBuf); cmdIdx++)
    {
        cmdBuf[cmdIdx] = '\0';
    }
    cmdIdx = 0;
}

//
// scia_parser - SCIA command parser
//
int scia_cmd_parser(char* cmd, long* num)
{
    if ((cmd[0] == 'h') || (cmd[0] == '?'))
    {
        if (cmd[1] == '\0')
        {
            return CMD_GET_HELP;
        }
    }
    else if (cmd[0] == 'v')
    {
        if (cmd[1] == '\0')
        {
            return CMD_GET_VER_INFO;
        }
    }
    else if (cmd[0] == 'm')
    {
        if (cmd[1] == '\0')
        {
            return CMD_GET_MARK_GAIN;
        }
        else if (cmd[1] == '=')
        {
            if (scia_str2num(&cmd[2], num))
            {
                return CMD_SET_MARK_GAIN;
            }
        }
    }
    else if (cmd[0] == 's')
    {
        if (cmd[1] == '\0')
        {
            return CMD_GET_SPACE_GAIN;
        }
        else if (cmd[1] == '=')
        {
            if (scia_str2num(&cmd[2], num))
            {
                return CMD_SET_SPACE_GAIN;
            }
        }
    }
    else if (cmd[0] == 'o')
    {
        if (cmd[1] == '\0')
        {
            return CMD_GET_DAC_OFFSET;
        }
        else if (cmd[1] == '=')
        {
            if (scia_str2num(&cmd[2], num))
            {
                return CMD_SET_DAC_OFFSET;
            }
        }
    }
    else if (cmd[0] == 'c')
    {
        if (cmd[1] == '\0')
        {
            return CMD_GET_CURRENT_CNT;
        }
        else if (cmd[1] == '=')
        {
            if (scia_str2num(&cmd[2], num))
            {
                return CMD_SET_CURRENT_CNT;
            }
        }
    }
    else if (cmd[0] == 't')
    {
        if (cmd[1] == '\0')
        {
            return CMD_GET_THERMAL_CNT;
        }
        else if (cmd[1] == '=')
        {
            if (scia_str2num(&cmd[2], num))
            {
                return CMD_SET_THERMAL_CNT;
            }
        }
    }
    else if (cmd[0] == 'u')
    {
        if (cmd[1] == '\0')
        {
            return CMD_GET_USER_TM;
        }
        else if (cmd[1] == '=')
        {
            if (scia_str2num(&cmd[2], num))
            {
                return CMD_SET_USER_TM;
            }
        }
    }

    return CMD_UNKNOWN;
}

//
// scia_str2num - SCIA string to number utility
//
int scia_str2num(char* str, long* num)
{
    int dig[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int i = 0;
    while (1)
    {
        char c = str[i];
        if (c =='\0')
        {
            break;
        }
        else if (i >= sizeof(dig))
        {
            return 0;
        }
        dig[i] = (int)c - 0x30;
        if ((dig[i] < 0) || (dig[i] > 9))
        {
            return 0;
        }
        i++;
    }

    *num = 0;
    int n = i;
    for (i = 0; i < n; i++)
    {
        long pow10 = scia_pow10(n-i-1);
        *num = *num + (long)dig[i]*pow10;
    }

    return n;
}

//
// scia_num2str - SCIA number to string utility
//
char* scia_num2str(long num)
{
    static char rspBuf[80];

    int n = 9;
    if (num < 10)               n = 1;
    else if (num < 100)         n = 2;
    else if (num < 1000)        n = 3;
    else if (num < 10000)       n = 4;
    else if (num < 100000)      n = 5;
    else if (num < 1000000)     n = 6;
    else if (num < 10000000)    n = 7;
    else if (num < 100000000)   n = 8;

    long rem = num;
    int i;
    for(i = 0; i < n; i++)
    {
        long pow10 = scia_pow10(n-i-1);
        long dig = rem/pow10;
        rspBuf[i] = (char)dig + 0x30;
        rem -= (dig * pow10);
    }

    rspBuf[i] = '\0';

    return rspBuf;
}

//
// scia_pow10 - SCIA power of 10 utility
//
long scia_pow10(long pow)
{
    long pow10;
    switch (pow)
    {
        case 0:     pow10 = 1;            break;
        case 1:     pow10 = 10;           break;
        case 2:     pow10 = 100;          break;
        case 3:     pow10 = 1000;         break;
        case 4:     pow10 = 10000;        break;
        case 5:     pow10 = 100000;       break;
        case 6:     pow10 = 1000000;      break;
        case 7:     pow10 = 10000000;     break;
        case 8:     pow10 = 100000000;    break;
        default:    pow10 = 1000000000;   break;
    }
    return pow10;
}
