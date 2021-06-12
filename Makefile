#
#  Makefile
#  gpack - https://github.com/WestleyR/gpack
#
# Created by WestleyR on Jun 16, 2019
# Source code: https://github.com/WestleyR/gpack
#
# Copyright (c) 2019-2021 WestleyR. All rights reserved.
# This software is licensed under a BSD 3-Clause Clear License.
# Consult the LICENSE file that came with this software regarding
# your rights to distribute this software.
#

# The prefix to install the gpack command. This should
# not be changed, unless you know what your doing.
PREFIX = $(HOME)/.local

# The C compiler
CC = gcc

# These flags can be changed though the command line
CFLAGS = -Wall -Ideps -g
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

MODDED = $(shell if command -v git > /dev/null ; then (git diff --exit-code --quiet && echo \"[No changes]\") || echo \"[With uncommited changes]\" ; else echo \"[unknown]\" ; fi)
COMMIT = "$(shell git log -1 --oneline --decorate=short --no-color || ( echo 'ERROR: unable to get commit hash' >&2 ; echo unknown ) )"

CFLAGS += -DCOMMIT_HASH=\"$(COMMIT)\"
CFLAGS += -DUNCOMMITED_CHANGES=\"$(MODDED)\"

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
