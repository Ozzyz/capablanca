CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CCFLAGS  = -g -Wall -Wextra -Werror -Iinclude/
# the build target executable:
TARGET = main

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)


$(TARGET): $(obj)
	$(CC) -o $@ $^ $(CCFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) $(TARGET)
