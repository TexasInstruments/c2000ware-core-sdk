### := simply expanded variables
# - Use gcc instead of cc (which is just a symbolic link to gcc). Cygwin wont 
#   accept cc
CC      := gcc
AR      := ar
# -g enables symbols (for debugging)
#CFLAGS  := -g -I include -D _DEBUG
CFLAGS  := -g -I include -D _DEBUG -D USE_FPU64=1
LDFLAGS := 
# r (keyletter) to archive, 
# (mods)c - creates each time, v - verbose, s- create index
ARFLAGS := -rcvs
OBJDIR  := out
LIBDIR  := lib
HEADERS := dsp.h         \
           dsp_assert.h  \
		   dsp_error.h   \
		   vector.h      \
		   filter.h      \
		   fft.h
LIBRARY := $(addprefix $(LIBDIR)/,libdsp.a) 
### = recursively expanded vairables
# the wildcard produces all c files under source/ and then we
# substitute .c with .o and attach the output directory prefix
LOBJECTS = $(addprefix $(OBJDIR)/,                                            \
            $(patsubst source/%.c,%.o, $(wildcard source/*.c))                \
            $(patsubst source/vector/%.c,%.o, $(wildcard source/vector/*.c))  \
			$(patsubst source/filter/%.c,%.o, $(wildcard source/filter/*.c))  \
			$(patsubst source/fft/%.c,%.o, $(wildcard source/fft/*.c))        \
			$(patsubst source/utility/%.c,%.o, $(wildcard source/utility/*.c))\
			$(patsubst source/math/%.c,%.o, $(wildcard source/math/*.c))      \
			$(patsubst source/error/%.c,%.o, $(wildcard source/error/*.c))    \
			)

# Specify search directories using the vpath directive
# vpath pattern dir1 dir2 ...
vpath %.c source : source/error : source/vector : source/fft : source/filter
vpath %.c source/math : source/utility
vpath %.h include
vpath %.a lib

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
$(OBJDIR)/%.o: %.c $(HEADERS) $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBRARY): $(LOBJECTS)
	$(AR) $(ARFLAGS) $@ $(LOBJECTS)             ;  
# Uncomment below when you have issues with archiving
#	@echo -e "\nExtracting Object files\n"      ;
#	$-$(AR) x $@                                ;
#	@echo -e "\nObject files in the archive\n"  ;
#	@-$(AR) -t $@ | xargs -n1 file              ; 
#	@echo -e "\nSymbols in each obj file\n"     ;
#	@-$(AR) -t $@ | xargs -n1 nm
    
all: $(LIBRARY)

$(LIBRARY): | $(OBJDIR) $(LIBDIR)

$(OBJDIR):
	mkdir $(OBJDIR)
	
$(LIBDIR):
	mkdir $(LIBDIR)

    
# Pseudo Targets
# make will delete targets in error, partially built, so that on the
# next go-around make doesnt ignore the file because its time stamp
# is up-to-date
.DELETE_ON_ERROR :

# Phony Targets - make runs recipe unconditionally
.PHONY: clean
clean :
	-rm $(LOBJECTS) $(LIBRARY)
