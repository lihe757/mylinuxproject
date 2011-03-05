CXX = gcc
TARGET = py
C_FLAGS += -g -Wall

INC = -I/usr/include/python2.6/
LIB = -L/usr/lib/ -lpython2.6

all: $(TARGET)

py:  py.o
		$(CXX) -o $@ $^  $(LIB) $(C_FLAGS) 
.c.o:
		$(CXX) -c -g -o $*.o $(INC) $(C_FLAGS) $*.c
		 
clean:
	-rm -f *.o $(TARGET)
