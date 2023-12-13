//###########################################################################
//
// FILE:    f28p65x_output_xbar.h
//
// TITLE:   Definitions for the OUTPUT_XBAR registers.
//
//###########################################################################
// $Copyright:
//###########################################################################

#ifndef F28P65X_OUTPUT_XBAR_H
#define F28P65X_OUTPUT_XBAR_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// OUTPUT_XBAR Individual Register Bit Definitions:

struct EXT64_OUTPUT1MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 Mux0 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX1:2;                      // 3:2 Mux1 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX2:2;                      // 5:4 Mux2 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX3:2;                      // 7:6 Mux3 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX4:2;                      // 9:8 Mux4 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX5:2;                      // 11:10 Mux5 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX6:2;                      // 13:12 Mux6 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX7:2;                      // 15:14 Mux7 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX8:2;                      // 17:16 Mux8 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX9:2;                      // 19:18 Mux9 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX10:2;                     // 21:20 Mux10 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX11:2;                     // 23:22 Mux11 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX12:2;                     // 25:24 Mux12 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX13:2;                     // 27:26 Mux13 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX14:2;                     // 29:28 Mux14 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX15:2;                     // 31:30 Mux15 Configuration for OUTPUT1 of OUTPUT-XBAR
};

union EXT64_OUTPUT1MUX0TO15CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT1MUX0TO15CFG_BITS  bit;
};

struct EXT64_OUTPUT1MUX16TO31CFG_BITS {       // bits description
    Uint16 MUX16:2;                     // 1:0 Mux16 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX17:2;                     // 3:2 Mux17 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX18:2;                     // 5:4 Mux18 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX19:2;                     // 7:6 Mux19 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX20:2;                     // 9:8 Mux20 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX21:2;                     // 11:10 Mux21 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX22:2;                     // 13:12 Mux22 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX23:2;                     // 15:14 Mux23 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX24:2;                     // 17:16 Mux24 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX25:2;                     // 19:18 Mux25 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX26:2;                     // 21:20 Mux26 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX27:2;                     // 23:22 Mux27 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX28:2;                     // 25:24 Mux28 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX29:2;                     // 27:26 Mux29 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX30:2;                     // 29:28 Mux30 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX31:2;                     // 31:30 Mux31 Configuration for OUTPUT1 of OUTPUT-XBAR
};

union EXT64_OUTPUT1MUX16TO31CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT1MUX16TO31CFG_BITS  bit;
};

struct EXT64_OUTPUT1MUX32TO47CFG_BITS {       // bits description
    Uint16 MUX32:2;                     // 1:0 MUX32 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX33:2;                     // 3:2 MUX33 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX34:2;                     // 5:4 MUX34 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX35:2;                     // 7:6 MUX35 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX36:2;                     // 9:8 MUX36 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX37:2;                     // 11:10 MUX37 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX38:2;                     // 13:12 MUX38 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX39:2;                     // 15:14 MUX39 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX40:2;                     // 17:16 MUX40 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX41:2;                     // 19:18 MUX41 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX42:2;                     // 21:20 MUX42 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX43:2;                     // 23:22 MUX43 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX44:2;                     // 25:24 MUX44 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX45:2;                     // 27:26 MUX45 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX46:2;                     // 29:28 MUX46 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX47:2;                     // 31:30 MUX47 Configuration for OUTPUT1 of OUTPUT-XBAR
};

union EXT64_OUTPUT1MUX32TO47CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT1MUX32TO47CFG_BITS  bit;
};

struct EXT64_OUTPUT1MUX48TO63CFG_BITS {       // bits description
    Uint16 MUX48:2;                     // 1:0 MUX48 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX49:2;                     // 3:2 MUX49 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX50:2;                     // 5:4 MUX50 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX51:2;                     // 7:6 MUX51 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX52:2;                     // 9:8 MUX52 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX53:2;                     // 11:10 MUX53 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX54:2;                     // 13:12 MUX54 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX55:2;                     // 15:14 MUX55 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX56:2;                     // 17:16 MUX56 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX57:2;                     // 19:18 MUX57 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX58:2;                     // 21:20 MUX58 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX59:2;                     // 23:22 MUX59 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX60:2;                     // 25:24 MUX60 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX61:2;                     // 27:26 MUX61 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX62:2;                     // 29:28 MUX62 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX63:2;                     // 31:30 MUX63 Configuration for OUTPUT1 of OUTPUT-XBAR
};

union EXT64_OUTPUT1MUX48TO63CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT1MUX48TO63CFG_BITS  bit;
};

struct EXT64_OUTPUT2MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 Mux0 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX1:2;                      // 3:2 Mux1 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX2:2;                      // 5:4 Mux2 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX3:2;                      // 7:6 Mux3 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX4:2;                      // 9:8 Mux4 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX5:2;                      // 11:10 Mux5 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX6:2;                      // 13:12 Mux6 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX7:2;                      // 15:14 Mux7 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX8:2;                      // 17:16 Mux8 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX9:2;                      // 19:18 Mux9 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX10:2;                     // 21:20 Mux10 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX11:2;                     // 23:22 Mux11 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX12:2;                     // 25:24 Mux12 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX13:2;                     // 27:26 Mux13 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX14:2;                     // 29:28 Mux14 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX15:2;                     // 31:30 Mux15 Configuration for OUTPUT2 of OUTPUT-XBAR
};

union EXT64_OUTPUT2MUX0TO15CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT2MUX0TO15CFG_BITS  bit;
};

struct EXT64_OUTPUT2MUX16TO31CFG_BITS {       // bits description
    Uint16 MUX16:2;                     // 1:0 Mux16 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX17:2;                     // 3:2 Mux17 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX18:2;                     // 5:4 Mux18 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX19:2;                     // 7:6 Mux19 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX20:2;                     // 9:8 Mux20 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX21:2;                     // 11:10 Mux21 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX22:2;                     // 13:12 Mux22 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX23:2;                     // 15:14 Mux23 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX24:2;                     // 17:16 Mux24 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX25:2;                     // 19:18 Mux25 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX26:2;                     // 21:20 Mux26 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX27:2;                     // 23:22 Mux27 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX28:2;                     // 25:24 Mux28 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX29:2;                     // 27:26 Mux29 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX30:2;                     // 29:28 Mux30 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX31:2;                     // 31:30 Mux31 Configuration for OUTPUT2 of OUTPUT-XBAR
};

union EXT64_OUTPUT2MUX16TO31CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT2MUX16TO31CFG_BITS  bit;
};

struct EXT64_OUTPUT2MUX32TO47CFG_BITS {       // bits description
    Uint16 MUX32:2;                     // 1:0 MUX32 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX33:2;                     // 3:2 MUX33 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX34:2;                     // 5:4 MUX34 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX35:2;                     // 7:6 MUX35 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX36:2;                     // 9:8 MUX36 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX37:2;                     // 11:10 MUX37 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX38:2;                     // 13:12 MUX38 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX39:2;                     // 15:14 MUX39 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX40:2;                     // 17:16 MUX40 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX41:2;                     // 19:18 MUX41 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX42:2;                     // 21:20 MUX42 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX43:2;                     // 23:22 MUX43 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX44:2;                     // 25:24 MUX44 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX45:2;                     // 27:26 MUX45 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX46:2;                     // 29:28 MUX46 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX47:2;                     // 31:30 MUX47 Configuration for OUTPUT2 of OUTPUT-XBAR
};

union EXT64_OUTPUT2MUX32TO47CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT2MUX32TO47CFG_BITS  bit;
};

struct EXT64_OUTPUT2MUX48TO63CFG_BITS {       // bits description
    Uint16 MUX48:2;                     // 1:0 MUX48 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX49:2;                     // 3:2 MUX49 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX50:2;                     // 5:4 MUX50 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX51:2;                     // 7:6 MUX51 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX52:2;                     // 9:8 MUX52 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX53:2;                     // 11:10 MUX53 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX54:2;                     // 13:12 MUX54 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX55:2;                     // 15:14 MUX55 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX56:2;                     // 17:16 MUX56 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX57:2;                     // 19:18 MUX57 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX58:2;                     // 21:20 MUX58 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX59:2;                     // 23:22 MUX59 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX60:2;                     // 25:24 MUX60 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX61:2;                     // 27:26 MUX61 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX62:2;                     // 29:28 MUX62 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX63:2;                     // 31:30 MUX63 Configuration for OUTPUT2 of OUTPUT-XBAR
};

union EXT64_OUTPUT2MUX48TO63CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT2MUX48TO63CFG_BITS  bit;
};

struct EXT64_OUTPUT3MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 Mux0 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX1:2;                      // 3:2 Mux1 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX2:2;                      // 5:4 Mux2 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX3:2;                      // 7:6 Mux3 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX4:2;                      // 9:8 Mux4 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX5:2;                      // 11:10 Mux5 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX6:2;                      // 13:12 Mux6 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX7:2;                      // 15:14 Mux7 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX8:2;                      // 17:16 Mux8 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX9:2;                      // 19:18 Mux9 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX10:2;                     // 21:20 Mux10 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX11:2;                     // 23:22 Mux11 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX12:2;                     // 25:24 Mux12 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX13:2;                     // 27:26 Mux13 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX14:2;                     // 29:28 Mux14 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX15:2;                     // 31:30 Mux15 Configuration for OUTPUT3 of OUTPUT-XBAR
};

union EXT64_OUTPUT3MUX0TO15CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT3MUX0TO15CFG_BITS  bit;
};

