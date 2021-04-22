CC=gcc
CFLAGS = -Wall -Werror -std=gnu99 -g

all: html_parser

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

html_parser: html_parser.c
	$(CC) $(CFLAGS) -o html_parser html_parser.c 
                               
.PHONY: clean

clean:
	rm -f html_parser *.o