TARGET = project
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla 
GCC = g++ -std=c99 -g $(WARNING) $(ERROR)

SRCS = main.cpp
OBJS = $(SRCS:%.c=%.o)

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)
.c.o: 
	$(GCC)-c $*.cpp 

test1: $(TARGET)
	./project interpreter_input.smp

clean: 
	rm -f split *.b $(TARGET) $(OBJS)
