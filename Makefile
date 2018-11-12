CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CCFLAGS  = -g -Wall -Wextra -Werror -Iinclude/
# the build target executable:
TARGET = main
SRCDIR = src
OBJDIR = obj
BINDIR = bin

src = $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)

$(BINDIR)/$(TARGET): $(obj)
	$(CC) -o $@ $^ $(CCFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/$(obj) $(TARGET)
