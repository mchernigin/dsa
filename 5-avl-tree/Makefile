CXX = g++
CXXFLAGS += -O2 -std=c++2a \
			-pedantic -Wall -Wextra -Wshadow -Wold-style-cast \
			-Wmissing-declarations -Wcast-qual -Wsign-conversion -Wno-unused

TARGET = test

$(TARGET) : $(TARGET).cpp

.PHONY : clean
clean :
	rm -rf $(TARGET)
