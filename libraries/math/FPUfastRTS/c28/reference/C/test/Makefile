# Variables
# - Use gcc instead of cc (which is just a symbolic link to gcc). Cygwin wont 
#   accept cc
CC      := gcc 
#CFLAGS  := -std=c99 -g -I ../include -D _DEBUG -D USE_FID=0
#CFLAGS  := -std=c99 -g -I ../include -D _DEBUG -D USE_FID=1
CFLAGS  := -std=c99 -g -I ../include -D _DEBUG -D USE_FPU64=1 -D USE_FID=0
#CFLAGS  := -std=c99 -g -I ../include -D _DEBUG -D USE_FPU64=1 -D USE_FID=1
LDFLAGS := 
OBJECTS :=  main.o               \
            atan2Input.o         \
            atan2Output.o        \
            atan2Table.o         \
            atanInput.o          \
            atanOutput.o         \
            cosInput.o           \
            cosOutput.o          \
            divInput.o           \
            divOutput.o          \
            isqrtInput.o         \
            isqrtOutput.o        \
            sincosInput.o        \
            sincosOutput.o       \
            sincosTable.o        \
            sinInput.o           \
            sinOutput.o          \
            sqrtInput.o          \
            sqrtOutput.o         \
			ui32byui32Input.o    \
			ui32byui32Output.o   \
			i32byi32Input.o      \
			i32byi32Output.o     \
			i32byui32Input.o     \
			i32byui32Output.o    \
			ui64byui32Input.o    \
			ui64byui32Output.o   \
			i64byi32Input.o      \
			i64byi32Output.o     \
			i64byui32Input.o     \
            i64byui32Output.o    \
			ui64byui64Input.o    \
			ui64byui64Output.o   \
			i64byi64Input.o      \
			i64byi64Output.o     \
			i64byui64Input.o     \
			i64byui64Output.o    \
			ui16byui16Input.o    \
			ui16byui16Output.o   \
			i16byi16Input.o      \
			i16byi16Output.o     \
			ui32byui16Input.o    \
			ui32byui16Output.o   \
			i32byi16Input.o      \
			i32byi16Output.o     \
			f64byf64Input.o      \
			f64byf64Output.o     \
			cordic_sinInput.o    \
			cordic_sinOutput.o   \
			cordic_cosInput.o    \
			cordic_cosOutput.o   \
			cordic_atan2Input.o  \
			cordic_atan2Output.o \
			expInput.o			 \
			expOutput.o		     \
			logInput.o			 \
			logOutput.o          \
			powfInput.o          \
			powfOutput.o
			
TARGETS	:=  cos sin sincos sqrt isqrt div atan atan2 ui32byui32 \
            i32byi32 i32byui32 ui64byui32 i64byi32 i64byui32    \
			ui64byui64 i64byi64 i64byui64 ui16byui16 i16byi16   \
			ui32byui16 i32byi16 f64byf64                        \
			cordic_sin cordic_cos cordic_atan2                  \
			exp log powf

# Specify search directories using the vpath directive
# vpath pattern dir1 dir2 ...
vpath %.h    ../include
vpath %.a    ../lib

# target : prerequisites
#   recipe
# $< is the first prerequisite
# $^ is all the prerequisites
# $* is all the prerequisites (no repetition)
# $@ is the target
# $? files that have changed
# |<..> specifies order-only prerequisites
# - before the recipe means ignore errors (reported as ignored)
# @ before the recipe prevents the shell from echoing the command
# % is the stem (the wildcard) in pattern matches

# make all targets
all  : $(TARGETS)

# user invokes make with one of the TARGETS, make
# will filter all .o files that have the target name
# as the prefix and set them as the prerequisites
# The SECONDEXPANSION allows $@ to be used in the 
# prerequisites
.SECONDEXPANSION :
$(TARGETS) : $$(filter $$@Input.o $$@Output.o, $(OBJECTS)) main.o -lfastrts -lm
	$(CC) $^ -o  $@ 

$(OBJECTS) : %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
	

    
# Pseudo Targets
# make will delete targets in error, partially built, so that on the
# next go-around make doesnt ignore the file because its time stamp
# is up-to-date
.DELETE_ON_ERROR :

# Phony Targets
.PHONY: clean
clean :
	-rm *.o *dump.txt *.stackdump $(TARGETS)
