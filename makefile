.PHONY: clean # This creates the label which can be called

CC = gcc 
CFLAGS = -Wall -pedantic
DEPS = GameOfLife.h
OBJ = GameOfLife.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

game: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^


clean:
	rm $(OBJ)