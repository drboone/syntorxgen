/* calcplug.c, Boone, 07/23/02
   Compute the bit string for one mode in a code plug
   Copyright (C) 2002, Dennis Boone, East Lansing, MI */

/* Modifications:
   07/23/02 Boone      Initial coding
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
#include <math.h>

#include "syntorxgen.h"
/* #include "vbits.h" */

unsigned char ctable[3] = { 2, 1, 3 };
/* unsigned char dpltable[8] = { 0, 4, 2, 6, 1, 5, 3, 7 }; */
unsigned int dpltable[8] = { 7, 3, 5, 1, 6, 2, 4, 0 };

typedef struct 
{
	unsigned int normal;
	unsigned int inverted;
} Dplinv;

Dplinv dplinv[] =
{
	0023, 0047, 0116, 0754, 0244, 0025, 0411, 0226, 0612, 0346,
	0025, 0244, 0125, 0365, 0245, 0072, 0412, 0143, 0624, 0632,
	0026, 0464, 0131, 0364, 0251, 0165, 0413, 0054, 0627, 0031,
	0031, 0627, 0132, 0546, 0261, 0732, 0423, 0315, 0631, 0606,
	0032, 0051, 0134, 0223, 0263, 0205, 0431, 0723, 0632, 0624,
	0036, 0172, 0143, 0412, 0265, 0156, 0432, 0516, 0654, 0743,
	0043, 0445, 0152, 0115, 0271, 0065, 0445, 0043, 0662, 0466,
	0047, 0023, 0155, 0731, 0306, 0071, 0464, 0026, 0664, 0311,
	0051, 0032, 0156, 0265, 0311, 0664, 0465, 0331, 0703, 0565,
	0054, 0413, 0162, 0503, 0315, 0423, 0466, 0662, 0712, 0114,
	0065, 0271, 0165, 0251, 0331, 0465, 0503, 0162, 0723, 0431,
	0071, 0306, 0172, 0036, 0343, 0532, 0506, 0073, 0731, 0155,
	0072, 0245, 0174, 0074, 0346, 0612, 0516, 0432, 0732, 0261,
	0073, 0506, 0205, 0263, 0351, 0243, 0532, 0343, 0734, 0371,
	0074, 0174, 0223, 0134, 0364, 0131, 0546, 0132, 0743, 0654,
	0114, 0712, 0226, 0411, 0365, 0125, 0565, 0703, 0754, 0116,
	0115, 0152, 0243, 0351, 0371, 0734, 0606, 0631
};

int selvbits(unsigned int txfreq, unsigned int rxfreq,
	unsigned int *txvbits, unsigned int *rxvbits)

{
	unsigned int txvcosplit;
	unsigned int rxvcosplit;

	if (gtxvcosplit == -1)
		if (txfreq < MAXLOWBAND)
			gtxvcosplit = 47.1;
		else
			if (txfreq < MAXHIGHBAND)
				gtxvcosplit = 161.8;
			else
				if (txfreq < MAXUHFBAND)
					gtxvcosplit = 459.5;
				else
					gtxvcosplit = 825.0;

	if (grxvcosplit == -1)
		if (rxfreq < MAXLOWBAND)
			grxvcosplit = 47.1;
		else
			if (rxfreq < MAXHIGHBAND)
				grxvcosplit = 150.0;
			else
				if (rxfreq < MAXUHFBAND)
					grxvcosplit = 459.5;
				else
					grxvcosplit = 825.0;

	txvcosplit = (int)(gtxvcosplit * 1000000.0L);
	rxvcosplit = (int)(grxvcosplit * 1000000.0L);

	if (rxfreq < MAXLOWBAND)
	{
		if (rxfreq < glbvco1splitrx)
			*rxvbits = 0;
		else
			if (rxfreq < glbvco2splitrx)
				*rxvbits = 2;
			else
				if (rxfreq < glbvco3splitrx)
					*rxvbits = 1;
				else
					*rxvbits = 3;
	}

	if (txfreq < MAXLOWBAND)
	{
		if (txfreq < glbvco1splittx)
			*txvbits = 3;
		else
			if (txfreq < glbvco2splittx)
				*txvbits = 1;
			else
				if (txfreq < glbvco3splittx)
					*txvbits = 2;
				else
					*txvbits = 0;
	}
	else if (txfreq < MAXHIGHBAND)
	{
		if (txfreq < txvcosplit)
			*txvbits = 3;
		else
			*txvbits = 1;
		if (rxfreq < rxvcosplit)
			*rxvbits = 0;
		else
			*rxvbits = 2;
	}
	else if (txfreq < MAXUHFR1BAND)
	{
		if (txfreq < txvcosplit)
			*txvbits = 2;
		else
			*txvbits = 0;
		if (rxfreq < rxvcosplit)
			*rxvbits = 3;
		else
			*rxvbits = 1;
	}
	else if (txfreq < MAXUHFBAND)
	{
		if (txfreq < txvcosplit)
			*txvbits = 3;
		else
			*txvbits = 1;
		if (rxfreq < rxvcosplit)
			*rxvbits = 2;
		else
			*rxvbits = 0;
	}
	else if (txfreq < MAX800BAND)
	{
		if (txfreq > TALKAROUND800)
			*txvbits = 2;
		else
			*txvbits = 0;
		rxvbits = 0;
	}
}

