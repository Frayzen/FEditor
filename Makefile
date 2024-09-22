CC=gcc
SRC_DIR=src
CFLAGS= -std=c99 -pedantic -Werror -Wall -Wextra -Wvla -I./${SRC_DIR} -Wno-vla
LDFLAGS=-lncurses
OUT=editor
SRCS=$(shell find $(SRC_DIR) -name '*.c' -a ! -path '*/test/*')
OBJS=$(SRCS:.c=.o)

all: $(OBJS)
	$(CC) $(LDFLAGS) -o $(OUT) $(OBJS)

debug: CFLAGS +=-g
debug: LDFLAGS += -fsanitize=address
debug: $(OBJS)
	$(CC) $(LDFLAGS) -o $(OUT) $(OBJS)

clean:
	$(RM) $(OUT) $(shell find . -name '*.o')

.PHONY: clean all

