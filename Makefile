CC=gcc
CFLAGS= -std=c99 -pedantic -Werror -Wall -Wextra -Wvla -I./include -Wno-vla -g
LDFLAGS=
OUT=editor
SRCS = $(shell find $(SRC_DIR) -name '*.c' -a ! -path '*/test/*')
OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	$(CC) $(LDFLAGS) -o $(OUT) $(OBJS)

clean:
	$(RM) $(OUT) $(shell find . -name '*.o')

.PHONY: clean all