unsigned int selrefreq(unsigned int refreq, unsigned int txfreq)

{
	unsigned int newrefreq;

	newrefreq = refreq;
	if (txfreq % refreq)
	{
		if (refreq == 5000)
			if (txfreq % 6250)
				fprintf(stderr, "no valid ref. frequencies for %'d\n", txfreq);
			else
			{
				fprintf(stderr, "using ref. frequency of 6250 for %'d\n",
					txfreq);
				newrefreq = 6250;
			}
		else
			if (txfreq % 5000)
				fprintf(stderr, "no valid ref. frequencies for %'d\n", txfreq);
			else
			{
				fprintf(stderr, "using ref. frequency of 5000 for %'d\n",
					txfreq);
				newrefreq = 5000;
			}
	}

	return(newrefreq);
}

unsigned int encoderefreq(unsigned int refreq)

{
	switch(refreq)
	{
		case 5000:
			return(3);
		case 6250:
			return(0);
		case 4166:
			return(2);
		default:
			return(1);
	}
}

int txplookup(float ipl)

{
	if (ipl == 0.0F) return (0xffdf);
	else if (ipl == 67.0F) return (0x45bb);
	else if (ipl == 69.3F) return (0x1cbb);
	else if (ipl == 71.9F) return (0xedba);
	else if (ipl == 74.4F) return (0xc0ba);
	else if (ipl == 77.0F) return (0x91ba);
	else if (ipl == 79.7F) return (0x60ba);
	else if (ipl == 82.5F) return (0x2dba);
	else if (ipl == 85.4F) return (0xf9b9);
	else if (ipl == 88.5F) return (0xc1b9);
	else if (ipl == 91.5F) return (0x8bb9);
	else if (ipl == 94.8F) return (0x4fb9);
	else if (ipl == 97.4F) return (0x20b9);
	else if (ipl == 100.0F) return (0xf1b8);
	else if (ipl == 103.5F) return (0xb2b8);
	else if (ipl == 107.2F) return (0x6fb8);
	else if (ipl == 110.9F) return (0x2cb8);
	else if (ipl == 114.8F) return (0xe6b7);
	else if (ipl == 118.8F) return (0x9eb7);
	else if (ipl == 123.0F) return (0x52b7);
	else if (ipl == 127.3F) return (0x04b7);
	else if (ipl == 131.8F) return (0xb3b6);
	else if (ipl == 136.5F) return (0x5eb6);
	else if (ipl == 141.3F) return (0x07b6);
	else if (ipl == 146.2F) return (0xafb5);
	else if (ipl == 151.4F) return (0x51b5);
	else if (ipl == 156.7F) return (0xf1b4);
	else if (ipl == 162.2F) return (0x8eb4);
	else if (ipl == 167.9F) return (0x27b4);
	else if (ipl == 173.8F) return (0xbcb3);
	else if (ipl == 179.9F) return (0x4eb3);
	else if (ipl == 186.2F) return (0xdcb2);
	else if (ipl == 192.8F) return (0x65b2);
	else if (ipl == 203.3F) return (0xa4b1);
	else if (ipl == 206.5F) return (0x6eb1);
	else if (ipl == 210.7F) return (0x22b1);
	else if (ipl == 218.1F) return (0x9cb0);
	else if (ipl == 225.7F) return (0x13b0);
	else if (ipl == 229.1F) return (0xd6af);
	else if (ipl == 233.6F) return (0x84af);
	else if (ipl == 241.8F) return (0xf0ae);
	else if (ipl == 250.3F) return (0x57ae);
	else if (ipl == 254.1F) return (0x12ae);
	else
	{
		fprintf(stderr, "tx pl code %f is invalid, using 254.1\n", ipl);
		return(0x12ae);
	}
}

