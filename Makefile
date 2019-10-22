TARGET = project
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla 
GCC = g++ -std=c++17 -g $(WARNING) $(ERROR)

SRCS = main.cpp Bytcode.cpp BytecodeInt.cpp BytecodeFloat.cpp BytecodeShort.cpp BytecodeChar.cpp Datatype.cpp
OBJS = $(SRCS:%.cpp=%.o)

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)
.c.o: 
	$(GCC)-c $*.cpp 

test1: $(TARGET)
	./project interpreter_input.smp

clean: 
	rm -f split $(TARGET) $(OBJS)
