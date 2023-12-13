// main.c

#include "F28x_Project.h"
#include "DCLF32.h"
#include "f28004x_erad.h"
#include "f28004x_dcl_erad.h"

// controllers
DCL_PID F1 = PID_DEFAULTS;
DCL_PI F2 = PI_DEFAULTS;
DCL_PI F3 = PI_DEFAULTS;
DCL_GSM F4 = GSM_DEFAULTS;
DCL_DF11 F5 = DF11_DEFAULTS;
DCL_DF22 F6 = DF22_DEFAULTS;
DCL_DF23 F7 = DF23_DEFAULTS;
DCL_DF23_SPS F7sps = DF23_SPS_DEFAULTS;
DCL_CSS F7css = DCL_CSS_DEFAULTS;

// program constants
#define DECIM_F1    10
#define DECIM_F6    3
#define DECIM_F7    9
#define PAYLOAD_F7  2000

// variables
uint16_t i = 0;
uint32_t IdleLoopCount = 0UL;
uint16_t IsraCount = 0;
uint16_t IsrbCount = 0;
uint16_t IsrcCount = 0;
int16_t DecimF1 = DECIM_F1;
int16_t DecimF6 = DECIM_F6;
volatile float32_t r1, y1, u1;
volatile float32_t y2, u2;
volatile float32_t r3, y3, u3;
volatile float32_t r4, y4, u4;
volatile float32_t u5;
volatile float32_t r6, u6;
volatile float32_t r7, y7, u7;
float32_t x = 0.0f;

// ISR declarations
interrupt void ISRa(void);
interrupt void ISRb(void);
interrupt void ISRc(void);

void func_label(void);

void F28x_usDelayErad(long LoopCount);

void EradConfig(void);

uint32_t MaxWindowCycles = 0;
uint32_t MaxISRCycles = 0;

void main(void)
{
    InitSysCtrl();
    InitGpio();

    // interrupt configuration
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();
    EALLOW;
    PieVectTable.TIMER0_INT = &ISRa;
    PieVectTable.TIMER1_INT = &ISRb;
    PieVectTable.TIMER2_INT = &ISRc;

    // configure CPU timers
    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 100.0f, 100.0f);
    ConfigCpuTimer(&CpuTimer1, 100.0f, 3.952f);
    ConfigCpuTimer(&CpuTimer2, 100.0f, 16.67f);

    // controller initialization
    // PID controller (F1)
    F1.Kp = 9.0623f;
    F1.Ki = 0.012f;
    F1.Kd = 3.5f;
    F1.c1 = 0.99f;
    F1.c2 = 0.1221f;
    F1.Umax = 15.4665f;
    F1.Umin = -16.22f;
    r1 = 0.754f;
    y1 = 0.0f;
    u1 = 0.0f;

    // PI controller (F2)
    F2.Kp = 0.1234f;
    F2.Ki = 0.02389f;
    F2.Umax = 15.4665f;
    F2.Umin = -16.22f;
    F2.Imax = 1.465f;
    F2.Imin = -1.2f;
    y2 = 0.0f;

    // PI controller (F3)
    F3.Kp = 0.1234f;
    F3.Ki = 0.02389f;
    F3.Umax = 15.4665f;
    F3.Umin = -16.22f;
    F3.Imax = 1.465f;
    F3.Imin = -1.2f;
    r3 = -0.125f;
    y3 = 0.0f;

    // GSM (F4)
    for (i=1; i<=GSM_N; i++)
    {
        x += F4.h;
        F4.sps->c[i] = x*x;
    }
    DCL_loadGSMgains(&F4);
    DCL_REQUEST_UPDATE(&F4);
    DCL_updateGSM(&F4);
    r4 = 0.0899f;
    y4 = -0.106f;

    // DF11 (F5)
    F5.b0 = 5.106;
    F5.b1 = -5.094;
    F5.a1 = -1;

    // DF22 (F6)
    F6.b0 = 9.8549f;
    F6.b1 = -19.4165f;
    F6.b2 = 9.5636f;
    F6.a1 = -1.9417f;
    F6.a2 = 0.9417f;
    r6 = 0.95f;

    // DF23 (F7)
    F7.sps = &F7sps;
    F7.css = &F7css;
    F7.sps->b0 = 9.658f;
    F7.sps->b1 = -9.158f;
    F7.sps->b2 = -9.6521f;
    F7.sps->b3 = 9.1639f;
    F7.sps->a1 = -2.128f;
    F7.sps->a2 = 1.3968f;
    F7.sps->a3 = -0.2689f;
    DCL_REQUEST_UPDATE(&F7);
    DCL_updateDF23(&F7);
    r7 = 0.5f;
    y7 = 0.0f;

    // enable interrupts
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
    IER |= M_INT1;
    IER |= M_INT13;
    IER |= M_INT14;
    ERTM;
    EINT;

    // Configure ERAD for profiling
    EradConfig();

    // start CPU timers
    StartCpuTimer1();
    StartCpuTimer2();
    StartCpuTimer0();

    while(1)
    {
        DCL_REQUEST_UPDATE(&F7);
        DCL_updateDF23(&F7);

        asm(" NOP");
        IdleLoopCount++;

        if(IdleLoopCount == 1000)
        {
            CpuTimer0Regs.TCR.bit.TSS = 1;
            CpuTimer1Regs.TCR.bit.TSS = 1;
            CpuTimer2Regs.TCR.bit.TSS = 1;

            ERAD_setGlobalCTMDisable(CTM1_INST | CTM2_INST);
            ERAD_globalHWBPDisable(HWBP1_INST | HWBP2_INST | HWBP3_INST);

            MaxWindowCycles = ERAD_counterGetMaxCount(CTM2_INST);
            MaxISRCycles 	= ERAD_counterGetMaxCount(CTM1_INST);

            while(1);
        }
    }
}

