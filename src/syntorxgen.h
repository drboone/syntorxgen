/* syntorxgen.h, Boone, 07/23/02
   Global definitions for syntorxgen
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

#ifndef SYNXGEN_H
#define SYNXGEN_H

#ifdef INSTANTIATE
#define EXTERN
#else
#define EXTERN extern
#endif

#define MAXMODES 256
#define YYERROR_VERBOSE 1

#define MAXSTR 256

#define MODEBITSIZE 16

#define BINARY 1
#define HEX 2
#define SRECORD 3

/* Guesses as to the upper frequency limits various models of Syntor could
   be hacked to do; used to decide for which band of radio this mode def is
   targeted.  This is primitive; turning a high-band rig into a 220 rig
   might require changing things around from high- to low-side injection
   for example; the program isn't that smart.  The main hope is that these
   are wide enough for normal use, without overlapping. */

#define DEFMAXLOWBAND 100000000
#define DEFMAXHIGHBAND 250000000
#define DEFMAXUHFBAND 550000000
#define DEFMAX800BAND 950000000

/* Low-band radios have four sub-splits.  These are the operating
   frequencies which correspond to the default splits. */

#define DEFLBVCO1SPLITTX 40200000
#define DEFLBVCO2SPLITTX 50000000
#define DEFLBVCO3SPLITTX 59000000

#define DEFLBVCO1SPLITRX 38100000
#define DEFLBVCO2SPLITRX 47100000
#define DEFLBVCO3SPLITRX 56900000

/* UHF Range 1 radios use high-side injection, all others low-side, so
   we need to be able to tell the difference.  This definition assumes
   that anyone programming an R1 frequency will be using an unmodified
   radio in a factory-approved way.  Update: ok, the first actual R1
   radio I met and wanted to program at 431.xxx bit me.  Def'n is now
   435, which is halfway between the factory top of a R1 radio and the
   factory bottom of an R2. */

#define DEFMAXUHFR1BAND 435000000

/* 800 radios use one range for rx and tx, except in talkaround, when
   they shift transmit up to the receive range.  The split frequency
   is needed to calculate v-bits. */

#define DEFTALKAROUND800 825000000

typedef struct
{
	int defined;
	char label[81];
	int scanlistsize;
	int npscanlist[MAXMODES];
	int txdplflag;
	int txdpl;
	int txdplinv;
	int txplflag;
	double txpl;
	int txmpl;
	int rxdplflag;
	int rxdpl;
	int rxdplinv;
	int rxplflag;
	double rxpl;
	int rxmpl;
	int timeout;
	int txpower;
	int refreq;
	int scantype;
	int tbscan;
	int p2scanmode;
	int npscansource;
	int squelchtype;
	int p1scanmode;
	double txfreq;
	double rxfreq;
	int rxextender;
	double pmtxsplit;
	double pmrxsplit;
} Modestruct;

EXTERN int greffreq;
EXTERN int gtrvbitinvert;
EXTERN double gtxvcosplit;
EXTERN double grxvcosplit;
EXTERN double glbvco1splittx;
EXTERN double glbvco2splittx;
EXTERN double glbvco3splittx;
EXTERN double glbvco1splitrx;
EXTERN double glbvco2splitrx;
EXTERN double glbvco3splitrx;
EXTERN long gmaxlowband;
EXTERN long gmaxhighband;
EXTERN long gmaxuhfband;
EXTERN long gmax800band;
EXTERN long gmaxuhfr1band;
EXTERN long gtalkaround800;
EXTERN Modestruct gmodedef[MAXMODES];
EXTERN Modestruct gscratchmodedef;
EXTERN int gscratchlist[MAXMODES];
EXTERN int gscratchlistsize;
EXTERN int glineno;
EXTERN int gnmodes;
EXTERN int gdebug;
EXTERN char *optarg;

#endif /* !SYNXGEN_H */
