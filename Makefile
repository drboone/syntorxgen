# Makefile, Boone, 06/02/02
# Build syntorxgen
# Copyright (C) 2002, Dennis Boone, East Lansing, MI

# Modifications:
# 06/02/02 Boone      Initial coding
# 06/30/02 Boone      Added calcplug
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