/* control loop (a) - CPU timer 0 @ 10 kHz */
#pragma CODE_SECTION(ISRa, "interruptSection")
interrupt void ISRa(void)
{
	CpuTimer0Regs.TCR.bit.TIF = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    EINT;

    if (0 > --DecimF1)
    {
        u1 = DCL_runPID_C2(&F1, r1, y1, 1.0f);
        DecimF1 = DECIM_F1;
    }

    u2 = DCL_runPI_C2(&F2, u1, y2);
    u3 = DCL_runPI_C2(&F3, r3, y3);

    IsraCount++;
    DINT;
}

/* control loop (b) - CPU timer 1 @ 253 kHz */
#pragma CODE_SECTION(ISRb, "interruptSection")
interrupt void ISRb(void)
{
    CpuTimer1Regs.TCR.bit.TIF = 1;

    u4 = DCL_runGSM_C1(&F4, r4 - y4);
    u5 = DCL_runDF11_C2(&F5, u4);

    if (0 > --DecimF6)
    {
        u6 = DCL_runDF22_C4(&F6, r6);
        DecimF6 = DECIM_F6;
    }

    IsrbCount++;
}

/* control loop (c) - CPU timer 2 @ 60 kHz */
#pragma CODE_SECTION(ISRc, "interruptSection")
interrupt void ISRc(void)
{
    CpuTimer2Regs.TCR.bit.TIF = 1;

    u7 = DCL_runDF23_C4(&F7, r7 - y7);

    IsrcCount++;

    if (0 == (IsrcCount + IsrbCount) % DECIM_F7)
    {
    	F28x_usDelayErad(PAYLOAD_F7);
    }
}

