/* synxgrammar.l, Boone, 07/23/02
   Lexer for Syntor X code plug generator
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

%{
#include <stdlib.h>
#include <math.h>
#include "y.tab.h"
#define KWLISTSIZE 47

struct key
{
	char *cmd;
	int cval;
} kwlist[KWLISTSIZE] =
{
	"GREFFREQ",			GREFFREQ,
	"TXVCOSPLIT",		TXVCOSPLIT,
	"RXVCOSPLIT",		RXVCOSPLIT,
	"LBVCO1SPLITTX",	LBVCO1SPLITTX,
	"LBVCO2SPLITTX",	LBVCO2SPLITTX,
	"LBVCO3SPLITTX",	LBVCO3SPLITTX,
	"LBVCO1SPLITRX",	LBVCO1SPLITRX,
	"LBVCO2SPLITRX",	LBVCO2SPLITRX,
	"LBVCO3SPLITRX",	LBVCO3SPLITRX,
	"NMODES",			NMODES,
	"REFFREQ",			REFFREQ,
	"MODE",				MODE,
	"LABEL",			LABEL,
	"NPSCANLIST",		NPSCANLIST,
	"TXDPL",			TXDPL,
	"TXDPLINV",			TXDPLINV,
	"TXPL",				TXPL,
	"TXMPL",			TXMPL,
	"RXDPL",			RXDPL,
	"RXDPLINV",			RXDPLINV,
	"RXPL",				RXPL,
	"RXMPL",			RXMPL,
	"TIMEOUT",			TIMEOUT,
	"TXPOWER",			TXPOWER,
	"SCANTYPE",			SCANTYPE,
	"TBSCAN",			TBSCAN,
	"P2SCANMODE",		P2SCANMODE,
	"NPSCANSOURCE",		NPSCANSOURCE,
	"SQUELCHTYPE",		SQUELCHTYPE,
	"P1SCANMODE",		P1SCANMODE,
	"TXFREQ",			TXFREQ,
	"RXFREQ",			RXFREQ,
	"RXEXTENDER",		RXEXTENDER,
	"HIGH",				HIGH,
	"LOW",				LOW,
	"NONE",				NONE,
	"NONPRI",			NONPRI,
	"SGLPRI",			SGLPRI,
	"DBLPRI",			DBLPRI,
	"YES",				YES,
	"NO",				NO,
	"SELECTABLE",		SELECTABLE,
	"FIXED",			FIXED,
	"STDSTD",			STDSTD,
	"ANDSTD",			ANDSTD,
	"ANDOR",			ANDOR,
	"ERROR",			ERROR
};

int i;
extern int glineno;
%}

SHARP			[#]
SEMICOLON		[;]
LBRACE			[{]
RBRACE			[}]
NEWLINE			[\n]
WHITESPACE		[ \t]+
INTEGER			[0-9]+
DOUBLE			[0-9]*[.]+[0-9]+
KEYWORD			[A-Za-z][A-Za-z0-9]*
DQUOTE			["]
DEFAULT			[^#;{} \n\t0-9A-Za-z]

%s comment
%s string

%%

{NEWLINE}		glineno++; BEGIN(INITIAL);
{SHARP}			BEGIN(comment);
<comment>[^\n]+	
{WHITESPACE}	
{SEMICOLON}		return(';');
{LBRACE}		return('{');
{RBRACE}		return('}');
{DOUBLE}		{
					yylval.dval = atof(yytext);
					yylval.dval = (floor(yylval.dval * 1000000.0) / 1000000.0);
					return(DOUBLE);
				}
{INTEGER}		yylval.ival = atoi(yytext); return(INTEGER);
{KEYWORD}		{
					for (i = 0; i < KWLISTSIZE; i++)
					{
						if (strcasecmp(kwlist[i].cmd, yytext) == 0)
						{
							yylval.keyword = kwlist[i].cval;
							break;
						}
					}
					if (i < KWLISTSIZE)
						return(kwlist[i].cval);
					else
					{
						yylval.sval = yytext;
						return(ERROR);
					}
				}
{DQUOTE}		BEGIN(string);
<string>[^"]+{DQUOTE}	{
					BEGIN(INITIAL);
					yytext[strlen(yytext)-1] = 0;
					yylval.sval = yytext;
					return(STRING);
				}
{DEFAULT}		{
					fprintf(stderr, "invalid character %c at line %d\n",
						yytext[0], glineno);
				}

%%