struct EXT64_OUTPUT3MUX16TO31CFG_BITS {       // bits description
    Uint16 MUX16:2;                     // 1:0 Mux16 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX17:2;                     // 3:2 Mux17 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX18:2;                     // 5:4 Mux18 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX19:2;                     // 7:6 Mux19 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX20:2;                     // 9:8 Mux20 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX21:2;                     // 11:10 Mux21 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX22:2;                     // 13:12 Mux22 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX23:2;                     // 15:14 Mux23 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX24:2;                     // 17:16 Mux24 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX25:2;                     // 19:18 Mux25 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX26:2;                     // 21:20 Mux26 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX27:2;                     // 23:22 Mux27 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX28:2;                     // 25:24 Mux28 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX29:2;                     // 27:26 Mux29 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX30:2;                     // 29:28 Mux30 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX31:2;                     // 31:30 Mux31 Configuration for OUTPUT3 of OUTPUT-XBAR
};

union EXT64_OUTPUT3MUX16TO31CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT3MUX16TO31CFG_BITS  bit;
};

struct EXT64_OUTPUT3MUX32TO47CFG_BITS {       // bits description
    Uint16 MUX32:2;                     // 1:0 MUX32 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX33:2;                     // 3:2 MUX33 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX34:2;                     // 5:4 MUX34 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX35:2;                     // 7:6 MUX35 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX36:2;                     // 9:8 MUX36 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX37:2;                     // 11:10 MUX37 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX38:2;                     // 13:12 MUX38 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX39:2;                     // 15:14 MUX39 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX40:2;                     // 17:16 MUX40 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX41:2;                     // 19:18 MUX41 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX42:2;                     // 21:20 MUX42 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX43:2;                     // 23:22 MUX43 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX44:2;                     // 25:24 MUX44 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX45:2;                     // 27:26 MUX45 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX46:2;                     // 29:28 MUX46 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX47:2;                     // 31:30 MUX47 Configuration for OUTPUT3 of OUTPUT-XBAR
};

union EXT64_OUTPUT3MUX32TO47CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT3MUX32TO47CFG_BITS  bit;
};

struct EXT64_OUTPUT3MUX48TO63CFG_BITS {       // bits description
    Uint16 MUX48:2;                     // 1:0 MUX48 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX49:2;                     // 3:2 MUX49 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX50:2;                     // 5:4 MUX50 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX51:2;                     // 7:6 MUX51 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX52:2;                     // 9:8 MUX52 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX53:2;                     // 11:10 MUX53 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX54:2;                     // 13:12 MUX54 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX55:2;                     // 15:14 MUX55 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX56:2;                     // 17:16 MUX56 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX57:2;                     // 19:18 MUX57 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX58:2;                     // 21:20 MUX58 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX59:2;                     // 23:22 MUX59 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX60:2;                     // 25:24 MUX60 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX61:2;                     // 27:26 MUX61 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX62:2;                     // 29:28 MUX62 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX63:2;                     // 31:30 MUX63 Configuration for OUTPUT3 of OUTPUT-XBAR
};

union EXT64_OUTPUT3MUX48TO63CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT3MUX48TO63CFG_BITS  bit;
};

struct EXT64_OUTPUT4MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 Mux0 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX1:2;                      // 3:2 Mux1 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX2:2;                      // 5:4 Mux2 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX3:2;                      // 7:6 Mux3 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX4:2;                      // 9:8 Mux4 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX5:2;                      // 11:10 Mux5 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX6:2;                      // 13:12 Mux6 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX7:2;                      // 15:14 Mux7 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX8:2;                      // 17:16 Mux8 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX9:2;                      // 19:18 Mux9 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX10:2;                     // 21:20 Mux10 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX11:2;                     // 23:22 Mux11 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX12:2;                     // 25:24 Mux12 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX13:2;                     // 27:26 Mux13 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX14:2;                     // 29:28 Mux14 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX15:2;                     // 31:30 Mux15 Configuration for OUTPUT4 of OUTPUT-XBAR
};

union EXT64_OUTPUT4MUX0TO15CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT4MUX0TO15CFG_BITS  bit;
};

struct EXT64_OUTPUT4MUX16TO31CFG_BITS {       // bits description
    Uint16 MUX16:2;                     // 1:0 Mux16 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX17:2;                     // 3:2 Mux17 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX18:2;                     // 5:4 Mux18 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX19:2;                     // 7:6 Mux19 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX20:2;                     // 9:8 Mux20 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX21:2;                     // 11:10 Mux21 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX22:2;                     // 13:12 Mux22 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX23:2;                     // 15:14 Mux23 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX24:2;                     // 17:16 Mux24 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX25:2;                     // 19:18 Mux25 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX26:2;                     // 21:20 Mux26 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX27:2;                     // 23:22 Mux27 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX28:2;                     // 25:24 Mux28 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX29:2;                     // 27:26 Mux29 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX30:2;                     // 29:28 Mux30 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX31:2;                     // 31:30 Mux31 Configuration for OUTPUT4 of OUTPUT-XBAR
};

union EXT64_OUTPUT4MUX16TO31CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT4MUX16TO31CFG_BITS  bit;
};

struct EXT64_OUTPUT4MUX32TO47CFG_BITS {       // bits description
    Uint16 MUX32:2;                     // 1:0 MUX32 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX33:2;                     // 3:2 MUX33 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX34:2;                     // 5:4 MUX34 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX35:2;                     // 7:6 MUX35 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX36:2;                     // 9:8 MUX36 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX37:2;                     // 11:10 MUX37 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX38:2;                     // 13:12 MUX38 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX39:2;                     // 15:14 MUX39 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX40:2;                     // 17:16 MUX40 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX41:2;                     // 19:18 MUX41 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX42:2;                     // 21:20 MUX42 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX43:2;                     // 23:22 MUX43 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX44:2;                     // 25:24 MUX44 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX45:2;                     // 27:26 MUX45 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX46:2;                     // 29:28 MUX46 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX47:2;                     // 31:30 MUX47 Configuration for OUTPUT4 of OUTPUT-XBAR
};

union EXT64_OUTPUT4MUX32TO47CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT4MUX32TO47CFG_BITS  bit;
};

struct EXT64_OUTPUT4MUX48TO63CFG_BITS {       // bits description
    Uint16 MUX48:2;                     // 1:0 MUX48 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX49:2;                     // 3:2 MUX49 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX50:2;                     // 5:4 MUX50 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX51:2;                     // 7:6 MUX51 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX52:2;                     // 9:8 MUX52 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX53:2;                     // 11:10 MUX53 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX54:2;                     // 13:12 MUX54 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX55:2;                     // 15:14 MUX55 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX56:2;                     // 17:16 MUX56 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX57:2;                     // 19:18 MUX57 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX58:2;                     // 21:20 MUX58 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX59:2;                     // 23:22 MUX59 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX60:2;                     // 25:24 MUX60 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX61:2;                     // 27:26 MUX61 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX62:2;                     // 29:28 MUX62 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX63:2;                     // 31:30 MUX63 Configuration for OUTPUT4 of OUTPUT-XBAR
};

union EXT64_OUTPUT4MUX48TO63CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT4MUX48TO63CFG_BITS  bit;
};

struct EXT64_OUTPUT5MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 Mux0 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX1:2;                      // 3:2 Mux1 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX2:2;                      // 5:4 Mux2 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX3:2;                      // 7:6 Mux3 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX4:2;                      // 9:8 Mux4 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX5:2;                      // 11:10 Mux5 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX6:2;                      // 13:12 Mux6 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX7:2;                      // 15:14 Mux7 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX8:2;                      // 17:16 Mux8 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX9:2;                      // 19:18 Mux9 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX10:2;                     // 21:20 Mux10 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX11:2;                     // 23:22 Mux11 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX12:2;                     // 25:24 Mux12 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX13:2;                     // 27:26 Mux13 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX14:2;                     // 29:28 Mux14 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX15:2;                     // 31:30 Mux15 Configuration for OUTPUT5 of OUTPUT-XBAR
};

union EXT64_OUTPUT5MUX0TO15CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT5MUX0TO15CFG_BITS  bit;
};

struct EXT64_OUTPUT5MUX16TO31CFG_BITS {       // bits description
    Uint16 MUX16:2;                     // 1:0 Mux16 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX17:2;                     // 3:2 Mux17 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX18:2;                     // 5:4 Mux18 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX19:2;                     // 7:6 Mux19 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX20:2;                     // 9:8 Mux20 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX21:2;                     // 11:10 Mux21 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX22:2;                     // 13:12 Mux22 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX23:2;                     // 15:14 Mux23 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX24:2;                     // 17:16 Mux24 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX25:2;                     // 19:18 Mux25 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX26:2;                     // 21:20 Mux26 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX27:2;                     // 23:22 Mux27 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX28:2;                     // 25:24 Mux28 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX29:2;                     // 27:26 Mux29 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX30:2;                     // 29:28 Mux30 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX31:2;                     // 31:30 Mux31 Configuration for OUTPUT5 of OUTPUT-XBAR
};

union EXT64_OUTPUT5MUX16TO31CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT5MUX16TO31CFG_BITS  bit;
};