/* ERAD configuration */
void EradConfig()
{
    hwbpConfig hwbpConfig1,hwbpConfig2,hwbpConfig3;
    counterConfig counterConfig1,counterConfig2;

    // Disable all comparator and counter units
    ERAD_setGlobalCTMDisable(CTM1_INST | CTM2_INST);
    ERAD_globalHWBPDisable(HWBP1_INST | HWBP2_INST | HWBP3_INST);

    // Setup BC-1 for VPC Match when code is executing interrupts
    // Configure BC-1 for tracing any match for the following "0x9800 - 0x9FFF" i.e. LS3
    hwbpConfig1.BUS_SEL		= VPC;
	hwbpConfig1.COMP_MODE	= EQ;
	hwbpConfig1.DBGEVT		= DISABLED;
	hwbpConfig1.MASK		= 0x000007FF;
	hwbpConfig1.REF			= 0x00009800;
	hwbpConfig1.RTOSINT		= DISABLED;
	ERAD_HWBPConfig(HWBP1_INST,hwbpConfig1);

    // Setup BC-2 for VPC Match when ISR + 2 instruction start
    hwbpConfig2.BUS_SEL		= VPC;
	hwbpConfig2.COMP_MODE	= EQ;
	hwbpConfig2.DBGEVT		= DISABLED;
	hwbpConfig2.MASK		= 0x00000000;
	hwbpConfig2.REF			= ((uint32_t)&(ISRa)) + 0x1;
	hwbpConfig2.RTOSINT		= DISABLED;
	ERAD_HWBPConfig(HWBP2_INST,hwbpConfig2);

    // Setup BC-3 for VPC Match when ISRa starts
    hwbpConfig3.BUS_SEL		= VPC;
	hwbpConfig3.COMP_MODE	= EQ;
	hwbpConfig3.DBGEVT		= DISABLED;
	hwbpConfig3.MASK		= 0x00000000;
	hwbpConfig3.REF			= (uint32_t)&(ISRa);
	hwbpConfig3.RTOSINT		= DISABLED;
	ERAD_HWBPConfig(HWBP3_INST,hwbpConfig3);

    // Setup CNT-1 in START STOP mode with START = BC-2, STOP=BC-3, COUNTER ENABLE = BC-1
	counterConfig1.RTOSINT		= DISABLED;
	counterConfig1.DBGEVT		= DISABLED;
	counterConfig1.EDGE_LEVEL_CFG 	= LEVEL;
	counterConfig1.START_STOP_MODE 	= ENABLED;
	counterConfig1.START_INP_SEL	= BUS_COMP2_EVENT;
	counterConfig1.STOP_INP_SEL		= BUS_COMP3_EVENT;
	counterConfig1.CNT_INP_SEL_EN 	= ENABLED;
	counterConfig1.CNT_INP_SEL		= BUS_COMP1_EVENT;
	counterConfig1.HW_CNT_RST 	= DISABLED;
	counterConfig1.RST_INP_SEL 	= BUS_COMP1_EVENT; // This is don't care since HW_CNT_RST is Disabled
	counterConfig1.RST_ON_MATCH	= DISABLED;
	ERAD_counterConfig(CTM1_INST,counterConfig1);

    // Setup CNT-2 in START STOP mode with START = BC-2, STOP=BC-3, COUNTER ENABLE = Always / CPU_CYCLES
	counterConfig2.RTOSINT		= DISABLED;
	counterConfig2.DBGEVT		= DISABLED;
	counterConfig2.EDGE_LEVEL_CFG 	= LEVEL;
	counterConfig2.START_STOP_MODE 	= ENABLED;
	counterConfig2.START_INP_SEL	= BUS_COMP2_EVENT;
	counterConfig2.STOP_INP_SEL		= BUS_COMP3_EVENT;
	counterConfig2.CNT_INP_SEL_EN 	= DISABLED;
	counterConfig2.CNT_INP_SEL		= BUS_COMP1_EVENT; //T his is don't care since CNT_INP_SEL_EN is Disabled
	counterConfig2.HW_CNT_RST 	= DISABLED;
	counterConfig2.RST_INP_SEL 	= BUS_COMP1_EVENT; // This is don't care since HW_CNT_RST is Disabled
	counterConfig2.RST_ON_MATCH	= DISABLED;
	ERAD_counterConfig(CTM2_INST,counterConfig2);

    // Enable all comparator and counter units
    ERAD_setGlobalCTMEnable(CTM1_INST | CTM2_INST);
    ERAD_globalHWBPEnable(HWBP1_INST | HWBP2_INST | HWBP3_INST);
}

/* end of file */
