# Makefile, Boone, 06/02/02
# Build syntorxgen
# Copyright (C) 2002, Dennis Boone, East Lansing, MI

# Modifications:
# 06/02/02 Boone      Initial coding
# End Modifications

YACC=bison
YFLAGS=-d -y -t
LEX=flex
LFLAGS=-s
LIBS=-lfl

syntorxgen: synxparser.o synxlexer.o
	$(CC) -o $@ $^ $(LIBS)

clean:
	rm *.c *.o y.tab.h