int rxplookup(float ipl)

{
	if (ipl == 0.0F) return (0xffdf);
	else if (ipl == 67.0F) return (0xfdaf);
	else if (ipl == 69.3F) return (0x70af);
	else if (ipl == 71.9F) return (0xd1ae);
	else if (ipl == 74.4F) return (0x38ae);
	else if (ipl == 77.0F) return (0x99ad);
	else if (ipl == 79.7F) return (0xf4ac);
	else if (ipl == 82.5F) return (0x48ac);
	else if (ipl == 85.4F) return (0x97ab);
	else if (ipl == 88.5F) return (0xd9aa);
	else if (ipl == 91.5F) return (0x22aa);
	else if (ipl == 94.8F) return (0x58a9);
	else if (ipl == 97.4F) return (0xb9a8);
	else if (ipl == 100.0F) return (0x1aa8);
	else if (ipl == 103.5F) return (0x44a7);
	else if (ipl == 107.2F) return (0x62a6);
	else if (ipl == 110.9F) return (0x7fa5);
	else if (ipl == 114.8F) return (0x91a4);
	else if (ipl == 118.8F) return (0x9ca3);
	else if (ipl == 123.0F) return (0x9ba2);
	else if (ipl == 127.3F) return (0x94a1);
	else if (ipl == 131.8F) return (0x81a0);
	else if (ipl == 136.5F) return (0x619f);
	else if (ipl == 141.3F) return (0x3c9e);
	else if (ipl == 146.2F) return (0x109d);
	else if (ipl == 151.4F) return (0xd29b);
	else if (ipl == 156.7F) return (0x8e9a);
	else if (ipl == 162.2F) return (0x3d99);
	else if (ipl == 167.9F) return (0xe197);
	else if (ipl == 173.8F) return (0x7896);
	else if (ipl == 179.9F) return (0x0395);
	else if (ipl == 186.2F) return (0x8193);
	else if (ipl == 192.8F) return (0xed91);
	else if (ipl == 203.3F) return (0x5f8f);
	else if (ipl == 206.5F) return (0xa78e);
	else if (ipl == 210.7F) return (0xa68d);
	else if (ipl == 218.1F) return (0xe28b);
	else if (ipl == 225.7F) return (0x118a);
	else if (ipl == 229.1F) return (0x4189);
	else if (ipl == 233.6F) return (0x2e88);
	else if (ipl == 241.8F) return (0x3886);
	else if (ipl == 250.3F) return (0x3084);
	else if (ipl == 254.1F) return (0x4883);
	else
	{
		fprintf(stderr, "rx pl code %.3f is invalid, using 254.1\n", ipl);
		return(0x4883);
	}
}

int totlookup(int secs)

{
	unsigned int i;

	i = secs / 15;

	if (i > 31)
	{
		fprintf(stderr, "tot of %d seconds is too large, using 15 seconds\n",
			secs);
		i = 15;
	}
	i = (~ i) & 0x1f;

	return (i);
}

void calcbits(Modestruct *gmodedef, unsigned char plugbuf[])

