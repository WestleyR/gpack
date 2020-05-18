# Created by: WestleyR
# Email: westleyr@nym.hush.com
# Url: https://github.com/WestleyR/gpack
# Last modified date: 2020-05-17
#
# This file is licensed under the terms of
#
# The Clear BSD License
#
# Copyright (c) 2019-2020 WestleyR
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

TARGET = gpack

COMMIT = $(subst `,\`,"$(shell git log -1 --oneline --decorate=short --no-color || ( echo 'ERROR: unable to get commit hash' >&2 ; echo unknown ))")

DEFLAGS += -DCOMMIT_HASH=\"$(COMMIT)\"

ifeq ($(DEBUG), true)
	CFLAGS += -DDEBUG
endif

SRCDIR = src
DEPDIR = deps

SRC = $(wildcard src/*.c)
SRC += $(wildcard deps/*/*.c)

OBJS = $(SRC:.c=.o)

.PHONY:
all: $(TARGET)

.PHONY:
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(TARGET)
	$(MAKE) -C get-json-value

.PHONY:
%.o: %.c
	$(CC) $(DEP_FLAG) $(CFLAGS) $(DEFLAGS) -o $@ -c $< $(LDFLAGS)

.PHONY:
clean:
	rm -f $(OBJS)
	$(MAKE) -C get-json-value clean

.PHONY:
cleanall:
	rm -f $(TARGET) $(OBJS)
	$(MAKE) -C get-json-value cleanall

.PHONY:
install: $(TARGET)
	mkdir -p $(PREFIX)/bin
	mkdir -p $(PREFIX)/installed
	cp -f $(TARGET) $(PREFIX)/bin
	cp -f cmd/load_gpack $(PREFIX)/bin
	$(MAKE) -C get-json-value install
	@# Ensure the packages are there
	cd $(HOME)/.gpack ; test -d packages || git clone https://github.com/WestleyR/packages ;

#
# End Makefile
#
