#define I_Trig_pos_start 15
#define I_Trig_pos_end 11
#define I_Opcode_pos_start 10
#define I_Opcode_pos_end 6
#define I_Src_pos_start 5
#define I_Src_pos_end 3
#define I_Dest_pos_start 2
#define I_Dest_pos_end 0
#define INSTR_ARRAY_DEPTH 31
#define INSTR_ARRAY_WIDTH 11
#define INSTR_ARRAY_INDEX 4


#define OPCODE_MOV    0x0
#define OPCODE_T1_MOV 0x1
#define OPCODE_T2_MOV 0x2
#define OPCODE_PUSH   0x3
#define OPCODE_PULL   0x4
#define OPCODE_ADD    0x5
#define OPCODE_SUB    0x6
#define OPCODE_INTR   0x7

#define REG_R0 0
#define REG_R1 1
#define REG_R2 2
#define REG_R3 3
#define REG_C0 4
#define REG_C1 5
#define REG_C2 6

//#define LINE_MAX 255

typedef struct { const char *key; unsigned long val; } t_string_struct;

//static t_string_struct lookuptable_opcode[8] = {
//    { "MOV",     OPCODE_MOV },
//    { "T1_MOV",  OPCODE_T1_MOV},
//    { "T2_MOV",  OPCODE_T2_MOV},
//    { "PUSH",    OPCODE_PUSH },
//    { "PULL",    OPCODE_PULL },
//    { "ADD",     OPCODE_ADD },
//    { "SUB",     OPCODE_SUB },
//    { "INTR",    OPCODE_INTR }
//};
//
//static t_string_struct lookuptable_operand[7] = {
//    { "R0", REG_R0 },
//    { "R1", REG_R1 },
//    { "R2", REG_R2 },
//    { "R3", REG_R3 },
//    { "C0", REG_C0 },
//    { "C1", REG_C1 },
//    { "C2", REG_C2 }
//};
//
//#define BADKEY 8

//#define NKEYS_1 (sizeof(lookuptable_opcode)/sizeof(t_string_struct))

//#define NKEYS_2 (sizeof(lookuptable_operand)/sizeof(t_string_struct))

//static int get_opcode(char *);
//static int get_operand(char *);

//		void comm_proc_lite_REG (void);
//		void comm_proc_lite_CTRL (void);
//      void comm_proc_lite_SEVAL(void);
 

