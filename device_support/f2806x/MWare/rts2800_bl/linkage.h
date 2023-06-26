/*****************************************************************************/
/* linkage.h   v6.0.1                                                         */
/*                                                                           */
/* Copyright (c) 1998-2015 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/

#ifndef _LINKAGE
#define _LINKAGE

/* No modifiers needed to access code */

#define _CODE_ACCESS

/*--------------------------------------------------------------------------*/
/* Define _DATA_ACCESS ==> how to access RTS global or static data          */
/*--------------------------------------------------------------------------*/
#ifndef _FAR_RTS
#define _DATA_ACCESS
#else
#define _DATA_ACCESS far
#endif
#define _DATA_ACCESS_NEAR

/*--------------------------------------------------------------------------*/
/* Define _OPTIMIZE_FOR_SPACE ==> Always optimize for space.                */
/*--------------------------------------------------------------------------*/
#ifndef _OPTIMIZE_FOR_SPACE
#define _OPTIMIZE_FOR_SPACE 1
#endif

/*--------------------------------------------------------------------------*/
/* Define _IDECL ==> how inline functions are declared                      */
/*--------------------------------------------------------------------------*/
#ifdef _INLINE
#define _IDECL static __inline
#define _IDEFN static __inline
#else
#define _IDECL extern _CODE_ACCESS
#define _IDEFN _CODE_ACCESS
#endif

#endif /* _LINKAGE */