struct EXT64_OUTPUT5MUX32TO47CFG_BITS {       // bits description
    Uint16 MUX32:2;                     // 1:0 MUX32 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX33:2;                     // 3:2 MUX33 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX34:2;                     // 5:4 MUX34 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX35:2;                     // 7:6 MUX35 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX36:2;                     // 9:8 MUX36 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX37:2;                     // 11:10 MUX37 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX38:2;                     // 13:12 MUX38 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX39:2;                     // 15:14 MUX39 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX40:2;                     // 17:16 MUX40 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX41:2;                     // 19:18 MUX41 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX42:2;                     // 21:20 MUX42 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX43:2;                     // 23:22 MUX43 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX44:2;                     // 25:24 MUX44 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX45:2;                     // 27:26 MUX45 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX46:2;                     // 29:28 MUX46 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX47:2;                     // 31:30 MUX47 Configuration for OUTPUT5 of OUTPUT-XBAR
};

union EXT64_OUTPUT5MUX32TO47CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT5MUX32TO47CFG_BITS  bit;
};

struct EXT64_OUTPUT5MUX48TO63CFG_BITS {       // bits description
    Uint16 MUX48:2;                     // 1:0 MUX48 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX49:2;                     // 3:2 MUX49 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX50:2;                     // 5:4 MUX50 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX51:2;                     // 7:6 MUX51 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX52:2;                     // 9:8 MUX52 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX53:2;                     // 11:10 MUX53 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX54:2;                     // 13:12 MUX54 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX55:2;                     // 15:14 MUX55 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX56:2;                     // 17:16 MUX56 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX57:2;                     // 19:18 MUX57 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX58:2;                     // 21:20 MUX58 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX59:2;                     // 23:22 MUX59 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX60:2;                     // 25:24 MUX60 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX61:2;                     // 27:26 MUX61 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX62:2;                     // 29:28 MUX62 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX63:2;                     // 31:30 MUX63 Configuration for OUTPUT5 of OUTPUT-XBAR
};

union EXT64_OUTPUT5MUX48TO63CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT5MUX48TO63CFG_BITS  bit;
};

struct EXT64_OUTPUT6MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 Mux0 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX1:2;                      // 3:2 Mux1 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX2:2;                      // 5:4 Mux2 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX3:2;                      // 7:6 Mux3 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX4:2;                      // 9:8 Mux4 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX5:2;                      // 11:10 Mux5 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX6:2;                      // 13:12 Mux6 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX7:2;                      // 15:14 Mux7 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX8:2;                      // 17:16 Mux8 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX9:2;                      // 19:18 Mux9 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX10:2;                     // 21:20 Mux10 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX11:2;                     // 23:22 Mux11 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX12:2;                     // 25:24 Mux12 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX13:2;                     // 27:26 Mux13 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX14:2;                     // 29:28 Mux14 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX15:2;                     // 31:30 Mux15 Configuration for OUTPUT6 of OUTPUT-XBAR
};

union EXT64_OUTPUT6MUX0TO15CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT6MUX0TO15CFG_BITS  bit;
};

struct EXT64_OUTPUT6MUX16TO31CFG_BITS {       // bits description
    Uint16 MUX16:2;                     // 1:0 Mux16 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX17:2;                     // 3:2 Mux17 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX18:2;                     // 5:4 Mux18 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX19:2;                     // 7:6 Mux19 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX20:2;                     // 9:8 Mux20 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX21:2;                     // 11:10 Mux21 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX22:2;                     // 13:12 Mux22 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX23:2;                     // 15:14 Mux23 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX24:2;                     // 17:16 Mux24 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX25:2;                     // 19:18 Mux25 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX26:2;                     // 21:20 Mux26 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX27:2;                     // 23:22 Mux27 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX28:2;                     // 25:24 Mux28 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX29:2;                     // 27:26 Mux29 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX30:2;                     // 29:28 Mux30 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX31:2;                     // 31:30 Mux31 Configuration for OUTPUT6 of OUTPUT-XBAR
};

union EXT64_OUTPUT6MUX16TO31CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT6MUX16TO31CFG_BITS  bit;
};

struct EXT64_OUTPUT6MUX32TO47CFG_BITS {       // bits description
    Uint16 MUX32:2;                     // 1:0 MUX32 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX33:2;                     // 3:2 MUX33 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX34:2;                     // 5:4 MUX34 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX35:2;                     // 7:6 MUX35 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX36:2;                     // 9:8 MUX36 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX37:2;                     // 11:10 MUX37 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX38:2;                     // 13:12 MUX38 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX39:2;                     // 15:14 MUX39 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX40:2;                     // 17:16 MUX40 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX41:2;                     // 19:18 MUX41 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX42:2;                     // 21:20 MUX42 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX43:2;                     // 23:22 MUX43 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX44:2;                     // 25:24 MUX44 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX45:2;                     // 27:26 MUX45 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX46:2;                     // 29:28 MUX46 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX47:2;                     // 31:30 MUX47 Configuration for OUTPUT6 of OUTPUT-XBAR
};

union EXT64_OUTPUT6MUX32TO47CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT6MUX32TO47CFG_BITS  bit;
};

struct EXT64_OUTPUT6MUX48TO63CFG_BITS {       // bits description
    Uint16 MUX48:2;                     // 1:0 MUX48 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX49:2;                     // 3:2 MUX49 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX50:2;                     // 5:4 MUX50 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX51:2;                     // 7:6 MUX51 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX52:2;                     // 9:8 MUX52 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX53:2;                     // 11:10 MUX53 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX54:2;                     // 13:12 MUX54 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX55:2;                     // 15:14 MUX55 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX56:2;                     // 17:16 MUX56 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX57:2;                     // 19:18 MUX57 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX58:2;                     // 21:20 MUX58 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX59:2;                     // 23:22 MUX59 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX60:2;                     // 25:24 MUX60 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX61:2;                     // 27:26 MUX61 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX62:2;                     // 29:28 MUX62 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX63:2;                     // 31:30 MUX63 Configuration for OUTPUT6 of OUTPUT-XBAR
};

union EXT64_OUTPUT6MUX48TO63CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT6MUX48TO63CFG_BITS  bit;
};

struct EXT64_OUTPUT7MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 Mux0 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX1:2;                      // 3:2 Mux1 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX2:2;                      // 5:4 Mux2 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX3:2;                      // 7:6 Mux3 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX4:2;                      // 9:8 Mux4 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX5:2;                      // 11:10 Mux5 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX6:2;                      // 13:12 Mux6 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX7:2;                      // 15:14 Mux7 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX8:2;                      // 17:16 Mux8 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX9:2;                      // 19:18 Mux9 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX10:2;                     // 21:20 Mux10 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX11:2;                     // 23:22 Mux11 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX12:2;                     // 25:24 Mux12 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX13:2;                     // 27:26 Mux13 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX14:2;                     // 29:28 Mux14 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX15:2;                     // 31:30 Mux15 Configuration for OUTPUT7 of OUTPUT-XBAR
};

union EXT64_OUTPUT7MUX0TO15CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT7MUX0TO15CFG_BITS  bit;
};

struct EXT64_OUTPUT7MUX16TO31CFG_BITS {       // bits description
    Uint16 MUX16:2;                     // 1:0 Mux16 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX17:2;                     // 3:2 Mux17 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX18:2;                     // 5:4 Mux18 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX19:2;                     // 7:6 Mux19 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX20:2;                     // 9:8 Mux20 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX21:2;                     // 11:10 Mux21 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX22:2;                     // 13:12 Mux22 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX23:2;                     // 15:14 Mux23 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX24:2;                     // 17:16 Mux24 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX25:2;                     // 19:18 Mux25 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX26:2;                     // 21:20 Mux26 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX27:2;                     // 23:22 Mux27 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX28:2;                     // 25:24 Mux28 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX29:2;                     // 27:26 Mux29 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX30:2;                     // 29:28 Mux30 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX31:2;                     // 31:30 Mux31 Configuration for OUTPUT7 of OUTPUT-XBAR
};

union EXT64_OUTPUT7MUX16TO31CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT7MUX16TO31CFG_BITS  bit;
};

struct EXT64_OUTPUT7MUX32TO47CFG_BITS {       // bits description
    Uint16 MUX32:2;                     // 1:0 MUX32 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX33:2;                     // 3:2 MUX33 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX34:2;                     // 5:4 MUX34 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX35:2;                     // 7:6 MUX35 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX36:2;                     // 9:8 MUX36 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX37:2;                     // 11:10 MUX37 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX38:2;                     // 13:12 MUX38 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX39:2;                     // 15:14 MUX39 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX40:2;                     // 17:16 MUX40 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX41:2;                     // 19:18 MUX41 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX42:2;                     // 21:20 MUX42 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX43:2;                     // 23:22 MUX43 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX44:2;                     // 25:24 MUX44 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX45:2;                     // 27:26 MUX45 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX46:2;                     // 29:28 MUX46 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX47:2;                     // 31:30 MUX47 Configuration for OUTPUT7 of OUTPUT-XBAR
};

union EXT64_OUTPUT7MUX32TO47CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT7MUX32TO47CFG_BITS  bit;
};

struct EXT64_OUTPUT7MUX48TO63CFG_BITS {       // bits description
    Uint16 MUX48:2;                     // 1:0 MUX48 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX49:2;                     // 3:2 MUX49 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX50:2;                     // 5:4 MUX50 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX51:2;                     // 7:6 MUX51 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX52:2;                     // 9:8 MUX52 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX53:2;                     // 11:10 MUX53 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX54:2;                     // 13:12 MUX54 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX55:2;                     // 15:14 MUX55 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX56:2;                     // 17:16 MUX56 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX57:2;                     // 19:18 MUX57 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX58:2;                     // 21:20 MUX58 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX59:2;                     // 23:22 MUX59 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX60:2;                     // 25:24 MUX60 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX61:2;                     // 27:26 MUX61 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX62:2;                     // 29:28 MUX62 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX63:2;                     // 31:30 MUX63 Configuration for OUTPUT7 of OUTPUT-XBAR
};

