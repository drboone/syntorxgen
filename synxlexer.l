/* synxgrammar.l, Boone, 05/26/02
   Lexer for Syntor X code plug generator
   Copyright (C) 2002, Dennis Boone, East Lansing, MI */

%{
#include "y.tab.h"
#define KWLISTSIZE 39

struct key
{
	char *cmd;
	int cval;
} kwlist[KWLISTSIZE] =
{
	"GREFFREQ",		GREFFREQ,
	"SPLITFREQ",	SPLITFREQ,
	"NMODES",		NMODES,
	"REFFREQ",		REFFREQ,
	"RANGE",		RANGE,
	"MODE",			MODE,
	"NPSCANLIST",	NPSCANLIST,
	"TXDPL",		TXDPL,
	"TXDPLINV",		TXDPLINV,
	"TXPL",			TXPL,
	"TXMPL",		TXMPL,
	"RXDPL",		RXDPL,
	"RXDPLINV",		RXDPLINV,
	"RXPL",			RXPL,
	"RXMPL",		RXMPL,
	"TIMEOUT",		TIMEOUT,
	"TXPOWER",		TXPOWER,
	"SCANTYPE",		SCANTYPE,
	"TBSCAN",		TBSCAN,
	"P2SCANMODE",	P2SCANMODE,
	"NPSCANSOURCE",	NPSCANSOURCE,
	"SQUELCHTYPE",	SQUELCHTYPE,
	"P1SCANMODE",	P1SCANMODE,
	"TXFREQ",		TXFREQ,
	"RXFREQ",		RXFREQ,
	"HIGH",			HIGH,
	"LOW",			LOW,
	"NONE",			NONE,
	"NONPRI",		NONPRI,
	"SGLPRI",		SGLPRI,
	"DBLPRI",		DBLPRI,
	"YES",			YES,
	"NO",			NO,
	"SELECTABLE",	SELECTABLE,
	"FIXED",		FIXED,
	"STDSTD",		STDSTD,
	"ANDSTD",		ANDSTD,
	"ANDOR",		ANDOR,
	"ERROR",		ERROR
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
DEFAULT			[^#;{} \n\t0-9A-Za-z]

%s comment

%%

{NEWLINE}		glineno++; BEGIN(INITIAL);
{SHARP}			BEGIN(comment);
<comment>[^\n]+	
{WHITESPACE}	
{SEMICOLON}		return(';');
{LBRACE}		return('{');
{RBRACE}		return('}');
{DOUBLE}		yylval.dval = atof(yytext); return(DOUBLE);
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
{DEFAULT}		{
					fprintf(stderr, "invalid character %c at line %d\n",
						yytext[0], glineno);
				}

%%
