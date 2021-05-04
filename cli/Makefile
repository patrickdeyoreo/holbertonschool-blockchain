CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
RM = rm -f
CTAGS = ctags
TAGS = .tags

LIBS = -L../blockchain/v0.3 -lhblk_blockchain -L../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,%.o,$(SRC))

.PHONY: all clean distclean oclean tags cli

all: cli

clean: oclean
	$(RM) cli

distclean: clean
	$(RM) $(TAGS)

oclean:
	$(RM) $(OBJ)

tags:
	$(CTAGS) -f $(TAGS) -R

cli: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)