union EXT64_OUTPUT7MUX48TO63CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT7MUX48TO63CFG_BITS  bit;
};

struct EXT64_OUTPUT8MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 Mux0 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX1:2;                      // 3:2 Mux1 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX2:2;                      // 5:4 Mux2 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX3:2;                      // 7:6 Mux3 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX4:2;                      // 9:8 Mux4 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX5:2;                      // 11:10 Mux5 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX6:2;                      // 13:12 Mux6 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX7:2;                      // 15:14 Mux7 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX8:2;                      // 17:16 Mux8 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX9:2;                      // 19:18 Mux9 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX10:2;                     // 21:20 Mux10 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX11:2;                     // 23:22 Mux11 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX12:2;                     // 25:24 Mux12 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX13:2;                     // 27:26 Mux13 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX14:2;                     // 29:28 Mux14 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX15:2;                     // 31:30 Mux15 Configuration for OUTPUT8 of OUTPUT-XBAR
};

union EXT64_OUTPUT8MUX0TO15CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT8MUX0TO15CFG_BITS  bit;
};

struct EXT64_OUTPUT8MUX16TO31CFG_BITS {       // bits description
    Uint16 MUX16:2;                     // 1:0 Mux16 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX17:2;                     // 3:2 Mux17 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX18:2;                     // 5:4 Mux18 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX19:2;                     // 7:6 Mux19 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX20:2;                     // 9:8 Mux20 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX21:2;                     // 11:10 Mux21 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX22:2;                     // 13:12 Mux22 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX23:2;                     // 15:14 Mux23 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX24:2;                     // 17:16 Mux24 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX25:2;                     // 19:18 Mux25 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX26:2;                     // 21:20 Mux26 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX27:2;                     // 23:22 Mux27 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX28:2;                     // 25:24 Mux28 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX29:2;                     // 27:26 Mux29 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX30:2;                     // 29:28 Mux30 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX31:2;                     // 31:30 Mux31 Configuration for OUTPUT8 of OUTPUT-XBAR
};

union EXT64_OUTPUT8MUX16TO31CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT8MUX16TO31CFG_BITS  bit;
};

struct EXT64_OUTPUT8MUX32TO47CFG_BITS {       // bits description
    Uint16 MUX32:2;                     // 1:0 MUX32 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX33:2;                     // 3:2 MUX33 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX34:2;                     // 5:4 MUX34 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX35:2;                     // 7:6 MUX35 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX36:2;                     // 9:8 MUX36 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX37:2;                     // 11:10 MUX37 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX38:2;                     // 13:12 MUX38 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX39:2;                     // 15:14 MUX39 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX40:2;                     // 17:16 MUX40 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX41:2;                     // 19:18 MUX41 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX42:2;                     // 21:20 MUX42 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX43:2;                     // 23:22 MUX43 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX44:2;                     // 25:24 MUX44 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX45:2;                     // 27:26 MUX45 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX46:2;                     // 29:28 MUX46 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX47:2;                     // 31:30 MUX47 Configuration for OUTPUT8 of OUTPUT-XBAR
};

union EXT64_OUTPUT8MUX32TO47CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT8MUX32TO47CFG_BITS  bit;
};

struct EXT64_OUTPUT8MUX48TO63CFG_BITS {       // bits description
    Uint16 MUX48:2;                     // 1:0 MUX48 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX49:2;                     // 3:2 MUX49 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX50:2;                     // 5:4 MUX50 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX51:2;                     // 7:6 MUX51 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX52:2;                     // 9:8 MUX52 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX53:2;                     // 11:10 MUX53 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX54:2;                     // 13:12 MUX54 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX55:2;                     // 15:14 MUX55 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX56:2;                     // 17:16 MUX56 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX57:2;                     // 19:18 MUX57 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX58:2;                     // 21:20 MUX58 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX59:2;                     // 23:22 MUX59 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX60:2;                     // 25:24 MUX60 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX61:2;                     // 27:26 MUX61 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX62:2;                     // 29:28 MUX62 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX63:2;                     // 31:30 MUX63 Configuration for OUTPUT8 of OUTPUT-XBAR
};

union EXT64_OUTPUT8MUX48TO63CFG_REG {
    Uint32  all;
    struct  EXT64_OUTPUT8MUX48TO63CFG_BITS  bit;
};

struct EXT64_OUTPUT1MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 Mux0 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX1:1;                      // 1 Mux1 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX2:1;                      // 2 Mux2 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX3:1;                      // 3 Mux3 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX4:1;                      // 4 Mux4 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX5:1;                      // 5 Mux5 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX6:1;                      // 6 Mux6 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX7:1;                      // 7 Mux7 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX8:1;                      // 8 Mux8 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX9:1;                      // 9 Mux9 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX10:1;                     // 10 Mux10 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX11:1;                     // 11 Mux11 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX12:1;                     // 12 Mux12 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX13:1;                     // 13 Mux13 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX14:1;                     // 14 Mux14 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX15:1;                     // 15 Mux15 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX16:1;                     // 16 Mux16 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX17:1;                     // 17 Mux17 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX18:1;                     // 18 Mux18 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX19:1;                     // 19 Mux19 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX20:1;                     // 20 Mux20 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX21:1;                     // 21 Mux21 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX22:1;                     // 22 Mux22 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX23:1;                     // 23 Mux23 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX24:1;                     // 24 Mux24 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX25:1;                     // 25 Mux25 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX26:1;                     // 26 Mux26 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX27:1;                     // 27 Mux27 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX28:1;                     // 28 Mux28 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX29:1;                     // 29 Mux29 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX30:1;                     // 30 Mux30 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX31:1;                     // 31 Mux31 to drive OUTPUT1 of OUTPUT-XBAR
};

union EXT64_OUTPUT1MUXENABLE_REG {
    Uint32  all;
    struct  EXT64_OUTPUT1MUXENABLE_BITS  bit;
};

struct EXT64_OUTPUT1MUXENABLE32TO63_BITS {    // bits description
    Uint16 MUX32:1;                     // 0 MUX32 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX33:1;                     // 1 MUX33 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX34:1;                     // 2 MUX34 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX35:1;                     // 3 MUX35 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX36:1;                     // 4 MUX36 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX37:1;                     // 5 MUX37 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX38:1;                     // 6 MUX38 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX39:1;                     // 7 MUX39 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX40:1;                     // 8 MUX40 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX41:1;                     // 9 MUX41 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX42:1;                     // 10 MUX42 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX43:1;                     // 11 MUX43 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX44:1;                     // 12 MUX44 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX45:1;                     // 13 MUX45 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX46:1;                     // 14 MUX46 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX47:1;                     // 15 MUX47 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX48:1;                     // 16 MUX48 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX49:1;                     // 17 MUX49 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX50:1;                     // 18 MUX50 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX51:1;                     // 19 MUX51 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX52:1;                     // 20 MUX52 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX53:1;                     // 21 MUX53 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX54:1;                     // 22 MUX54 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX55:1;                     // 23 MUX55 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX56:1;                     // 24 MUX56 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX57:1;                     // 25 MUX57 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX58:1;                     // 26 MUX58 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX59:1;                     // 27 MUX59 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX60:1;                     // 28 MUX60 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX61:1;                     // 29 MUX61 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX62:1;                     // 30 MUX62 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX63:1;                     // 31 MUX63 to drive OUTPUT1 of OUTPUT-XBAR
};

union EXT64_OUTPUT1MUXENABLE32TO63_REG {
    Uint32  all;
    struct  EXT64_OUTPUT1MUXENABLE32TO63_BITS  bit;
};

struct EXT64_OUTPUT2MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 Mux0 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX1:1;                      // 1 Mux1 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX2:1;                      // 2 Mux2 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX3:1;                      // 3 Mux3 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX4:1;                      // 4 Mux4 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX5:1;                      // 5 Mux5 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX6:1;                      // 6 Mux6 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX7:1;                      // 7 Mux7 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX8:1;                      // 8 Mux8 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX9:1;                      // 9 Mux9 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX10:1;                     // 10 Mux10 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX11:1;                     // 11 Mux11 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX12:1;                     // 12 Mux12 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX13:1;                     // 13 Mux13 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX14:1;                     // 14 Mux14 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX15:1;                     // 15 Mux15 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX16:1;                     // 16 Mux16 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX17:1;                     // 17 Mux17 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX18:1;                     // 18 Mux18 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX19:1;                     // 19 Mux19 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX20:1;                     // 20 Mux20 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX21:1;                     // 21 Mux21 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX22:1;                     // 22 Mux22 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX23:1;                     // 23 Mux23 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX24:1;                     // 24 Mux24 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX25:1;                     // 25 Mux25 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX26:1;                     // 26 Mux26 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX27:1;                     // 27 Mux27 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX28:1;                     // 28 Mux28 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX29:1;                     // 29 Mux29 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX30:1;                     // 30 Mux30 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX31:1;                     // 31 Mux31 to drive OUTPUT2 of OUTPUT-XBAR
};

union EXT64_OUTPUT2MUXENABLE_REG {
    Uint32  all;
    struct  EXT64_OUTPUT2MUXENABLE_BITS  bit;
};

