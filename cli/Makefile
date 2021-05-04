CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
AR = ar -rcs
RM = rm -f
CTAGS = ctags
TAGS = .tags

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
