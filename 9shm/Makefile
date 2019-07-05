SRCS:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp, %.o, $(SRCS))
TARGET:=write
CC:=g++
INC:=.
LIB:=.
FLAGS:=-c

all:$(TARGET)


$(TARGET):$(OBJS)
	$(CC) $^ -L$(LIB) -o $@

%.o:%.cpp
	$(CC) $(FLAGS) -I$(INC) $< -o $@

.PHONY:clean
clean:
	$(RM) $(OBJS) $(TARGET)
