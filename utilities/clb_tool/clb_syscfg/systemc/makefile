INCLUDES  = -Iinclude

FILES  = src/CLB_counter_SC_model.cpp
FILES += src/CLB_LUT4_SC_model.cpp
FILES += src/CLB_OutputLUT_SC_model.cpp
FILES += src/CLB_FSM_SC_model.cpp
FILES += src/CLB_HLC_SC_model.cpp

OBJS =  $(FILES:.cpp=.o)

clb.lib: $(OBJS)
	ar -r $@ $^

%.o:%.cpp
	g++ -c $(INCLUDES) $< -o $@

clean:
	rm -rf */*.o clb.lib