struct EXT64_OUTPUT2MUXENABLE32TO63_BITS {    // bits description
    Uint16 MUX32:1;                     // 0 MUX32 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX33:1;                     // 1 MUX33 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX34:1;                     // 2 MUX34 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX35:1;                     // 3 MUX35 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX36:1;                     // 4 MUX36 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX37:1;                     // 5 MUX37 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX38:1;                     // 6 MUX38 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX39:1;                     // 7 MUX39 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX40:1;                     // 8 MUX40 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX41:1;                     // 9 MUX41 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX42:1;                     // 10 MUX42 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX43:1;                     // 11 MUX43 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX44:1;                     // 12 MUX44 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX45:1;                     // 13 MUX45 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX46:1;                     // 14 MUX46 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX47:1;                     // 15 MUX47 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX48:1;                     // 16 MUX48 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX49:1;                     // 17 MUX49 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX50:1;                     // 18 MUX50 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX51:1;                     // 19 MUX51 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX52:1;                     // 20 MUX52 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX53:1;                     // 21 MUX53 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX54:1;                     // 22 MUX54 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX55:1;                     // 23 MUX55 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX56:1;                     // 24 MUX56 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX57:1;                     // 25 MUX57 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX58:1;                     // 26 MUX58 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX59:1;                     // 27 MUX59 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX60:1;                     // 28 MUX60 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX61:1;                     // 29 MUX61 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX62:1;                     // 30 MUX62 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX63:1;                     // 31 MUX63 to drive OUTPUT2 of OUTPUT-XBAR
};

union EXT64_OUTPUT2MUXENABLE32TO63_REG {
    Uint32  all;
    struct  EXT64_OUTPUT2MUXENABLE32TO63_BITS  bit;
};

struct EXT64_OUTPUT3MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 Mux0 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX1:1;                      // 1 Mux1 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX2:1;                      // 2 Mux2 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX3:1;                      // 3 Mux3 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX4:1;                      // 4 Mux4 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX5:1;                      // 5 Mux5 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX6:1;                      // 6 Mux6 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX7:1;                      // 7 Mux7 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX8:1;                      // 8 Mux8 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX9:1;                      // 9 Mux9 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX10:1;                     // 10 Mux10 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX11:1;                     // 11 Mux11 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX12:1;                     // 12 Mux12 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX13:1;                     // 13 Mux13 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX14:1;                     // 14 Mux14 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX15:1;                     // 15 Mux15 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX16:1;                     // 16 Mux16 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX17:1;                     // 17 Mux17 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX18:1;                     // 18 Mux18 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX19:1;                     // 19 Mux19 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX20:1;                     // 20 Mux20 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX21:1;                     // 21 Mux21 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX22:1;                     // 22 Mux22 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX23:1;                     // 23 Mux23 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX24:1;                     // 24 Mux24 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX25:1;                     // 25 Mux25 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX26:1;                     // 26 Mux26 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX27:1;                     // 27 Mux27 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX28:1;                     // 28 Mux28 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX29:1;                     // 29 Mux29 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX30:1;                     // 30 Mux30 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX31:1;                     // 31 Mux31 to drive OUTPUT3 of OUTPUT-XBAR
};

union EXT64_OUTPUT3MUXENABLE_REG {
    Uint32  all;
    struct  EXT64_OUTPUT3MUXENABLE_BITS  bit;
};

struct EXT64_OUTPUT3MUXENABLE32TO63_BITS {    // bits description
    Uint16 MUX32:1;                     // 0 MUX32 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX33:1;                     // 1 MUX33 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX34:1;                     // 2 MUX34 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX35:1;                     // 3 MUX35 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX36:1;                     // 4 MUX36 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX37:1;                     // 5 MUX37 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX38:1;                     // 6 MUX38 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX39:1;                     // 7 MUX39 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX40:1;                     // 8 MUX40 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX41:1;                     // 9 MUX41 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX42:1;                     // 10 MUX42 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX43:1;                     // 11 MUX43 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX44:1;                     // 12 MUX44 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX45:1;                     // 13 MUX45 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX46:1;                     // 14 MUX46 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX47:1;                     // 15 MUX47 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX48:1;                     // 16 MUX48 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX49:1;                     // 17 MUX49 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX50:1;                     // 18 MUX50 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX51:1;                     // 19 MUX51 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX52:1;                     // 20 MUX52 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX53:1;                     // 21 MUX53 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX54:1;                     // 22 MUX54 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX55:1;                     // 23 MUX55 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX56:1;                     // 24 MUX56 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX57:1;                     // 25 MUX57 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX58:1;                     // 26 MUX58 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX59:1;                     // 27 MUX59 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX60:1;                     // 28 MUX60 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX61:1;                     // 29 MUX61 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX62:1;                     // 30 MUX62 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX63:1;                     // 31 MUX63 to drive OUTPUT3 of OUTPUT-XBAR
};

union EXT64_OUTPUT3MUXENABLE32TO63_REG {
    Uint32  all;
    struct  EXT64_OUTPUT3MUXENABLE32TO63_BITS  bit;
};

struct EXT64_OUTPUT4MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 Mux0 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX1:1;                      // 1 Mux1 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX2:1;                      // 2 Mux2 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX3:1;                      // 3 Mux3 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX4:1;                      // 4 Mux4 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX5:1;                      // 5 Mux5 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX6:1;                      // 6 Mux6 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX7:1;                      // 7 Mux7 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX8:1;                      // 8 Mux8 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX9:1;                      // 9 Mux9 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX10:1;                     // 10 Mux10 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX11:1;                     // 11 Mux11 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX12:1;                     // 12 Mux12 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX13:1;                     // 13 Mux13 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX14:1;                     // 14 Mux14 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX15:1;                     // 15 Mux15 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX16:1;                     // 16 Mux16 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX17:1;                     // 17 Mux17 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX18:1;                     // 18 Mux18 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX19:1;                     // 19 Mux19 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX20:1;                     // 20 Mux20 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX21:1;                     // 21 Mux21 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX22:1;                     // 22 Mux22 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX23:1;                     // 23 Mux23 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX24:1;                     // 24 Mux24 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX25:1;                     // 25 Mux25 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX26:1;                     // 26 Mux26 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX27:1;                     // 27 Mux27 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX28:1;                     // 28 Mux28 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX29:1;                     // 29 Mux29 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX30:1;                     // 30 Mux30 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX31:1;                     // 31 Mux31 to drive OUTPUT4 of OUTPUT-XBAR
};

union EXT64_OUTPUT4MUXENABLE_REG {
    Uint32  all;
    struct  EXT64_OUTPUT4MUXENABLE_BITS  bit;
};

struct EXT64_OUTPUT4MUXENABLE32TO63_BITS {    // bits description
    Uint16 MUX32:1;                     // 0 MUX32 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX33:1;                     // 1 MUX33 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX34:1;                     // 2 MUX34 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX35:1;                     // 3 MUX35 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX36:1;                     // 4 MUX36 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX37:1;                     // 5 MUX37 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX38:1;                     // 6 MUX38 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX39:1;                     // 7 MUX39 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX40:1;                     // 8 MUX40 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX41:1;                     // 9 MUX41 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX42:1;                     // 10 MUX42 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX43:1;                     // 11 MUX43 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX44:1;                     // 12 MUX44 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX45:1;                     // 13 MUX45 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX46:1;                     // 14 MUX46 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX47:1;                     // 15 MUX47 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX48:1;                     // 16 MUX48 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX49:1;                     // 17 MUX49 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX50:1;                     // 18 MUX50 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX51:1;                     // 19 MUX51 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX52:1;                     // 20 MUX52 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX53:1;                     // 21 MUX53 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX54:1;                     // 22 MUX54 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX55:1;                     // 23 MUX55 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX56:1;                     // 24 MUX56 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX57:1;                     // 25 MUX57 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX58:1;                     // 26 MUX58 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX59:1;                     // 27 MUX59 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX60:1;                     // 28 MUX60 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX61:1;                     // 29 MUX61 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX62:1;                     // 30 MUX62 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX63:1;                     // 31 MUX63 to drive OUTPUT4 of OUTPUT-XBAR
};

union EXT64_OUTPUT4MUXENABLE32TO63_REG {
    Uint32  all;
    struct  EXT64_OUTPUT4MUXENABLE32TO63_BITS  bit;
};

struct EXT64_OUTPUT5MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 Mux0 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX1:1;                      // 1 Mux1 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX2:1;                      // 2 Mux2 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX3:1;                      // 3 Mux3 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX4:1;                      // 4 Mux4 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX5:1;                      // 5 Mux5 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX6:1;                      // 6 Mux6 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX7:1;                      // 7 Mux7 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX8:1;                      // 8 Mux8 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX9:1;                      // 9 Mux9 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX10:1;                     // 10 Mux10 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX11:1;                     // 11 Mux11 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX12:1;                     // 12 Mux12 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX13:1;                     // 13 Mux13 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX14:1;                     // 14 Mux14 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX15:1;                     // 15 Mux15 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX16:1;                     // 16 Mux16 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX17:1;                     // 17 Mux17 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX18:1;                     // 18 Mux18 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX19:1;                     // 19 Mux19 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX20:1;                     // 20 Mux20 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX21:1;                     // 21 Mux21 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX22:1;                     // 22 Mux22 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX23:1;                     // 23 Mux23 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX24:1;                     // 24 Mux24 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX25:1;                     // 25 Mux25 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX26:1;                     // 26 Mux26 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX27:1;                     // 27 Mux27 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX28:1;                     // 28 Mux28 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX29:1;                     // 29 Mux29 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX30:1;                     // 30 Mux30 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX31:1;                     // 31 Mux31 to drive OUTPUT5 of OUTPUT-XBAR
};

