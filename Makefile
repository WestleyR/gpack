# Created by: WestleyR
# email: westleyr@nym.hush.com
# Date: Jun 16, 2019
# https://github.com/WestleyR/gpack
# version-1.0.0
#
# The Clear BSD License
#
# Copyright (c) 2019 WestleyR
# All rights reserved.
#
# This software is licensed under a Clear BSD License.
#

PREFIX = $(HOME)/.gpack

# your c compiler
CC = gcc

DEP_FLAG = -Ideps
CFLAGS = -Wall
DEFLAGS = 
LDFLAGS =

TARGET = gpack

COMMIT = "$(shell git log -1 --oneline --decorate=short --no-color || ( echo 'ERROR: unable to get commit hash' >&2 ; echo unknown ) )"
DEFLAGS += -DCOMMIT_HASH=\"$(COMMIT)\"

ifeq ($(DEBUG), true)
	CFLAGS += -DDEBUG
endif

CMD = $(wildcard cmd/*)

SRCDIR = src
DEPDIR = deps

SRC = $(wildcard src/*.c)
SRC += $(wildcard deps/*/*.c)

OBJS = $(SRC:.c=.o)

.PHONY:
all: $(TARGET)

.PHONY:
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS)

.PHONY:
%.o: %.c
	$(CC) $(DEP_FLAG) $(CFLAGS) $(DEFLAGS) $(LDFLAGS) -o $@ -c $<

.PHONY:
clean:
	rm -f $(OBJS)

.PHONY:
cleanall:
	rm -f $(TARGET) $(OBJS)

.PHONY:
install: $(TARGET)
	mkdir -p $(PREFIX)/bin
	cp -f $(TARGET) $(PREFIX)/bin

#
# End Makefile
#
