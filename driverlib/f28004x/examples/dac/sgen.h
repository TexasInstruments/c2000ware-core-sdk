//######################################################################################
//
// File name   :   SGEN.H
//
// Originator    : Advanced Embedded Control (AEC)
//                 Texas Instruments Inc.
//
// Description:
// Header file containing  object definitions, prototype declaration and
// default object initializers for Signal Generator Modules
//
//#############################################################################
// $TI Release: F28004x Support Library v4.03.00.00 $
// $Release Date: 02-02-2023 $
// $Copyright:
// Copyright (C) 2021 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef __SGEN_H__

#define __SGEN_H__
#define NULL    0

typedef struct {
        unsigned int freq;
        unsigned int step_max;
        unsigned int alpha;
        int gain;
        int offset;
        int out;
        void (*calc)(void *);
        }SGENT_1;

#define SGENT_1_DEFAULTS    { 5369,\
        1000,\
        0,\
        0x7fff,\
        0,\
        0,\
        (void (*)(void *))SGENT_1_calc}

typedef struct {
        unsigned int freq;
        unsigned int step_max;
        unsigned int alpha;
        int gain;
        int offset;
        int out;
        void (*calc)(void *);
        }SGENTI_1;

#define SGENTI_1_DEFAULTS   { 5369,\
        1000,\
        0,\
        0x7fff,\
        0,\
        0,\
        (void (*)(void *))SGENTI_1_calc}

typedef struct {
        unsigned int freq;
        unsigned int step_max;
        unsigned int alpha;
        int gain;
        int offset;
        int out1;
        unsigned int phase;
        int out2;
        void (*calc)(void *);
        }SGENT_2;

#define SGENT_2_DEFAULTS    { 5369,\
        1000,\
        0,\
        0x7fff,\
        0,\
        0,\
        0x4000,\
        0,\
        (void (*)(void *))SGENT_2_calc}

typedef struct {
        unsigned int freq;
        unsigned int step_max;
        unsigned int alpha;
        int gain;
        int offset;
        int out1;
        unsigned int phase;
        int out2;
        void (*calc)(void *);
        }SGENTI_2;

#define SGENTI_2_DEFAULTS   { 5369,\
        1000,\
        0,\
        0x7fff,\
        0,\
        0,\
        0x4000,\
        0,\
        (void (*)(void *))SGENTI_2_calc}


typedef struct {
        unsigned int freq;
        unsigned int step_max;
        unsigned int alpha;
        int gain;
        int offset;
        int out1;
        int out2;
        int out3;
        void (*calc)(void *);
        }SGENT_3;

#define SGENT_3_DEFAULTS    { 5369,\
        1000,\
        0,\
        0x7fff,\
        0,\
        0,\
        0,\
        0,\
        (void (*)(void *))SGENT_3_calc}

typedef struct {
        unsigned int freq;
        unsigned int step_max;
        unsigned int alpha;
        int gain;
        int offset;
        int out1;
        int out2;
        int out3;
        void (*calc)(void *);
        }SGENTI_3;

#define SGENTI_3_DEFAULTS   { 5369,\
        1000,\
        0,\
        0x7fff,\
        0,\
        0,\
        0,\
        0,\
        (void (*)(void *))SGENTI_3_calc}


typedef struct {
        unsigned int freq;
        unsigned int step_max;
        unsigned int alpha;
        int gain;
        int offset;
        int out11;
        int out12;
        int out13;
        unsigned int phase;
        int out21;
        int out22;
        int out23;
        void (*calc)(void *);
        }SGENT_3D;


#define SGENT_3D_DEFAULTS   { 5369,\
        1000,\
        0,\
        0x7fff,\
        0,\
        0,\
        0,\
        0,\
        0x4000,\
        0,\
        0,\
        0,\
        (void (*)(void *))SGENT_3D_calc}

typedef struct {
        unsigned int freq;
        unsigned int step_max;
        unsigned int alpha;
        int gain;
        int offset;
        int out11;
        int out12;
        int out13;
        unsigned int phase;
        int out21;
        int out22;
        int out23;
        void (*calc)(void *);
        }SGENTI_3D;

#define SGENTI_3D_DEFAULTS  { 5369,\
        1000,\
        0,\
        0x7fff,\
        0,\
        0,\
        0,\
        0,\
        0x4000,\
        0,\
        0,\
        0,\
        (void (*)(void *))SGENTI_3D_calc}


