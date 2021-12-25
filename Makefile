CC := gcc
CFLAGS := -Wall -g -Werror

all: main.o huffman.o huffman

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

huffman:
	$(CC) -o huffman main.o huffman.o $(CFLAGS)

clean:
	rm -f *.o huffman *.txt .vscode/*.txt

.PHONY: all clean