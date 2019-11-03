TARGET = project
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla 
GCC = g++ -std=c++17 -g $(WARNING) $(ERROR)

SRCS = main.cpp Bytecode.cpp Datatype.cpp
OBJS = $(SRCS:%.cpp=%.o)

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)
.c.o: 
	$(GCC)-c $*.cpp 

testmain: $(TARGET)
	./project interpreter_input.smp

testBasics: $(TARGET)
	./project Basics.bin

testComparisons: $(TARGET)
	./project Comparisons.bin

testJumps: $(TARGET)
	./project Jumps.bin

testMath: $(TARGET)
	./project Math.bin

testPeekPoke: $(TARGET)
	./project Peek_Poke.bin

testPushPop: $(TARGET)
	./project Push_Pop.bin

testSubroutines: $(TARGET)
	./project Subroutines.bin


clean: 
	rm -f split $(TARGET) $(OBJS)