typedef struct {
        void (*calc)(void *);
        unsigned long int freq;
        unsigned long int step_max;
        unsigned long int alpha;
        int gain;
        int offset;
        int out;
        }SGENHP_1;

#define SGENHP_1_DEFAULTS   { (void (*) (void *))SGENHP_1_calc,\
		0x14F8CF92,\
        0x3E7FB26,\
        0UL,\
        0x7fff,\
        0,\
        0}


typedef struct {
        unsigned long int freq;
        unsigned long int step_max;
        unsigned long int alpha;
        int gain;
        int offset;
        int out1;
        int out2;
        unsigned long int phase;
        void (*calc)(void *);
        }SGENHP_2;

#define SGENHP_2_DEFAULTS   { 0x14F8CF92,\
        0x3E7FB26,\
        0,\
        0x7fff,\
        0,\
        0,\
        0,\
        0x40000000,\
        (void (*)(void *))SGENHP_2_calc}

typedef struct { int  freq;
        unsigned int  step_max;
        unsigned int  angle;
        int  gain;
        int  offset;
        int  out;
        void  (*calc)(void *);
        }RMPGEN;

#define RMPGEN_DEFAULTS {5369,\
        1000,\
        0x0000,\
        0x7FFF,\
        0x0000,\
        0,\
        (void (*)(void *))RMPGEN_calc }

typedef struct {  unsigned int skip_cntr;
        unsigned int  prescalar;
        unsigned int  freq;
        unsigned int  step_max;
        unsigned long task;
        unsigned int  alpha;
        int  gain;
        int  offset;
        int  out;
        void  (*init)(void *);
        void  (*calc)(void *);
        }TZDLGEN;

#define TZDLGEN_DEFAULTS { 0, \
        1, \
        5369, \
        4000, \
        0x0000UL, \
        0x0000, \
        0x7fff, \
        0x0000, \
        0x0000, \
        (void (*)(void *))TZDLGEN_init,\
        (void (*)(void *))TZDLGEN_calc}

typedef struct { int mode;
        int trig;
        unsigned int skip_cntr;
        unsigned int prescalar;
        unsigned int  freq;
        unsigned int  step_max;
        int  t_rmpup;
        int  t_max;
        int  t_rmpdn;
        int  t_min;
        unsigned long task;
        unsigned int  alpha;
        int  gain;
        int  offset;
        int  out;
        void  (*init)(void *);
        void  (*calc)(void *);
        }PROFILE;

#define PROFILE_DEFAULTS {1, \
        0, \
        0, \
        1, \
        5369, \
        4000, \
        0, \
        0, \
        0, \
        0, \
        0x0000UL, \
        0x0000, \
        0x7fff, \
        0x0000, \
        0x0000, \
        (void (*)(void *))PROFILE_init, \
        (void (*)(void *))PROFILE_calc}




typedef SGENT_1   *SGENT_1_handle;
typedef SGENT_2   *SGENT_2_handle;
typedef SGENT_3   *SGENT_3_handle;
typedef SGENT_3D  *SGENT_3D_handle;
typedef SGENTI_1  *SGENTI_1_handle;
typedef SGENTI_2  *SGENTI_2_handle;
typedef SGENTI_3  *SGENTI_3_handle;
typedef SGENTI_3D *SGENTI_3D_handle;
typedef SGENHP_1  *SGENHP_1_handle;
typedef SGENHP_2  *SGENHP_2_handle;
typedef RMPGEN    *RMPGEN_handle;
typedef TZDLGEN   *TZDLGEN_handle;
typedef PROFILE   *PROFILE_handle;


void SGENT_1_calc(void *);
void SGENTI_1_calc(void *);
void SGENT_2_calc(void *);
void SGENTI_2_calc(void *);
void SGENT_3_calc(void *);
void SGENTI_3_calc(void *);
void SGENT_3D_calc(void *);
void SGENTI_3D_calc(void *);
void SGENHP_1_calc(void *);
void SGENHP_2_calc(void *);
void RMPGEN_calc(void *);
void TZDLGEN_init(void *);
void TZDLGEN_calc(void *);
void PROFILE_init(void *);
void PROFILE_calc(void *);

#endif



