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
#include <time.h>
#include <math.h>

#define USAGE     "decode [-LHUW8sh] [-f inputfile]"
#define HEX       1
#define SRECORD   2
#define MAXSTR    256
#define LOWBAND   1
#define HIGHBAND  2
#define UHFR1BAND 3
#define UHFR2BAND 4
#define X800BAND  5

unsigned char dpltable[8] = { 7, 3, 5, 1, 6, 2, 4, 0 };
unsigned int ctable[4] = { 0, 1, 3, 2 };
char rtype[6][16] =
{
	"invalid", "low band", "high band",
	"UHF range 1", "UHF ranges 2-5", "800"
};
unsigned int radio = HIGHBAND;

void decode(unsigned int *binbuf)
{
	unsigned int i, j;
	unsigned int bit, bits;
	unsigned int refreq;
	unsigned int txa, txb, txc, txv;
	unsigned int rxa, rxb, rxc, rxv;

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
		else
			puts("\ttxmpl no;");
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
		else
			puts("\trxmpl no;");
	}

	/* Timeout */

	bits = (binbuf[8] & 0xf8) >> 3;
	printf("\ttimeout %d;\n", 465 - (bits * 15));

	/* Transmitter power */

	if (binbuf[8] & 0x04)
		puts("\ttxpower high;");
	else
		puts("\ttxpower low;");

	/* Reference frequency */

	bits = binbuf[8] & 0x03;
	switch (bits)
	{
		case 0:
			puts("\treffreq 6250;");
			refreq = 6250;
			break;
		case 1:
			puts("\treffreq invalid;");
			refreq = 0;
			break;
		case 2:
			puts("\treffreq 4166;");
			refreq = 4166;
			break;
		case 3:
			puts("\treffreq 5000;");
			refreq = 5000;
			break;
	};

	/* Scan things */

	bits = (binbuf[9] & 0xc0) >> 6;
	switch (bits)
	{
		case 0:
			puts("\tscantype dblpri;");
			break;
		case 1:
			puts("\tscantype sglpri;");
			break;
		case 2:
			puts("\tscantype none;");
			break;
		case 3:
			puts("\tscantype nonpri;");
			break;
	};

	if (binbuf[9] & 0x20)
		puts("\ttbscan yes;");
	else
		puts("\ttbscan no;");

	printf("\tp1scanmode %d;\n", binbuf[10] & 0x1f);
	printf("\tp2scanmode %d;\n", binbuf[9] & 0x1f);

	if (binbuf[10] & 0x80)
		puts("\tnpscansource fixed;");
	else
		puts("\tnpscansource selectable;");

	/* Squelch type */

	bits = (binbuf[10] & 0x60) >> 5;
	switch (bits)
	{
		case 0:
			puts("\tsquelchtype andor;");
			break;
		case 1:
			puts("\tsquelchtype andstd;");
			break;
		case 2:
			puts("\tsquelchtype invalid;");
			break;
		case 3:
			puts("\tsquelchtype stdstd;");
			break;
	};

	/* Frequency programming */

	txv = (binbuf[11] & 0x00c0) >> 6;
	txc = (binbuf[11] & 0x0030) >> 4;
	rxv = (binbuf[11] & 0x000c) >> 2;
	rxc = (binbuf[11] & 0x0003);
	txb = (binbuf[12] & 0x00f0) << 2;
	rxb = (binbuf[12] & 0x000f) << 6;
	txb |= (binbuf[13] & 0x00f0) >> 2;
	rxb |= (binbuf[13] & 0x000f) << 2;
	txb |= (binbuf[14] & 0x00c0) >> 6;
	rxb |= (binbuf[14] & 0x000c) >> 2;
	txa = binbuf[14] & 0x0030;
	rxa = (binbuf[14] & 0x0003) << 4;
	txa |= (binbuf[15] & 0x00f0) >> 4;
	rxa |= binbuf[15] & 0x000f;

	if (radio == LOWBAND)
	{
		int fvco, frx, ftx;

		fvco = ((64 * rxa) + (63 * rxb)) * refreq;
		frx = fvco - 75700000;
		fvco = ((64 * txa) + (63 * txb)) * refreq;
		ftx = 172800000 - fvco;

		printf("\ttxfreq %8.4f;\n", (double)ftx / 1000000.0);
		printf("\trxfreq %8.4f;\n", (double)frx / 1000000.0);
	}
	else if ((radio == HIGHBAND) || (radio == UHFR1BAND))
	{
		int fvco, frx, ftx;

		fvco = ((((64 * rxa) + (63 * rxb)) * 3) + ctable[rxc]) * refreq;
		frx = fvco - 53900000;
		fvco = ((((64 * txa) + (63 * txb)) * 3) + ctable[txc]) * refreq;
		ftx = fvco;

		printf("\ttxfreq %8.4f;\n", (double)ftx / 1000000.0);
		printf("\trxfreq %8.4f;\n", (double)frx / 1000000.0);
	}
	else if (radio == UHFR2BAND) /* actually ranges 2-5 */
	{
		int fvco, frx, ftx;

		fvco = ((((64 * rxa) + (63 * rxb)) * 3) + ctable[rxc]) * refreq;
		frx = fvco + 53900000;
		fvco = ((((64 * txa) + (63 * txb)) * 3) + ctable[txc]) * refreq;
		ftx = fvco;

		printf("\ttxfreq %8.4f;\n", (double)ftx / 1000000.0);
		printf("\trxfreq %8.4f;\n", (double)frx / 1000000.0);
	}
	else if (radio == X800BAND)
	{
		int fvco, frx, ftx;

		fvco = ((((64 * rxa) + (63 * rxb)) * 3) + ctable[rxc]) * refreq;
		frx = (fvco * 2) + 53900000;
		fvco = ((((64 * txa) + (63 * txb)) * 3) + ctable[txc]) * refreq;
		ftx = fvco * 2;

		printf("\ttxfreq %8.4f;\n", (double)ftx / 1000000.0);
		printf("\trxfreq %8.4f;\n", (double)frx / 1000000.0);
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
	char filename[MAXSTR+1] = "";
	char inbuf[MAXSTR+1];
	int rtypespec = 0;
	unsigned int binbuf[16];
	int n;
	time_t now;

	while ((c = getopt(argc, argv, "LHU8shf:")) != -1)
	{
		switch (c)
		{
			case 'L':
				radio = LOWBAND;
				rtypespec = 1;
				break;
			case 'H':
				radio = HIGHBAND;
				rtypespec = 1;
				break;
			case 'U':
				radio = UHFR1BAND;
				rtypespec = 1;
				break;
			case 'W':
				radio = UHFR2BAND;
				rtypespec = 1;
				break;
			case '8':
				radio = X800BAND;
				rtypespec = 1;
				break;
			case 's':
				infmt = HEX;
				break;
			case 'h':
				infmt = SRECORD;
				break;
			case 'f':
				strncpy(filename, optarg, MAXSTR);
				if (freopen(filename, "r", stdin) == NULL)
				{
					perror(filename);
					exit(errno);
				}
				break;
			default:
				fprintf(stderr, USAGE);
		};
	}

	printf("# syntorxgen input file generated by decode from %s\n",
		*filename ? filename : "standard input");
	printf("# Radio type %s %s\n",
		rtypespec ? "was specified as" : "defaulted to",
		rtype[radio]);
	now = time(NULL);
	printf("# Decoded %s\n", ctime(&now));

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
