# Created by: WestleyR
# Email: westleyr@nym.hush.com
# Url: https://github.com/WestleyR/gpack
# Last modified date: 2021-01-17
#
# This file is licensed under the terms of
#
# The Clear BSD License
#
# Copyright (c) 2019-2021 WestleyR
# All rights reserved.
#
# This software is licensed under a Clear BSD License.
#

# The prefix to install the gpack command. This should
# not be changed, unless you know what your doing.
PREFIX = $(HOME)/.local

# The C compiler
CC = gcc

# These flags can be changed though the command line
CFLAGS = -Wall -Ideps
LDFLAGS ?= 

TARGET = gpack

CHECKSUM_CMD_FILE = $(HOME)/.gpack/gpack/cmd-checksum.ssum
CHECKSUM_PROG = ssum
ifeq (, $(shell which $(CHECKSUM_PROG)))
$(warning "No $(CHECKSUM_PROG) command found")
else
$(info "Generating checksums for scripts...")
files = $(wildcard $(HOME)/.gpack/gpack/cmd/*)
$(shell $(CHECKSUM_PROG) $(files) > $(CHECKSUM_CMD_FILE))
endif

COMMIT = $(subst `,\`,"$(shell git log -1 --oneline --decorate=short --no-color || ( echo 'ERROR: unable to get commit hash' >&2 ; echo unknown ))")

DEFLAGS += -DCOMMIT_HASH=\"$(COMMIT)\"

ifeq ($(DEBUG), true)
	CFLAGS += -DDEBUG
endif

SRC = $(wildcard src/*.c)
SRC += $(wildcard deps/*/*.c)

OBJS = $(SRC:.c=.o)

.PHONY:
all: $(TARGET)

.PHONY:
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(TARGET)

.PHONY:
%.o: %.c
	$(CC) $(DEP_FLAG) $(CFLAGS) $(DEFLAGS) -o $@ -c $< $(LDFLAGS)

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
	@# Ensure the packages are there
	cd $(HOME)/.gpack ; test -d packages || git clone https://github.com/WestleyR/packages ;

#
# End Makefile
#
