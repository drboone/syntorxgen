/* calcplug.c, Boone, 06/30/02
   Compute the bit string for one mode in a code plug
   Copyright (C) 2002, Dennis Boone, East Lansing, MI */

/* Modifications:
   06/30/02 Boone      Initial coding
   End Modifications */

#include <stdio.h>

#include "syntorxgen.h"

unsigned char ctable[3] = { 2, 1, 3 };
unsigned char dpltable[8] = { 0, 4, 2, 6, 1, 5, 3, 7 };

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

void calcbits(Modestruct *gmodedef, int plugbuf[])

{
	unsigned int i;
	unsigned int rxvcofreq;
	unsigned int refreq;
	unsigned char accum;
	unsigned int txa, txb, txc, txn, txn1, txn2;
	unsigned int rxa, rxb, rxc, rxn, rxn1, rxn2;
	unsigned int txcix, rxcix;
	float rxif;
	unsigned int txfreq, rxfreq;

	/* Default: "VHF RSS prefers the 5 KHz reference frequency. All other
	   radios prefer the 6.25 KHz frequency." -- From Pakman's code plug
	   documentation at http://home.xnet.com/~pakman/syntor/syntorx.htm */

	if (gmodedef -> txfreq < MAXLOWBAND)
		refreq = 6.25;
	else
		if (gmodedef -> txfreq < MAXHIGHBAND)
			refreq = 5.0;
		else
			refreq = 6.25;

	/* A global reference frequency spec overrides a default */

	if (greffreq != -1)
		refreq = greffreq;

	/* Else a mode reference frequency spec overrides a global */

	if (gmodedef -> refreq != -1)
		refreq = gmodedef -> refreq;

	txa = txb = txc = txn = txn1 = txn2 = 0;
	rxa = rxb = rxc = rxn = rxn1 = rxn2 = 0;
	txcix = rxcix = 0;

	/* RX IF varies between bands */

	if (gmodedef -> rxfreq < MAXLOWBAND)
		rxif = 75.7;
	else
		if (gmodedef -> rxfreq < MAXHIGHBAND)
			rxif = 53.9;
		else
			if (gmodedef -> rxfreq < MAXUHFR1BAND)
				rxif = 53.9;
			else
				if (gmodedef -> rxfreq < MAXUHFBAND)
					rxif = -53.9;
				else
					if (gmodedef -> rxfreq < MAX800BAND)
						rxif = -53.9;

	/* Divisor math is all integer */

	txfreq = int(gmodedef -> txfreq * 1000.0L);
	rxfreq = int(gmodedef -> rxfreq * 1000.0L);

	for (i = 0; i < 16; i++)
		plugbuf[i] = 0;

	txn = txfreq / refreq;
	txc = txn % 3;
	txcix = txc;
	txn1 = txn / 3;
	if (txc == 0)
		txn1--;
	txa = txn1 % 63;
	if (txa == 0)
	{
		txa = 63;
		txn1 -= 63;
	}
	txn2 = txn1 / 63;
	txb = txn2 - txa;

	rxvcofreq = rxfreq + rxif;
	rxn = rxvcofreq / refreq;
	rxc = rxn % 3;
	rxcix = rxc;
	rxn1 = rxn / 3;
	if (rxc == 0)
		rxn1--;
	rxa = rxn1 % 63;
	if (rxa == 0)
	{
		rxa = 63;
		rxn1 -= 63;
	}
	rxn2 = rxn1 / 63;
	rxb = rxn2 - rxa;

	plugbuf[0x00] = (scanlist & 0xff000000) >> 24;
	plugbuf[0x01] = (scanlist & 0x00ff0000) >> 16;
	plugbuf[0x02] = (scanlist & 0x0000ff00) >> 8;
	plugbuf[0x03] = (scanlist & 0x000000ff);
	if (txdpl != 0)
	{
		plugbuf[0x04] |= (txdplinv & 0x01) << 7;
		plugbuf[0x04] |= (dpltable[(txdpl & 0007)]) << 4;
		plugbuf[0x04] |= (dpltable[(txdpl & 0070)]) << 1;
		plugbuf[0x04] |= (dpltable[(txdpl & 0700)] & 0001);
		plugbuf[0x05] |= (txmpl & 0x01) << 7;
		plugbuf[0x05] |= (1 << 6);
		plugbuf[0x05] |= (1 << 5);
		plugbuf[0x05] |= (dpltable[(txdpl & 0700)] & 0006) << 3;
		plugbuf[0x05] |= 0x07;
	}
	else
	{
		plugbuf[0x04] |= (txpl & 0xff00) >> 8;
		/* DPL/PL bit value 0 means PL, so it's already set */
		/* DPL enable bit value 0 means PL, so it's already set */
		plugbuf[0x05] |= txpl & 0x00ff;
		plugbuf[0x05] |= (txmpl & 0x01) << 7;
	}
	if (rxdpl != 0)
	{
		plugbuf[0x06] |= (rxdplinv & 0x01) << 7;
		plugbuf[0x06] |= (dpltable[(rxdpl & 0007)]) << 4;
		plugbuf[0x06] |= (dpltable[(rxdpl & 0070)]) << 1;
		plugbuf[0x06] |= (dpltable[(rxdpl & 0700)] & 0001);
		plugbuf[0x07] |= (rxmpl & 0x01) << 7;
		plugbuf[0x07] |= (1 << 6);
		plugbuf[0x07] |= (1 << 5);
		plugbuf[0x07] |= (dpltable[(rxdpl & 0700)] & 0006) << 3;
		plugbuf[0x07] |= 0x07;
	}
	else
	{
		plugbuf[0x06] |= (rxpl & 0xff00) >> 8;
		/* DPL/PL bit value 0 means PL, so it's already set */
		/* DPL enable bit value 0 means PL, so it's already set */
		plugbuf[0x07] |= rxpl & 0x00ff;
		plugbuf[0x07] |= (rxmpl & 0x01) << 7;
	}
	plugbuf[0x08] |= (tot & 0x1f) << 3;
	plugbuf[0x08] |= (pwr & 0x01) << 2;
	plugbuf[0x08] |= 0x03;
	plugbuf[0x09] |= scantype << 6;
	plugbuf[0x09] |= tbscan << 5;
	plugbuf[0x09] |= (p2scan & 0x1f);
	plugbuf[0x0a] |= scansource << 7;
	plugbuf[0x0a] |= squelchtype << 6;
	plugbuf[0x0a] |= p2scan;
	accum = 0x40;
	if (txfreq < 155800)
		accum |= 0x80;
	if (rxvcofreq > 203900)
		accum |= 0x08;
	accum |= (ctable[txcix] << 4);
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
