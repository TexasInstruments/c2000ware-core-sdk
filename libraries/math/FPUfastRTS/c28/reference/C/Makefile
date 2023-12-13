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
HEADERS := fastrts.h        \
           fid.h            \
           fastrts_assert.h \
           fastrts_error.h  \
		   fastrts_cordic.h
LIBRARY := $(addprefix $(LIBDIR)/,libfastrts.a) 
### = recursively expanded vairables
# the wildcard produces all c files under source/ and then we
# substitute .c with .o and attach the output directory prefix
LOBJECTS = $(addprefix $(OBJDIR)/,                                            \
            $(patsubst source/%.c,%.o, $(wildcard source/*.c))                \
           )

# Specify search directories using the vpath directive
# vpath pattern dir1 dir2 ...
vpath %.c source
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
all: $(LIBRARY)

$(LIBRARY): | $(OBJDIR) $(LIBDIR)

$(LIBRARY): $(LOBJECTS)
	$(AR) $(ARFLAGS) $@ $(LOBJECTS)             ;  
# Uncomment below when you have issues with archiving
#	@echo -e "\nExtracting Object files\n"      ;
#	$-$(AR) x $@                                ;
#	@echo -e "\nObject files in the archive\n"  ;
#	@-$(AR) -t $@ | xargs -n1 file              ; 
#	@echo -e "\nSymbols in each obj file\n"     ;
#	@-$(AR) -t $@ | xargs -n1 nm
    
$(LOBJECTS): $(OBJDIR)/%.o : %.c $(OBJDIR) $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)
	

$(LIBDIR):
	mkdir $(LIBDIR)

# Target has no prereqs but ensures object files are rebuilt if the 
# header changes
$(HEADERS):

# Pseudo Targets
# make will delete targets in error, partially built, so that on the
# next go-around make doesnt ignore the file because its time stamp
# is up-to-date
.DELETE_ON_ERROR :

# Phony Targets - make runs recipe unconditionally
.PHONY: clean
clean :
	-rm $(LOBJECTS) $(LIBRARY)
