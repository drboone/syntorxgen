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

#define MAXLOWBAND 100000000
#define MAXHIGHBAND 250000000
#define MAXUHFBAND 550000000
#define MAX800BAND 950000000

/* Low-band radios have four sub-splits.  These are the operating
   frequencies which correspond to the default splits. */

#define DEFLBVCO1SPLIT 38100000
#define DEFLBVCO2SPLIT 47100000
#define DEFLBVCO3SPLIT 56900000

/* UHF Range 1 radios use high-side injection, all others low-side, so
   we need to be able to tell the difference.  This definition assumes
   that anyone programming an R1 frequency will be using an unmodified
   radio in a factory-approved way. */

#define MAXUHFR1BAND 420000000

/* 800 radios use one range for rx and tx, except in talkaround, when
   they shift transmit up to the receive range.  The split frequency
   is needed to calculate v-bits. */

#define TALKAROUND800 825000000

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
} Modestruct;

EXTERN int greffreq;
EXTERN double gtxvcosplit;
EXTERN double grxvcosplit;
EXTERN double glbvco1split;
EXTERN double glbvco2split;
EXTERN double glbvco3split;
EXTERN Modestruct gmodedef[MAXMODES];
EXTERN Modestruct gscratchmodedef;
EXTERN int gscratchlist[MAXMODES];
EXTERN int gscratchlistsize;
EXTERN int glineno;
EXTERN int gnmodes;
EXTERN int gdebug;

