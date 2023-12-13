### := simply expanded variables
# - Use gcc instead of cc (which is just a symbolic link to gcc). Cygwin wont 
#   accept cc
CC      := g++
# -g enables symbols (for debugging)
CFLAGS  := -g -I ../include
TARGETS :=  tmu
OBJECTS  =  $(patsubst %.cpp, %.o, $(wildcard *.cpp))                              
### = recursively expanded vairables
# -Wl passes the comma seperated list that follows as arguments
#  to the linker
LDFLAGS  = -Wl,-Map,$@.map
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
$(TARGETS) : $(OBJECTS) -ltmu -lm
	$(CC) $^ -o  $@ $(LDFLAGS)

$(OBJECTS) : %.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	

    
# Pseudo Targets
# make will delete targets in error, partially built, so that on the
# next go-around make doesnt ignore the file because its time stamp
# is up-to-date
.DELETE_ON_ERROR :

# Phony Targets
.PHONY: clean
clean :
	-rm *.o *.stackdump *.txt *.map $(TARGETS) $(addsuffix .exe, $(TARGETS))
