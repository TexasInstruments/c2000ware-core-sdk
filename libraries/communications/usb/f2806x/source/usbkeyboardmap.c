//#############################################################################
// FILE: usbkeyboardmap.c
// TITLE: This file holds the table to enable USB keyboard usage
//#############################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "include/usblib.h"
#include "include/usbhid.h"

//*****************************************************************************
//
// This is the array that hold the unshifted and shifted ASCII character for
// each usage ID.
//
//*****************************************************************************
const uint8_t g_pui8KeyBoardMap[USBH_HID_MAX_USAGE][2] =
{
//
//  Usage ID to character mapping                      Usage ID     CAPS Lock
//
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 0 - 3        0
    {'a', 'A'}, {'b', 'B'}, {'c', 'C'}, {'d', 'D'}, // 4 - 7        f
    {'e', 'E'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'}, // 8 - 11       f
    {'i', 'I'}, {'j', 'J'}, {'k', 'K'}, {'l', 'L'}, // 12 - 15      f
    {'m', 'M'}, {'n', 'N'}, {'o', 'O'}, {'p', 'P'}, // 16 - 19      f
    {'q', 'Q'}, {'r', 'R'}, {'s', 'S'}, {'t', 'T'}, // 20 - 23      f
    {'u', 'U'}, {'v', 'V'}, {'w', 'W'}, {'x', 'X'}, // 24 - 27      f
    {'y', 'Y'}, {'z', 'Z'}, {'1', '!'}, {'2', '@'}, // 28 - 31      3

    {'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'}, // 32 - 35      0
    {'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'}, // 36 - 39      0
    {'\n', '\n'}, {0, 0},   {0, 0},   {'\t', '\t'}, // 40 - 43      0
    {' ', ' '}, {'-', '_'}, {'=', '+'}, {'[', '{'}, // 44 - 47      0
    {']', '}'}, {'\\', '|'},{'`', '~'}, {';', ':'}, // 48 - 51      0
    {'\'', '"'}, {'`', '~'}, {',', '<'}, {'.', '>'},// 52 - 55      0
    {'/', '?'}, {0, 0},     {0, 0},     {0, 0},     // 56 - 59      0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 60 - 63      0

    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 64 - 67      0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 68 - 71      0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 72 - 75      0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 76 - 79      0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 80 - 83      0
    {'/', '/'}, {'*', '*'}, {'-', '-'}, {'+', '+'}, // 84 - 87      0
    {'\n', '\n'}, {'1', 0}, {'2', 0},   {'3', 0},   // 88 - 91      0
    {'4', 0},   {'5', 0},   {'6', 0},   {'7', 0},   // 92 - 95      0

    {'8', 0},   {'9', 0},   {'0', 0},   {'.', 0},   // 96 - 99      0
    {'\\', '|'},{0, 0},     {0, 0},     {'=', '+'}, // 100 - 103    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 104 - 107    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 108 - 111    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 112 - 115    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 116 - 119    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 120 - 123    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 124 - 127    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 128 - 131    0

    {0, 0},     {',', ','}, {'=', '='}, {0, 0},     // 132 - 135    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 136 - 139    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 140 - 143    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 144 - 147    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 148 - 151    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 152 - 155    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 156 - 159    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 160 - 163    0

    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 164 - 167    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 168 - 171    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 172 - 175    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 174 - 179    0
    {0, 0},     {0, 0},     {'(', '('}, {')', ')'}, // 180 - 183    0
    {'{', '{'}, {'}', '}'}, {'\t', '\t'}, {0, 0},   // 184 - 187    0
    {'A', 'A'}, {'B', 'B'}, {'C', 'C'}, {'D', 'D'}, // 188 - 191    0
    {'E', 'E'}, {'F', 'F'}, {0, 0},     {'^', '^'}, // 192 - 195    0

    {'%', '%'}, {'<', '<'}, {'>', '>'}, {'&', '&'}, // 196 - 199    0
    {'&', '&'}, {'|', '|'}, {'|', '|'}, {':', ':'}, // 200 - 203    0
    {'#', '#'}, {' ', ' '}, {'@', '@'}, {'!', '!'}, // 204 - 207    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 208 - 211    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 212 - 215    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 216 - 219    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 220 - 223    0

    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 224 - 227    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 228 - 231    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 232 - 235    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 236 - 239    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 240 - 243    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 244 - 247    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 248 - 251    0
    {0, 0},     {0, 0},     {0, 0},     {0, 0},     // 252 - 255    0
};

//*****************************************************************************
//
// This is the structure that defines the mapping of USB usage IDs to ASCII
// values for printing.
//
//*****************************************************************************
const tHIDKeyboardUsageTable g_sUSKeyboardMap =
{
    //
    // One byte per character.
    //
    1,
    //
    // Packed bit array of usages codes that are effected by Caps Lock state.
    //
    {
        0x3ffffff0,     // Alpha characters are only one affected by CAPS LOCK
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
    },
    //
    // The large table of the direct mapping of usage id's to ascii characters.
    //
    (void *)g_pui8KeyBoardMap
};