union EXT64_OUTPUT5MUXENABLE_REG {
    Uint32  all;
    struct  EXT64_OUTPUT5MUXENABLE_BITS  bit;
};

struct EXT64_OUTPUT5MUXENABLE32TO63_BITS {    // bits description
    Uint16 MUX32:1;                     // 0 MUX32 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX33:1;                     // 1 MUX33 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX34:1;                     // 2 MUX34 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX35:1;                     // 3 MUX35 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX36:1;                     // 4 MUX36 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX37:1;                     // 5 MUX37 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX38:1;                     // 6 MUX38 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX39:1;                     // 7 MUX39 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX40:1;                     // 8 MUX40 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX41:1;                     // 9 MUX41 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX42:1;                     // 10 MUX42 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX43:1;                     // 11 MUX43 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX44:1;                     // 12 MUX44 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX45:1;                     // 13 MUX45 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX46:1;                     // 14 MUX46 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX47:1;                     // 15 MUX47 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX48:1;                     // 16 MUX48 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX49:1;                     // 17 MUX49 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX50:1;                     // 18 MUX50 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX51:1;                     // 19 MUX51 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX52:1;                     // 20 MUX52 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX53:1;                     // 21 MUX53 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX54:1;                     // 22 MUX54 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX55:1;                     // 23 MUX55 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX56:1;                     // 24 MUX56 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX57:1;                     // 25 MUX57 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX58:1;                     // 26 MUX58 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX59:1;                     // 27 MUX59 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX60:1;                     // 28 MUX60 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX61:1;                     // 29 MUX61 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX62:1;                     // 30 MUX62 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX63:1;                     // 31 MUX63 to drive OUTPUT5 of OUTPUT-XBAR
};

union EXT64_OUTPUT5MUXENABLE32TO63_REG {
    Uint32  all;
    struct  EXT64_OUTPUT5MUXENABLE32TO63_BITS  bit;
};

struct EXT64_OUTPUT6MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 Mux0 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX1:1;                      // 1 Mux1 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX2:1;                      // 2 Mux2 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX3:1;                      // 3 Mux3 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX4:1;                      // 4 Mux4 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX5:1;                      // 5 Mux5 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX6:1;                      // 6 Mux6 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX7:1;                      // 7 Mux7 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX8:1;                      // 8 Mux8 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX9:1;                      // 9 Mux9 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX10:1;                     // 10 Mux10 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX11:1;                     // 11 Mux11 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX12:1;                     // 12 Mux12 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX13:1;                     // 13 Mux13 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX14:1;                     // 14 Mux14 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX15:1;                     // 15 Mux15 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX16:1;                     // 16 Mux16 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX17:1;                     // 17 Mux17 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX18:1;                     // 18 Mux18 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX19:1;                     // 19 Mux19 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX20:1;                     // 20 Mux20 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX21:1;                     // 21 Mux21 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX22:1;                     // 22 Mux22 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX23:1;                     // 23 Mux23 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX24:1;                     // 24 Mux24 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX25:1;                     // 25 Mux25 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX26:1;                     // 26 Mux26 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX27:1;                     // 27 Mux27 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX28:1;                     // 28 Mux28 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX29:1;                     // 29 Mux29 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX30:1;                     // 30 Mux30 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX31:1;                     // 31 Mux31 to drive OUTPUT6 of OUTPUT-XBAR
};

union EXT64_OUTPUT6MUXENABLE_REG {
    Uint32  all;
    struct  EXT64_OUTPUT6MUXENABLE_BITS  bit;
};

struct EXT64_OUTPUT6MUXENABLE32TO63_BITS {    // bits description
    Uint16 MUX32:1;                     // 0 MUX32 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX33:1;                     // 1 MUX33 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX34:1;                     // 2 MUX34 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX35:1;                     // 3 MUX35 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX36:1;                     // 4 MUX36 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX37:1;                     // 5 MUX37 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX38:1;                     // 6 MUX38 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX39:1;                     // 7 MUX39 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX40:1;                     // 8 MUX40 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX41:1;                     // 9 MUX41 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX42:1;                     // 10 MUX42 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX43:1;                     // 11 MUX43 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX44:1;                     // 12 MUX44 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX45:1;                     // 13 MUX45 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX46:1;                     // 14 MUX46 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX47:1;                     // 15 MUX47 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX48:1;                     // 16 MUX48 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX49:1;                     // 17 MUX49 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX50:1;                     // 18 MUX50 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX51:1;                     // 19 MUX51 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX52:1;                     // 20 MUX52 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX53:1;                     // 21 MUX53 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX54:1;                     // 22 MUX54 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX55:1;                     // 23 MUX55 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX56:1;                     // 24 MUX56 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX57:1;                     // 25 MUX57 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX58:1;                     // 26 MUX58 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX59:1;                     // 27 MUX59 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX60:1;                     // 28 MUX60 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX61:1;                     // 29 MUX61 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX62:1;                     // 30 MUX62 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX63:1;                     // 31 MUX63 to drive OUTPUT6 of OUTPUT-XBAR
};

union EXT64_OUTPUT6MUXENABLE32TO63_REG {
    Uint32  all;
    struct  EXT64_OUTPUT6MUXENABLE32TO63_BITS  bit;
};

struct EXT64_OUTPUT7MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 Mux0 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX1:1;                      // 1 Mux1 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX2:1;                      // 2 Mux2 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX3:1;                      // 3 Mux3 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX4:1;                      // 4 Mux4 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX5:1;                      // 5 Mux5 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX6:1;                      // 6 Mux6 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX7:1;                      // 7 Mux7 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX8:1;                      // 8 Mux8 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX9:1;                      // 9 Mux9 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX10:1;                     // 10 Mux10 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX11:1;                     // 11 Mux11 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX12:1;                     // 12 Mux12 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX13:1;                     // 13 Mux13 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX14:1;                     // 14 Mux14 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX15:1;                     // 15 Mux15 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX16:1;                     // 16 Mux16 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX17:1;                     // 17 Mux17 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX18:1;                     // 18 Mux18 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX19:1;                     // 19 Mux19 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX20:1;                     // 20 Mux20 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX21:1;                     // 21 Mux21 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX22:1;                     // 22 Mux22 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX23:1;                     // 23 Mux23 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX24:1;                     // 24 Mux24 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX25:1;                     // 25 Mux25 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX26:1;                     // 26 Mux26 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX27:1;                     // 27 Mux27 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX28:1;                     // 28 Mux28 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX29:1;                     // 29 Mux29 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX30:1;                     // 30 Mux30 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX31:1;                     // 31 Mux31 to drive OUTPUT7 of OUTPUT-XBAR
};

union EXT64_OUTPUT7MUXENABLE_REG {
    Uint32  all;
    struct  EXT64_OUTPUT7MUXENABLE_BITS  bit;
};

struct EXT64_OUTPUT7MUXENABLE32TO63_BITS {    // bits description
    Uint16 MUX32:1;                     // 0 MUX32 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX33:1;                     // 1 MUX33 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX34:1;                     // 2 MUX34 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX35:1;                     // 3 MUX35 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX36:1;                     // 4 MUX36 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX37:1;                     // 5 MUX37 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX38:1;                     // 6 MUX38 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX39:1;                     // 7 MUX39 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX40:1;                     // 8 MUX40 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX41:1;                     // 9 MUX41 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX42:1;                     // 10 MUX42 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX43:1;                     // 11 MUX43 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX44:1;                     // 12 MUX44 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX45:1;                     // 13 MUX45 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX46:1;                     // 14 MUX46 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX47:1;                     // 15 MUX47 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX48:1;                     // 16 MUX48 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX49:1;                     // 17 MUX49 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX50:1;                     // 18 MUX50 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX51:1;                     // 19 MUX51 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX52:1;                     // 20 MUX52 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX53:1;                     // 21 MUX53 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX54:1;                     // 22 MUX54 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX55:1;                     // 23 MUX55 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX56:1;                     // 24 MUX56 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX57:1;                     // 25 MUX57 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX58:1;                     // 26 MUX58 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX59:1;                     // 27 MUX59 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX60:1;                     // 28 MUX60 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX61:1;                     // 29 MUX61 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX62:1;                     // 30 MUX62 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX63:1;                     // 31 MUX63 to drive OUTPUT7 of OUTPUT-XBAR
};

union EXT64_OUTPUT7MUXENABLE32TO63_REG {
    Uint32  all;
    struct  EXT64_OUTPUT7MUXENABLE32TO63_BITS  bit;
};

struct EXT64_OUTPUT8MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 Mux0 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX1:1;                      // 1 Mux1 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX2:1;                      // 2 Mux2 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX3:1;                      // 3 Mux3 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX4:1;                      // 4 Mux4 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX5:1;                      // 5 Mux5 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX6:1;                      // 6 Mux6 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX7:1;                      // 7 Mux7 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX8:1;                      // 8 Mux8 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX9:1;                      // 9 Mux9 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX10:1;                     // 10 Mux10 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX11:1;                     // 11 Mux11 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX12:1;                     // 12 Mux12 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX13:1;                     // 13 Mux13 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX14:1;                     // 14 Mux14 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX15:1;                     // 15 Mux15 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX16:1;                     // 16 Mux16 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX17:1;                     // 17 Mux17 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX18:1;                     // 18 Mux18 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX19:1;                     // 19 Mux19 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX20:1;                     // 20 Mux20 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX21:1;                     // 21 Mux21 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX22:1;                     // 22 Mux22 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX23:1;                     // 23 Mux23 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX24:1;                     // 24 Mux24 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX25:1;                     // 25 Mux25 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX26:1;                     // 26 Mux26 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX27:1;                     // 27 Mux27 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX28:1;                     // 28 Mux28 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX29:1;                     // 29 Mux29 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX30:1;                     // 30 Mux30 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX31:1;                     // 31 Mux31 to drive OUTPUT8 of OUTPUT-XBAR
};

