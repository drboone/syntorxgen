# Makefile, Boone, 07/23/02
# Build syntorxgen
# Copyright (C) 2002, Dennis Boone, East Lansing, MI

# Modifications:
# 07/23/02 Boone      Initial coding
# End Modifications

YACC=bison
YFLAGS=-d -y -t
CFLAGS=-g
LEX=flex
LFLAGS=-s
LIBS=-lfl

syntorxgen: synxparser.o synxlexer.o calcplug.o
	$(CC) -o $@ $^ $(LIBS)

clean:
	rm *.o y.tab.h syntorxgen
