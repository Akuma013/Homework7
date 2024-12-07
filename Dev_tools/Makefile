CC = gcc
CFLAGS = -Wall -Werror -Wextra
TARGET = sort_program

all: $(TARGET)

$(TARGET): SortArr.o
	$(CC) $(CFLAGS) -o $@ $^

SortArr.o: SortArr.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean