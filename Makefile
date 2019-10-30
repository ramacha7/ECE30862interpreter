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

testall: $(TARGET)
	./project interpreter_input.smp

testsub: $(TARGET)
	./project Individual_Test_Cases/104_sub_test.smp

testadd: $(TARGET)
	./project Individual_Test_Cases/100_add_test.smp

clean: 
	rm -f split $(TARGET) $(OBJS)
