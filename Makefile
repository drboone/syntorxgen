# Makefile, Boone, 07/23/02
# Build syntorxgen
# Copyright (C) 2002, Dennis Boone, East Lansing, MI

# Modifications:
# 07/23/02 Boone      Initial coding
# 07/27/02 Boone      Added decode
# End Modifications

# This file is part of syntorxgen.
# 
# Syntorxgen is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published
# by the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# Foobar is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Foobar; if not, write to the Free Software Foundation,
# Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

YACC=bison
YFLAGS=-d -y -t
CFLAGS=-g
LEX=flex
LFLAGS=-s
LIBS=-lfl -lm

all: syntorxgen decode

syntorxgen: synxparser.o synxlexer.o calcplug.o
	$(CC) -o $@ $^ $(LIBS)

decode: decode.o

clean:
	rm *.o y.tab.h syntorxgen