union EXT64_OUTPUT8MUXENABLE_REG {
    Uint32  all;
    struct  EXT64_OUTPUT8MUXENABLE_BITS  bit;
};

struct EXT64_OUTPUT8MUXENABLE32TO63_BITS {    // bits description
    Uint16 MUX32:1;                     // 0 MUX32 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX33:1;                     // 1 MUX33 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX34:1;                     // 2 MUX34 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX35:1;                     // 3 MUX35 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX36:1;                     // 4 MUX36 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX37:1;                     // 5 MUX37 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX38:1;                     // 6 MUX38 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX39:1;                     // 7 MUX39 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX40:1;                     // 8 MUX40 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX41:1;                     // 9 MUX41 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX42:1;                     // 10 MUX42 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX43:1;                     // 11 MUX43 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX44:1;                     // 12 MUX44 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX45:1;                     // 13 MUX45 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX46:1;                     // 14 MUX46 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX47:1;                     // 15 MUX47 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX48:1;                     // 16 MUX48 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX49:1;                     // 17 MUX49 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX50:1;                     // 18 MUX50 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX51:1;                     // 19 MUX51 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX52:1;                     // 20 MUX52 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX53:1;                     // 21 MUX53 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX54:1;                     // 22 MUX54 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX55:1;                     // 23 MUX55 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX56:1;                     // 24 MUX56 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX57:1;                     // 25 MUX57 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX58:1;                     // 26 MUX58 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX59:1;                     // 27 MUX59 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX60:1;                     // 28 MUX60 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX61:1;                     // 29 MUX61 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX62:1;                     // 30 MUX62 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX63:1;                     // 31 MUX63 to drive OUTPUT8 of OUTPUT-XBAR
};

union EXT64_OUTPUT8MUXENABLE32TO63_REG {
    Uint32  all;
    struct  EXT64_OUTPUT8MUXENABLE32TO63_BITS  bit;
};

