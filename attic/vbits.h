/* vbits.h, Boone, 07/23/02
   Table of frequency limits for various v-bit settings
   Copyright (C) 2002, Dennis Boone, East Lansing, MI  */

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

/* Magic numbers for bands */

#define B_LOW  0
#define B_HIGH 1
#define B_UHF  2
#define B_800  3

/* Magic numbers for ranges */

#define R_1    1
#define R_2    2
#define R_3    3
#define R_4    4
#define R_5    5

/* Magic numbers for transmit and receive */

#define RX     0
#define TX     1

/* Would it be useful to have high- or low-side injection in the table? */

typedef struct
{
	int band;
	int range;
	int v0;
	int v1;
	double lowfreq;
	double highfreq;
	int rxtx;
} Vbitstruct;

/* This table assumes factory standard radios.  You have to use the
   config file to adjust these if you're programming out of band and/or
   programming a modified radio.  This default data is based on the
   Pakman code plug documentation. */

Vbitstruct gvbittbl[] =
{
	B_LOW, R_1, 0, 0, 29.7L, 38.1L, RX,
	B_LOW, R_1, 1, 0, 38.1L, 47.1L, RX,
	B_LOW, R_1, 0, 1, 47.1L, 56.9L, RX,
	B_LOW, R_1, 1, 1, 56.9L, 67.5L, RX,
	B_LOW, R_1, 0, 0, 29.7L, 38.1L, TX,
	B_LOW, R_1, 1, 0, 38.1L, 47.1L, TX,
	B_LOW, R_1, 0, 1, 47.1L, 56.9L, TX,
	B_LOW, R_1, 1, 1, 56.9L, 67.5L, TX,
	B_HIGH, R_1, 0, 0, 136.0L, 144.6L, RX,
	B_HIGH, R_1, 0, 1, 144.6L, 154.4L, RX,
	B_HIGH, R_1, 1, 1, 136.0L, 144.0L, TX,
	B_HIGH, R_1, 1, 0, 144.0L, 154.4L, TX,
	B_HIGH, R_2, 0, 0, 107.7L, 150.0L, RX,
	B_HIGH, R_2, 0, 1, 150,0L, 174.0L, RX,
	B_HIGH, R_2, 1, 1, 150.0L, 161.8L, TX,
	B_HIGH, R_2, 1, 0, 161.8L, 174.0L, TX,
	B_UHF, R_1, 1, 1, 406.0L, 412.8L, RX,
	B_UHF, R_1, 1, 0, 412.8L, 420.0L, RX,
	B_UHF, R_1, 0, 1, 406.0L, 412.8L, TX,
	B_UHF, R_1, 0, 0, 412.8L, 420.0L, TX,
	B_UHF, R_2, 0, 1, 450.0L, 459.5L, RX,
	B_UHF, R_2, 0, 0, 459.5L, 470.0L, RX,
	B_UHF, R_2, 1, 1, 450.0L, 459.5L, TX,
	B_UHF, R_2, 1, 0, 459.5L, 470.0L, TX,
/* Does anyone have the factory frequency limits for the various v-bit
   ranges of the Range 3, 4 and 5 UHF radios?  I've been unable to find
   a source. */
	B_UHF, R_3, 0, 1, 470.0L, 470.0L, RX,
	B_UHF, R_3, 0, 0, 488.0L, 488.0L, RX,
	B_UHF, R_3, 1, 1, 470.0L, 470.0L, TX,
	B_UHF, R_3, 1, 0, 488.0L, 488.0L, TX,
	B_UHF, R_4, 0, 1, 482.0L, 482.0L, RX,
	B_UHF, R_4, 0, 0, 500.0L, 500.0L, RX,
	B_UHF, R_4, 1, 1, 482.0L, 482.0L, TX,
	B_UHF, R_4, 1, 0, 500.0L, 500.0L, TX,
	B_UHF, R_5, 0, 1, 494.0L, 494.0L, RX,
	B_UHF, R_5, 0, 0, 512.0L, 512.0L, RX,
	B_UHF, R_5, 1, 1, 494.0L, 494.0L, TX,
	B_UHF, R_5, 1, 0, 512.0L, 512.0L, TX,
	B_800, R_1, 0, 0, 851.0L, 878.9L, RX,
	B_800, R_1, 0, 0, 797.1L, 825.0L, TX,
	B_800, R_1, 0, 1, 851.0L, 870.0L, TX,
};