{
	unsigned int i;
	unsigned int txvcofreq, rxvcofreq;
	unsigned int refreq;
	unsigned char accum;
	unsigned int txa, txb, txc, txn, txn1, txn2;
	unsigned int rxa, rxb, rxc, rxn, rxn1, rxn2;
	unsigned int txcix, rxcix;
	unsigned int rxif;
	unsigned int txfreq, rxfreq;
	unsigned int scanlist = 0xffffffff;
	unsigned int txdpl, rxdpl;
	unsigned int txpl, rxpl;
	unsigned int tot;
	unsigned int txvbits, rxvbits;
	unsigned int foundab = 0;

	/* Divisor math is all integer */

	txfreq = (unsigned int)floor((gmodedef -> txfreq) * 1000000.0L);
	rxfreq = (unsigned int)floor((gmodedef -> rxfreq) * 1000000.0L);

	/* Figure VCO range splits */

	selvbits(txfreq, rxfreq, &txvbits, &rxvbits);

	/* Default: "VHF RSS prefers the 5 KHz reference frequency. All other
	   radios prefer the 6.25 kHz frequency." -- From Pakman's code plug
	   documentation at http://home.xnet.com/~pakman/syntor/syntorx.htm */

	if (txfreq < MAXLOWBAND)
		refreq = 6250;
	else
		if (txfreq < MAXHIGHBAND)
			refreq = 5000;
		else
			refreq = 6250;

	/* A global reference frequency spec overrides a default */

	if (greffreq != -1)
		refreq = greffreq;

	/* Else a mode reference frequency spec overrides a global */

	if (gmodedef -> refreq != -1)
		refreq = gmodedef -> refreq;

	/* But if it won't work, use whatever will */

	refreq = selrefreq(refreq, txfreq);

	txa = txb = txc = txn = txn1 = txn2 = 0;
	rxa = rxb = rxc = rxn = rxn1 = rxn2 = 0;
	txcix = rxcix = 0;

	/* RX IF varies between bands */

	if (rxfreq < MAXLOWBAND)
		rxif = 75700000;
	else
		if (rxfreq < MAXHIGHBAND)
			rxif = 53900000;
		else
			if (rxfreq < MAXUHFR1BAND)
				rxif = 53900000;
			else
				if (rxfreq < MAXUHFBAND)
					rxif = -53900000;
				else
					if (rxfreq < MAX800BAND)
						rxif = -53900000;

	for (i = 0; i < 16; i++)
		plugbuf[i] = 0;

	if (txfreq < MAXLOWBAND)
		txvcofreq = 172800000 - txfreq;
	else
		if (txfreq > MAXUHFBAND)
			txvcofreq = txfreq / 2;
		else
			txvcofreq = txfreq;
	txn = txvcofreq / refreq;
	txc = txn % 3;
	txcix = txc;
	if (txfreq < MAXLOWBAND)
		txn1 = txn;
	else
	{
		txn1 = txn / 3;
		if (txc == 0)
			txn1--;
	}
	txa = txn1 % 63;
	if (txa == 0)
	{
		txa = 63;
		txn1 -= 63;
	}
	txn2 = txn1 / 63;
	txb = txn2 - txa;

	if (rxfreq > MAXUHFBAND)
		rxvcofreq = (rxfreq + rxif) / 2;
	else
		rxvcofreq = rxfreq + rxif;
	rxn = rxvcofreq / refreq;
	rxc = rxn % 3;
	rxcix = rxc;
	if (rxfreq < MAXLOWBAND)
		rxn1 = rxn;
	else
	{
		rxn1 = rxn / 3;
		if (rxc == 0)
			rxn1--;
	}
	rxa = rxn1 % 63;
	if (rxa == 0)
	{
		rxa = 63;
		rxn1 -= 63;
	}
	rxn2 = rxn1 / 63;
	rxb = rxn2 - rxa;

	for (i = 0; i < gmodedef -> scanlistsize; i++)
	{
		scanlist &= ~(1 << (32 - (gmodedef -> npscanlist[i])));
	}

	plugbuf[0x00] = (scanlist & 0xff000000) >> 24;
	plugbuf[0x01] = (scanlist & 0x00ff0000) >> 16;
	plugbuf[0x02] = (scanlist & 0x0000ff00) >> 8;
	plugbuf[0x03] = (scanlist & 0x000000ff);
	if (gmodedef -> txdplflag)
	{
		txdpl = gmodedef -> txdpl;
		plugbuf[0x04] |= (gmodedef -> txdplinv & 0x01) << 7;
		plugbuf[0x04] |= (dpltable[(txdpl & 0007)]) << 4;
		plugbuf[0x04] |= (dpltable[(txdpl & 0070) >> 3]) << 1;
		plugbuf[0x04] |= (dpltable[(txdpl & 0700) >> 6] & 0004) >> 2;
		plugbuf[0x05] |= (! (gmodedef -> txmpl & 0x01)) << 7;
		plugbuf[0x05] |= (1 << 6);
		plugbuf[0x05] |= (1 << 5);
		plugbuf[0x05] |= (dpltable[(txdpl & 0700) >> 6] & 0003) << 3;
		plugbuf[0x05] |= 0x07;
	}
	else if (gmodedef -> txplflag)
	{
		txpl = txplookup(gmodedef -> txpl);
		plugbuf[0x04] |= (txpl & 0xff00) >> 8;
		plugbuf[0x05] |= (! gmodedef -> txmpl & 0x01) << 7;
		/* DPL/PL bit value 0 means PL, so it's already set */
		plugbuf[0x05] |= txpl & 0x003f;
	}
	else
	{
		plugbuf[0x04] = 0xff;
		plugbuf[0x05] = 0xdf;
	}
	if (gmodedef -> rxdplflag)
	{
		rxdpl = gmodedef -> rxdpl;
		plugbuf[0x06] |= (gmodedef -> rxdplinv & 0x01) << 7;
		plugbuf[0x06] |= (dpltable[(rxdpl & 0007)]) << 4;
		plugbuf[0x06] |= (dpltable[(rxdpl & 0070) >> 3]) << 1;
		plugbuf[0x06] |= (dpltable[(rxdpl & 0700) >> 6] & 0004) >> 2;
		plugbuf[0x07] |= (! gmodedef -> rxmpl & 0x01) << 7;
		plugbuf[0x07] |= (1 << 6);
		plugbuf[0x07] |= (1 << 5);
		plugbuf[0x07] |= (dpltable[(rxdpl & 0700) >> 6] & 0003) << 3;
		plugbuf[0x07] |= 0x07;
	}
	else if (gmodedef -> rxplflag)
	{
		rxpl = rxplookup(gmodedef -> rxpl);
		plugbuf[0x06] = 0;
		plugbuf[0x07] = 0;
		plugbuf[0x06] |= (rxpl & 0xff00) >> 8;
		plugbuf[0x07] |= (! gmodedef -> rxmpl & 0x01) << 7;
		/* DPL/PL bit value 0 means PL, so it's already set */
		plugbuf[0x07] |= rxpl & 0x003f;
	}
	else
	{
		plugbuf[0x06] = 0xff;
		plugbuf[0x07] = 0xdf;
	}
	tot = totlookup(gmodedef -> timeout);
	plugbuf[0x08] = (tot & 0x1f) << 3;
	plugbuf[0x08] |= (gmodedef -> txpower & 0x01) << 2;
	plugbuf[0x08] |= encoderefreq(refreq);
	plugbuf[0x09] = (gmodedef -> scantype) << 6;
	if (! gmodedef -> tbscan)
		plugbuf[0x09] |= 1 << 5;
	plugbuf[0x09] |= (gmodedef -> p2scanmode - 1) & 0x1f;
	plugbuf[0x0a] |= (gmodedef -> npscansource) << 7;
	plugbuf[0x0a] |= (gmodedef -> squelchtype) << 5;
	plugbuf[0x0a] |= (gmodedef -> p1scanmode - 1) & 0x1f;
	accum = (txvbits << 6);
	accum |= (rxvbits << 2);
	if (txfreq < MAXLOWBAND)
		accum |= 3 << 4;
	else
		accum |= (ctable[txcix] << 4);
	if (rxfreq < MAXLOWBAND)
		if (gmodedef -> rxextender)
			accum |= 2;
		else
			accum |= 3;
	else
		accum |= ctable[rxcix];
	plugbuf[0x0b] = accum;
	plugbuf[0x0c] |= ((txb & 0x03c0) >> 2);
	plugbuf[0x0c] |= ((rxb & 0x03c0) >> 6);
	plugbuf[0x0d] |= ((txb & 0x003c) << 2);
	plugbuf[0x0d] |= ((rxb & 0x003c) >> 2);
	plugbuf[0x0e] |= ((txb & 0x0003) << 6);
	plugbuf[0x0e] |= ((rxb & 0x0003) << 2);
	plugbuf[0x0e] |= (txa & 0x0030);
	plugbuf[0x0e] |= ((rxa & 0x0030) >> 4);
	plugbuf[0x0f] |= ((txa & 0x000f) << 4);
	plugbuf[0x0f] |= (rxa & 0x000f);
}