struct EXT64_OUTPUTLATCH_BITS {               // bits description
    Uint16 OUTPUT1:1;                   // 0 Records the OUTPUT1 of OUTPUT-XBAR
    Uint16 OUTPUT2:1;                   // 1 Records the OUTPUT2 of OUTPUT-XBAR
    Uint16 OUTPUT3:1;                   // 2 Records the OUTPUT3 of OUTPUT-XBAR
    Uint16 OUTPUT4:1;                   // 3 Records the OUTPUT4 of OUTPUT-XBAR
    Uint16 OUTPUT5:1;                   // 4 Records the OUTPUT5 of OUTPUT-XBAR
    Uint16 OUTPUT6:1;                   // 5 Records the OUTPUT6 of OUTPUT-XBAR
    Uint16 OUTPUT7:1;                   // 6 Records the OUTPUT7 of OUTPUT-XBAR
    Uint16 OUTPUT8:1;                   // 7 Records the OUTPUT8 of OUTPUT-XBAR
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EXT64_OUTPUTLATCH_REG {
    Uint32  all;
    struct  EXT64_OUTPUTLATCH_BITS  bit;
};

struct EXT64_OUTPUTLATCHCLR_BITS {            // bits description
    Uint16 OUTPUT1:1;                   // 0 Clears the Output-Latch for OUTPUT1 of OUTPUT-XBAR
    Uint16 OUTPUT2:1;                   // 1 Clears the Output-Latch for OUTPUT2 of OUTPUT-XBAR
    Uint16 OUTPUT3:1;                   // 2 Clears the Output-Latch for OUTPUT3 of OUTPUT-XBAR
    Uint16 OUTPUT4:1;                   // 3 Clears the Output-Latch for OUTPUT4 of OUTPUT-XBAR
    Uint16 OUTPUT5:1;                   // 4 Clears the Output-Latch for OUTPUT5 of OUTPUT-XBAR
    Uint16 OUTPUT6:1;                   // 5 Clears the Output-Latch for OUTPUT6 of OUTPUT-XBAR
    Uint16 OUTPUT7:1;                   // 6 Clears the Output-Latch for OUTPUT7 of OUTPUT-XBAR
    Uint16 OUTPUT8:1;                   // 7 Clears the Output-Latch for OUTPUT8 of OUTPUT-XBAR
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EXT64_OUTPUTLATCHCLR_REG {
    Uint32  all;
    struct  EXT64_OUTPUTLATCHCLR_BITS  bit;
};

struct EXT64_OUTPUTLATCHFRC_BITS {            // bits description
    Uint16 OUTPUT1:1;                   // 0 Sets the Output-Latch for OUTPUT1 of OUTPUT-XBAR
    Uint16 OUTPUT2:1;                   // 1 Sets the Output-Latch for OUTPUT2 of OUTPUT-XBAR
    Uint16 OUTPUT3:1;                   // 2 Sets the Output-Latch for OUTPUT3 of OUTPUT-XBAR
    Uint16 OUTPUT4:1;                   // 3 Sets the Output-Latch for OUTPUT4 of OUTPUT-XBAR
    Uint16 OUTPUT5:1;                   // 4 Sets the Output-Latch for OUTPUT5 of OUTPUT-XBAR
    Uint16 OUTPUT6:1;                   // 5 Sets the Output-Latch for OUTPUT6 of OUTPUT-XBAR
    Uint16 OUTPUT7:1;                   // 6 Sets the Output-Latch for OUTPUT7 of OUTPUT-XBAR
    Uint16 OUTPUT8:1;                   // 7 Sets the Output-Latch for OUTPUT8 of OUTPUT-XBAR
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EXT64_OUTPUTLATCHFRC_REG {
    Uint32  all;
    struct  EXT64_OUTPUTLATCHFRC_BITS  bit;
};

struct EXT64_OUTPUTLATCHENABLE_BITS {         // bits description
    Uint16 OUTPUT1:1;                   // 0 Selects the output latch to drive OUTPUT1 for OUTPUT-XBAR
    Uint16 OUTPUT2:1;                   // 1 Selects the output latch to drive OUTPUT2 for OUTPUT-XBAR
    Uint16 OUTPUT3:1;                   // 2 Selects the output latch to drive OUTPUT3 for OUTPUT-XBAR
    Uint16 OUTPUT4:1;                   // 3 Selects the output latch to drive OUTPUT4 for OUTPUT-XBAR
    Uint16 OUTPUT5:1;                   // 4 Selects the output latch to drive OUTPUT5 for OUTPUT-XBAR
    Uint16 OUTPUT6:1;                   // 5 Selects the output latch to drive OUTPUT6 for OUTPUT-XBAR
    Uint16 OUTPUT7:1;                   // 6 Selects the output latch to drive OUTPUT7 for OUTPUT-XBAR
    Uint16 OUTPUT8:1;                   // 7 Selects the output latch to drive OUTPUT8 for OUTPUT-XBAR
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EXT64_OUTPUTLATCHENABLE_REG {
    Uint32  all;
    struct  EXT64_OUTPUTLATCHENABLE_BITS  bit;
};

struct EXT64_OUTPUTINV_BITS {                 // bits description
    Uint16 OUTPUT1:1;                   // 0 Selects polarity for OUTPUT1 of OUTPUT-XBAR
    Uint16 OUTPUT2:1;                   // 1 Selects polarity for OUTPUT2 of OUTPUT-XBAR
    Uint16 OUTPUT3:1;                   // 2 Selects polarity for OUTPUT3 of OUTPUT-XBAR
    Uint16 OUTPUT4:1;                   // 3 Selects polarity for OUTPUT4 of OUTPUT-XBAR
    Uint16 OUTPUT5:1;                   // 4 Selects polarity for OUTPUT5 of OUTPUT-XBAR
    Uint16 OUTPUT6:1;                   // 5 Selects polarity for OUTPUT6 of OUTPUT-XBAR
    Uint16 OUTPUT7:1;                   // 6 Selects polarity for OUTPUT7 of OUTPUT-XBAR
    Uint16 OUTPUT8:1;                   // 7 Selects polarity for OUTPUT8 of OUTPUT-XBAR
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EXT64_OUTPUTINV_REG {
    Uint32  all;
    struct  EXT64_OUTPUTINV_BITS  bit;
};

struct EXT64_OUTPUTLOCK_BITS {                // bits description
    Uint16 LOCK:1;                      // 0 Locks the configuration for OUTPUT-XBAR
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 KEY:16;                      // 31:16 Write Protection KEY
};

union EXT64_OUTPUTLOCK_REG {
    Uint32  all;
    struct  EXT64_OUTPUTLOCK_BITS  bit;
};

struct OUTPUT_XBAR_EXT64_REGS {
    union   EXT64_OUTPUT1MUX0TO15CFG_REG           EXT64_OUTPUT1MUX0TO15CFG;           // Output X-BAR Mux Configuration for Output 1
    union   EXT64_OUTPUT1MUX16TO31CFG_REG          EXT64_OUTPUT1MUX16TO31CFG;          // Output X-BAR Mux Configuration for Output 1
    union   EXT64_OUTPUT1MUX32TO47CFG_REG          EXT64_OUTPUT1MUX32TO47CFG;          // Output X-BAR Mux Configuration for Output 1
    union   EXT64_OUTPUT1MUX48TO63CFG_REG          EXT64_OUTPUT1MUX48TO63CFG;          // Output X-BAR Mux Configuration for Output 1
    union   EXT64_OUTPUT2MUX0TO15CFG_REG           EXT64_OUTPUT2MUX0TO15CFG;           // Output X-BAR Mux Configuration for Output 2
    union   EXT64_OUTPUT2MUX16TO31CFG_REG          EXT64_OUTPUT2MUX16TO31CFG;          // Output X-BAR Mux Configuration for Output 2
    union   EXT64_OUTPUT2MUX32TO47CFG_REG          EXT64_OUTPUT2MUX32TO47CFG;          // Output X-BAR Mux Configuration for Output 2
    union   EXT64_OUTPUT2MUX48TO63CFG_REG          EXT64_OUTPUT2MUX48TO63CFG;          // Output X-BAR Mux Configuration for Output 2
    union   EXT64_OUTPUT3MUX0TO15CFG_REG           EXT64_OUTPUT3MUX0TO15CFG;           // Output X-BAR Mux Configuration for Output 3
    union   EXT64_OUTPUT3MUX16TO31CFG_REG          EXT64_OUTPUT3MUX16TO31CFG;          // Output X-BAR Mux Configuration for Output 3
    union   EXT64_OUTPUT3MUX32TO47CFG_REG          EXT64_OUTPUT3MUX32TO47CFG;          // Output X-BAR Mux Configuration for Output 3
    union   EXT64_OUTPUT3MUX48TO63CFG_REG          EXT64_OUTPUT3MUX48TO63CFG;          // Output X-BAR Mux Configuration for Output 3
    union   EXT64_OUTPUT4MUX0TO15CFG_REG           EXT64_OUTPUT4MUX0TO15CFG;           // Output X-BAR Mux Configuration for Output 4
    union   EXT64_OUTPUT4MUX16TO31CFG_REG          EXT64_OUTPUT4MUX16TO31CFG;          // Output X-BAR Mux Configuration for Output 4
    union   EXT64_OUTPUT4MUX32TO47CFG_REG          EXT64_OUTPUT4MUX32TO47CFG;          // Output X-BAR Mux Configuration for Output 4
    union   EXT64_OUTPUT4MUX48TO63CFG_REG          EXT64_OUTPUT4MUX48TO63CFG;          // Output X-BAR Mux Configuration for Output 4
    union   EXT64_OUTPUT5MUX0TO15CFG_REG           EXT64_OUTPUT5MUX0TO15CFG;           // Output X-BAR Mux Configuration for Output 5
    union   EXT64_OUTPUT5MUX16TO31CFG_REG          EXT64_OUTPUT5MUX16TO31CFG;          // Output X-BAR Mux Configuration for Output 5
    union   EXT64_OUTPUT5MUX32TO47CFG_REG          EXT64_OUTPUT5MUX32TO47CFG;          // Output X-BAR Mux Configuration for Output 5
    union   EXT64_OUTPUT5MUX48TO63CFG_REG          EXT64_OUTPUT5MUX48TO63CFG;          // Output X-BAR Mux Configuration for Output 5
    union   EXT64_OUTPUT6MUX0TO15CFG_REG           EXT64_OUTPUT6MUX0TO15CFG;           // Output X-BAR Mux Configuration for Output 6
    union   EXT64_OUTPUT6MUX16TO31CFG_REG          EXT64_OUTPUT6MUX16TO31CFG;          // Output X-BAR Mux Configuration for Output 6
    union   EXT64_OUTPUT6MUX32TO47CFG_REG          EXT64_OUTPUT6MUX32TO47CFG;          // Output X-BAR Mux Configuration for Output 6
    union   EXT64_OUTPUT6MUX48TO63CFG_REG          EXT64_OUTPUT6MUX48TO63CFG;          // Output X-BAR Mux Configuration for Output 6
    union   EXT64_OUTPUT7MUX0TO15CFG_REG           EXT64_OUTPUT7MUX0TO15CFG;           // Output X-BAR Mux Configuration for Output 7
    union   EXT64_OUTPUT7MUX16TO31CFG_REG          EXT64_OUTPUT7MUX16TO31CFG;          // Output X-BAR Mux Configuration for Output 7
    union   EXT64_OUTPUT7MUX32TO47CFG_REG          EXT64_OUTPUT7MUX32TO47CFG;          // Output X-BAR Mux Configuration for Output 7
    union   EXT64_OUTPUT7MUX48TO63CFG_REG          EXT64_OUTPUT7MUX48TO63CFG;          // Output X-BAR Mux Configuration for Output 7
    union   EXT64_OUTPUT8MUX0TO15CFG_REG           EXT64_OUTPUT8MUX0TO15CFG;           // Output X-BAR Mux Configuration for Output 8
    union   EXT64_OUTPUT8MUX16TO31CFG_REG          EXT64_OUTPUT8MUX16TO31CFG;          // Output X-BAR Mux Configuration for Output 8
    union   EXT64_OUTPUT8MUX32TO47CFG_REG          EXT64_OUTPUT8MUX32TO47CFG;          // Output X-BAR Mux Configuration for Output 8
    union   EXT64_OUTPUT8MUX48TO63CFG_REG          EXT64_OUTPUT8MUX48TO63CFG;          // Output X-BAR Mux Configuration for Output 8
    union   EXT64_OUTPUT1MUXENABLE_REG             EXT64_OUTPUT1MUXENABLE;             // Output X-BAR Mux Enable  for Output 1
    union   EXT64_OUTPUT1MUXENABLE32TO63_REG       EXT64_OUTPUT1MUXENABLE32TO63;       // Output X-BAR Mux Enable  for Output 1
    union   EXT64_OUTPUT2MUXENABLE_REG             EXT64_OUTPUT2MUXENABLE;             // Output X-BAR Mux Enable  for Output 2
    union   EXT64_OUTPUT2MUXENABLE32TO63_REG       EXT64_OUTPUT2MUXENABLE32TO63;       // Output X-BAR Mux Enable  for Output 2
    union   EXT64_OUTPUT3MUXENABLE_REG             EXT64_OUTPUT3MUXENABLE;             // Output X-BAR Mux Enable  for Output 3
    union   EXT64_OUTPUT3MUXENABLE32TO63_REG       EXT64_OUTPUT3MUXENABLE32TO63;       // Output X-BAR Mux Enable  for Output 3
    union   EXT64_OUTPUT4MUXENABLE_REG             EXT64_OUTPUT4MUXENABLE;             // Output X-BAR Mux Enable  for Output 4
    union   EXT64_OUTPUT4MUXENABLE32TO63_REG       EXT64_OUTPUT4MUXENABLE32TO63;       // Output X-BAR Mux Enable  for Output 4
    union   EXT64_OUTPUT5MUXENABLE_REG             EXT64_OUTPUT5MUXENABLE;             // Output X-BAR Mux Enable  for Output 5
    union   EXT64_OUTPUT5MUXENABLE32TO63_REG       EXT64_OUTPUT5MUXENABLE32TO63;       // Output X-BAR Mux Enable  for Output 5
    union   EXT64_OUTPUT6MUXENABLE_REG             EXT64_OUTPUT6MUXENABLE;             // Output X-BAR Mux Enable  for Output 6
    union   EXT64_OUTPUT6MUXENABLE32TO63_REG       EXT64_OUTPUT6MUXENABLE32TO63;       // Output X-BAR Mux Enable  for Output 6
    union   EXT64_OUTPUT7MUXENABLE_REG             EXT64_OUTPUT7MUXENABLE;             // Output X-BAR Mux Enable  for Output 7
    union   EXT64_OUTPUT7MUXENABLE32TO63_REG       EXT64_OUTPUT7MUXENABLE32TO63;       // Output X-BAR Mux Enable  for Output 7
    union   EXT64_OUTPUT8MUXENABLE_REG             EXT64_OUTPUT8MUXENABLE;             // Output X-BAR Mux Enable  for Output 8
    union   EXT64_OUTPUT8MUXENABLE32TO63_REG       EXT64_OUTPUT8MUXENABLE32TO63;       // Output X-BAR Mux Enable  for Output 8
    union   EXT64_OUTPUTLATCH_REG                  EXT64_OUTPUTLATCH;                  // Output X-BAR Output Latch
    union   EXT64_OUTPUTLATCHCLR_REG               EXT64_OUTPUTLATCHCLR;               // Output X-BAR Output Latch Clear
    union   EXT64_OUTPUTLATCHFRC_REG               EXT64_OUTPUTLATCHFRC;               // Output X-BAR Output Latch Clear
    union   EXT64_OUTPUTLATCHENABLE_REG            EXT64_OUTPUTLATCHENABLE;            // Output X-BAR Output Latch Enable
    union   EXT64_OUTPUTINV_REG                    EXT64_OUTPUTINV;                    // Output X-BAR Output Inversion
    Uint16                                         rsvd1[4];                     // Reserved
    union   EXT64_OUTPUTLOCK_REG                   EXT64_OUTPUTLOCK;                   // Output X-BAR Configuration Lock register
};

//---------------------------------------------------------------------------
// OUTPUT_XBAR External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct OUTPUT_XBAR_EXT64_REGS OutputXbarRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
