# Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

.PHONY: all clean

CC = g++
LIBS =
CFLAGS = -Wall -std=c++17 -O3

SRCS = $(wildcard *.cc)
OBJS = $(SRCS:.cc=.out)

%.out: %.cc
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

all: $(OBJS)

clean:
	rm -rf *.out

