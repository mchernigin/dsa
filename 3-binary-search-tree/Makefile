CC=gcc
TARGET=test

all: $(TARGET)

$(TARGET): test.c
	@printf "[CMD] "
	$(CC) $^ -o $(TARGET)

run: $(TARGET)
	@printf "[CMD] "
	./$(TARGET)

clean:
	@printf "[CMD] "
	rm -f $(TARGET)
