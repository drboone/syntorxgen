/* decode.c, Boone, 07/27/02
   Decipher a code plug
   Copyright (C) 2002, Dennis Boone, East Lansing, MI */

/* Modifications:
   07/27/02 Boone      Initial coding
   End Modifications */

/* This file is part of syntorxgen.

   Syntorxgen is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   Syntorxgen is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with syntorxgen; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>

#define USAGE     "decode [-sh] [-f inputfile]"
#define HEX       1
#define SRECORD   2
#define MAXSTR    256

unsigned char dpltable[8] = { 7, 3, 5, 1, 6, 2, 4, 0 };

void decode(unsigned int *binbuf)
{
	int i, j;
	int bit, bits;

	/* Non-priority scan list */

	for (i = 0; i < 4; i++)
		binbuf[i] = (~binbuf[i] & 0xff);
	if (binbuf[0] || binbuf[1] || binbuf[2] || binbuf[3])
	{
		printf("\tnpscanlist");
		for (i = 0; i < 4; i ++)
		{
			for (j = 1; j < 9; j++)
			{
				bit = (binbuf[i] & (1 << (8 - j))) >> (8 - j);
				if (bit)
					printf(" %d", (i * 8) + j);
			}
		}
		printf(";\n");
	}

	/* PL/DPL */

	if (binbuf[5] & 0x20)
	{
		if (binbuf[5] & 0x40)
		{
			bits = dpltable[(binbuf[4] & 0x70) >> 4]; /* C */
			bits |= dpltable[(binbuf[4] & 0x0e) >> 1] << 3; /* B */
			bit = (binbuf[4] & 0x01) << 2; /* A0 */
			bit |= (binbuf[5] & 0x18) >> 3; /* A1-2 */
			bits |= dpltable[bit] << 6;
			printf("\ttxdpl %03o;\n", bits);
		}
		else
		{
			double pl;

			bits = binbuf[4];
			bits |= (binbuf[5] & 0x3f) << 8;
			pl = (float)(~bits & 0x3fff) / 18.0616;
			printf("\ttxpl %5.1f;\n", pl);
		}
		if (binbuf[5] & 0x80)
			puts("\ttxmpl yes;");
	}
	if (binbuf[7] & 0x20)
	{
		if (binbuf[7] & 0x40)
		{
			bits = dpltable[(binbuf[6] & 0x70) >> 4]; /* C */
			bits |= dpltable[(binbuf[6] & 0x0e) >> 1] << 3; /* B */
			bit = (binbuf[6] & 0x01) << 2; /* A0 */
			bit |= (binbuf[7] & 0x18) >> 3; /* A1-2 */
			bits |= dpltable[bit] << 6;
			printf("\trxdpl %03o;\n", bits);
		}
		else
		{
			double pl;

			bits = binbuf[6];
			bits |= (binbuf[7] & 0x3f) << 8;
			pl = (float)(~bits & 0x3fff) / 61.17;
			printf("\trxpl %5.1f;\n", pl);
		}
		if (binbuf[7] & 0x80)
			puts("\trxmpl yes;");
	}
}

void srecbin(char *inbuf, unsigned int *binbuf)
{
}

void hexbin(char *inbuf, unsigned int *binbuf)
{
	int rc;

	rc = sscanf(inbuf, "%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x",
		&binbuf[0], &binbuf[1], &binbuf[2], &binbuf[3],
		&binbuf[4], &binbuf[5], &binbuf[6], &binbuf[7],
		&binbuf[8], &binbuf[9], &binbuf[10], &binbuf[11],
		&binbuf[12], &binbuf[13], &binbuf[14], &binbuf[15]);
	if (rc != 16)
	{
		fprintf(stderr, "invalid hex input line format\n");
		exit(EINVAL);
	}
}

int main(int argc, char *argv[])
{
	int c;
	int infmt = HEX;
	char inbuf[MAXSTR+1];
	unsigned int binbuf[16];
	int n;

	while ((c = getopt(argc, argv, "shf:")) != -1)
	{
		switch (c)
		{
			case 's':
				infmt = HEX;
				break;
			case 'h':
				infmt = SRECORD;
				break;
			case 'f':
				if (freopen(optarg, "r", stdin) == NULL)
				{
					perror(optarg);
					exit(errno);
				}
				break;
			default:
				fprintf(stderr, USAGE);
		};
	}

	n = 1;
	while (fgets(inbuf, MAXSTR, stdin) != NULL)
	{
		if (infmt == HEX)
			hexbin(inbuf, binbuf);
		else
			if (infmt == SRECORD)
				srecbin(inbuf, binbuf);
			else
			{
				fprintf(stderr, "unknown input file format\n");
			}
		printf("mode %d\n{\n", n++);
		decode(binbuf);
		puts("}");
	}
}
