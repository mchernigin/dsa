CC = gcc
CFLAGS += -O2 -std=c11 -fsanitize=address -g \
          -Wall -Wextra -Wpedantic \
          -Wformat=2 -Wno-unused-parameter -Wshadow \
          -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
          -Wredundant-decls -Wnested-externs -Wmissing-include-dirs

TARGET = test

.PHONY : all clean

$(TARGET) : $(TARGET).c

clean :
	rm -rf $(TARGET) $(TARGET).dSYM
