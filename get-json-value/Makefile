# Created by: WestleyR
# email: westleyr@nym.hush.com
# Date: Dec 22, 2019
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

CFLAGS = -Wall

TARGET = get-json-value

ifeq ($(DEBUG), true)
	CFLAGS += -DDEBUG
endif

SRC = $(wildcard ./*.c)

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

#
# End Makefile
#
