%{
/* synxgrammar.y, Boone, 06/02/02
   Bison grammar for Syntor X code plug generator
   Copyright (C) 2002, Dennis Boone, East Lansing, MI */

/* Modifications:
   06/02/02 Boone      Initial coding
   End Modifications */

#include <stdio.h>
#include <errno.h>
#include <getopt.h>
#include <unistd.h>

#define INSTANTIATE
#include "syntorxgen.h"

void calcbits(Modestruct *, unsigned char *);

void yyerror(char *s)

{
	fprintf(stderr, "%s on line %d\n", s, glineno);
}

void initmode(Modestruct *m)

{
	m -> defined = 0;
	m -> scanlistsize = 0;
	memset(m -> npscanlist, 0, sizeof(m -> npscanlist));
	m -> txdplflag = 0;
	m -> txdpl = 0;
	m -> txdplinv = 0;
	m -> txplflag = 0;
	m -> txpl = 0.0;
	m -> txmpl = 0;
	m -> rxdplflag = 0;
	m -> rxdpl = 0;
	m -> rxdplinv = 0;
	m -> rxplflag = 0;
	m -> rxpl = 0.0;
	m -> rxmpl = 0;
	m -> timeout = 0;
	m -> txpower = 0;
	m -> refreq = -1;
	m -> scantype = 0;
	m -> tbscan = 0;
	m -> p2scanmode = 0;
	m -> npscansource = 0;
	m -> squelchtype = 0;
	m -> p1scanmode = 0;
	m -> txfreq = 0.0;
	m -> rxfreq = 0.0;
}

%}

%union
{
	char	*sval;
	double	dval;
	long	ival;
	long	keyword;
}

%start codeplug

%token <dval> DOUBLE
%token <ival> INTEGER

%token <keyword> GREFFREQ NMODES REFFREQ MODE TXVCOSPLIT RXVCOSPLIT
%token <keyword> NPSCANLIST TXDPL TXDPLINV TXPL RXDPL RXDPLINV RXPL
%token <keyword> TXMPL RXMPL
%token <keyword> SCANTYPE TBSCAN TIMEOUT TXPOWER 
%token <keyword> P2SCANMODE NPSCANSOURCE
%token <keyword> SQUELCHTYPE P1SCANMODE TXFREQ RXFREQ
%token <keyword> HIGH LOW NONE NONPRI SGLPRI DBLPRI YES NO
%token <keyword> SELECTABLE FIXED STDSTD ANDSTD ANDOR
%token <keyword> ERROR

%type <keyword> high low none nonpri sglpri dblpri yes no selectable fixed
%type <keyword> stdstd andstd andor hiorlow scantype yesorno selorfixed
%type <keyword> sqtype

%%

codeplug:			stmtstream
					;

stmtstream:			/* empty */
					| stmtstream gstmt
					;

gstmt:				/* empty */
					| stmt ';'
					;

stmt:				/* empty */
					| GREFFREQ DOUBLE
						{
							greffreq = $2;
						}
					| TXVCOSPLIT DOUBLE
						{
							gtxvcosplit = $2;
						}
					| RXVCOSPLIT DOUBLE
						{
							grxvcosplit = $2;
						}
					| NMODES INTEGER
						{
							gnmodes = $2;
						}
					| MODE INTEGER mstmtblock
						{
							if ($2 > MAXMODES)
							{
								fprintf(stderr, "mode %d is larger than "
									"MAXMODES (%d) at line %d\n",
									$2, MAXMODES, glineno);
								exit(EINVAL);
							}
							gmodedef[$2-1] = gscratchmodedef;
							gmodedef[$2-1].defined = 1;
							gscratchlistsize = 0;
							initmode(&gscratchmodedef);
						}
					| ERROR
						{
							fprintf(stderr, "unexpected token %s;"
								" expecting global config statements at line %d\n",
								yylval.sval, glineno);
						}
					;

mstmtblock:			'{' mstmtstream '}'
					| ERROR
						{
							fprintf(stderr, "unexpected token %s;"
								" expecting a left brace at line %d\n",
								yylval.sval, glineno);
						}
					;

mstmtstream:		/* empty */
					| mstmtstream xmstmt
					| ERROR
						{
							fprintf(stderr, "unexpected token %s;"
								" expecting mode config statments at line %d\n",
								yylval.sval, glineno);
						}
					;

xmstmt:				/* empty */
					| mstmt ';'
					| ERROR
						{
								fprintf(stderr, "unexpected token at line %d\n",
									glineno);
						}
					;

mstmt:				NPSCANLIST intlist
						{
							memcpy(gscratchmodedef.npscanlist,
								gscratchlist, sizeof(int)*gscratchlistsize);
							gscratchmodedef.scanlistsize = gscratchlistsize;
						}
					| TXDPL INTEGER
						{
							char tooct[16];

							gscratchmodedef.txdplflag = 1;
							gscratchmodedef.txplflag = 0;
							sprintf(tooct, "%d", $2);
							sscanf(tooct, "%o", &gscratchmodedef.txdpl);
						}
					| TXDPLINV yesorno
						{
							gscratchmodedef.txdplinv = $2;
						}
					| TXPL DOUBLE
						{
							gscratchmodedef.txplflag = 1;
							gscratchmodedef.txdplflag = 0;
							gscratchmodedef.txpl = $2;
						}
					| TXMPL yesorno
						{
							gscratchmodedef.txmpl = $2;
						}
					| RXDPL INTEGER
						{
							char tooct[16];

							gscratchmodedef.rxdplflag = 1;
							gscratchmodedef.rxplflag = 0;
							sprintf(tooct, "%d", $2);
							sscanf(tooct, "%o", &gscratchmodedef.rxdpl);
						}
					| RXDPLINV yesorno
						{
							gscratchmodedef.txdplinv = $2;
						}
					| RXPL DOUBLE
						{
							gscratchmodedef.rxplflag = 1;
							gscratchmodedef.rxdplflag = 0;
							gscratchmodedef.rxpl = $2;
						}
					| RXMPL yesorno
						{
							gscratchmodedef.rxmpl = $2;
						}
					| TIMEOUT INTEGER
						{
							if ((($2 % 15) != 0) ||
								($2 > 465))
							{
								fprintf(stderr, "timeout value %d invalid "
									"at line %d; must be 0-465, evenly "
									"divisible by 15 seconds\n",
									$2, glineno);
								exit(EINVAL);
							}
							gscratchmodedef.timeout = $2;
						}
					| TXPOWER hiorlow
						{
							gscratchmodedef.txpower = $2;
						}
					| REFFREQ INTEGER
						{
							if (($1 == 4166) ||
								($1 == 5000) ||
								($1 == 6250))
							{
								gscratchmodedef.refreq = $2;
							}
							else
							{
								fprintf(stderr, "reference frequency "
									"%d is invalid at line %d\n",
									$1, glineno);
								exit(EINVAL);
							}
						}
					| SCANTYPE scantype
						{
							gscratchmodedef.scantype = $2;
						}
					| TBSCAN yesorno
						{
							gscratchmodedef.tbscan = $2;
						}
					| P2SCANMODE INTEGER
						{
							gscratchmodedef.p2scanmode = $2;
						}
					| NPSCANSOURCE selorfixed
						{
							gscratchmodedef.npscansource = $2;
						}
					| SQUELCHTYPE sqtype
						{
							gscratchmodedef.squelchtype = $2;
						}
					| P1SCANMODE INTEGER
						{
							gscratchmodedef.p1scanmode = $2;
						}
					| TXFREQ DOUBLE
						{
							gscratchmodedef.txfreq = $2;
						}
					| RXFREQ DOUBLE
						{
							gscratchmodedef.rxfreq = $2;
						}
					| ERROR
						{
							fprintf(stderr, "unexpected token %s"
								" at line %d\n", yylval.sval, glineno);
						}
					;

intlist:			/* empty */
					| intlist INTEGER
						{
							gscratchlist[gscratchlistsize] = $2;
							gscratchlistsize++;
						}
					| intlist ERROR
						{
							fprintf(stderr, "unexpected token %s;"
								" expecting an integer at line %d\n",
								yylval.sval, glineno);
						}
					| ERROR
						{
							fprintf(stderr, "unexpected token %s;"
								" expecting an integer at line %d\n",
								yylval.sval, glineno);
						}
					;

hiorlow:			high
					| low
					;

high:				HIGH
						{
							$$ = 1;
						}
					;

low:				LOW
						{
							$$ = 0;
						}
					;

scantype:			none
					| nonpri
					| sglpri
					| dblpri
					| ERROR
						{
							fprintf(stderr, "unexpected token %s;"
								" expecting scan type at line %d\n",
								yylval.sval, glineno);
						}
					;
					
none:				NONE
						{
							$$ = 2;
						}
					;

nonpri:				NONPRI
						{
							$$ = 3;
						}
					;

sglpri:				SGLPRI
						{
							$$ = 1;
						}
					;

dblpri:				DBLPRI
						{
							$$ = 0;
						}
					;

yesorno:			yes
					| no
					| ERROR
						{
							fprintf(stderr, "unexpected token %s;"
								" expecting YES or NO at line %d\n",
								yylval.sval, glineno);
						}
					;
					
yes:				YES
						{
							$$ = 1;
						}
					;

no:					NO
						{
							$$ = 0;
						}
					;

selorfixed:			selectable
					| fixed
					| ERROR
						{
							fprintf(stderr, "unexpected token %s;"
								" expecting SELECTABLE or FIXED"
								" at line %d\n",
								yylval.sval, glineno);
						}
					;
					
selectable:			SELECTABLE
						{
							$$ = 0;
						}
					;

fixed:				FIXED
						{
							$$ = 1;
						}
					;

sqtype:				stdstd
					| andstd
					| andor
					| ERROR
						{
							fprintf(stderr, "unexpected token %s;"
								" expecting squelch type at line %d\n",
								yylval.sval, glineno);
						}
					;
					
stdstd:				STDSTD
						{
							$$ = 3;
						}
					;

andstd:				ANDSTD
						{
							$$ = 1;
						}
					;

andor:				ANDOR
						{
							$$ = 0;
						}
					;

%%

void dumpmodes()

{
	int i, j;

	for (i = 0; i < gnmodes; i++)
	{
		if (gmodedef[i].defined)
		{
			printf("Mode %d:\n", i+1);
			printf("\tScan list size: %d\n", gmodedef[i].scanlistsize);
			printf("\tModes scanned:\n\t\t");
			for (j = 0; j < gmodedef[i].scanlistsize; j++)
				printf("%d ", gmodedef[i].npscanlist[j]);
			puts("");
			printf("\tTX uses DPL: %s\n", 
				gmodedef[i].txdplflag ? "yes" : "no");
			printf("\tTX DPL code: %d\n", gmodedef[i].txdpl);
			printf("\tTX uses PL: %s\n", 
				gmodedef[i].txplflag ? "yes" : "no");
			printf("\tTX PL frequency: %5.1f\n", gmodedef[i].txpl);
			printf("\tRX uses DPL: %s\n", 
				gmodedef[i].rxdplflag ? "yes" : "no");
			printf("\tRX DPL code: %d\n", gmodedef[i].rxdpl);
			printf("\tRX uses PL: %s\n", 
				gmodedef[i].rxplflag ? "yes" : "no");
			printf("\tRX PL frequency: %5.1f\n", gmodedef[i].rxpl);
			printf("\tTimeout (secs): %d\n", gmodedef[i].timeout);
			printf("\tTX power: %s\n", 
				gmodedef[i].txpower ? "high" : "low");
			if (gmodedef[i].refreq == -1)
				puts("\tReference frequency: default");
			else
				printf("\tReference frequency: %d\n", gmodedef[i].refreq);
			switch (gmodedef[i].scantype)
			{
				case 0:
					puts("\tScan type: double priority");
					break;
				case 1:
					puts("\tScan type: single priority");
					break;
				case 2:
					puts("\tScan type: none");
					break;
				case 3:
					puts("\tScan type: non-priority");
					break;
			}
			printf("\tTalkback scan? %s\n", 
				gmodedef[i].tbscan ? "yes" : "no");
			printf("\tPriority 2 scan mode: %d\n", gmodedef[i].p2scanmode);
			printf("\tNon-priority scan source: %s\n",
				gmodedef[i].npscansource ? "fixed" : "selectable");
			switch (gmodedef[i].squelchtype)
			{
				case 3:
					puts("\tSquelch type: STD/STD");
					break;
				case 1:
					puts("\tSquelch type: AND/STD");
					break;
				case 0:
					puts("\tSquelch type: AND/OR");
					break;
			}
			printf("\tPriority 1 scan mode: %d\n", gmodedef[i].p1scanmode);
			printf("\tTX frequency: %8.4f\n", gmodedef[i].txfreq);
			printf("\tRX frequency: %8.4f\n", gmodedef[i].rxfreq);
		}
		else
			printf("Mode %d not defined\n", i+1);
	}
}

void zerobits(unsigned char bitbuf[])

{
	int i;
	for (i = 0; i < MODEBITSIZE; i++)
		bitbuf[i] = 0;
}

void writehex(unsigned char bitbuf[], FILE *outfile)

{
	int i;
	int first = 1;

	for (i = 0; i < MODEBITSIZE; i++)
	{
		if (! first)
		{
			putc(' ', outfile);
		}
		fprintf(outfile, "%02X", bitbuf[i]);
		first = 0;
	}
	putc('\n', outfile);
}

int writesrecord(unsigned char bitbuf[], FILE *outfile, int offset)

{
	int i;
	unsigned char checksum = 0;

	fprintf(outfile, "S113%04X", offset);
	for (i = 0; i < MODEBITSIZE; i++)
	{
		fprintf(outfile, "%02X", bitbuf[i]);
		checksum += bitbuf[i];
	}
	checksum = ~checksum;
	fprintf(outfile, "%02X\n", checksum);
}

void writeplug(int outfmt, FILE *outfile)

{
	int i;
	unsigned char bitbuf[MODEBITSIZE];
	unsigned int offset = 0;
	unsigned char checksum = 0;

	for (i = 0; i < gnmodes; i++)
	{
		if (gmodedef[i].defined)
			calcbits(&(gmodedef[i]), bitbuf);
		else
			zerobits(bitbuf);

		if (outfmt == HEX)
			writehex(bitbuf, outfile);
		else
			if (outfmt == SRECORD)
			{
				writesrecord(bitbuf, outfile, offset);
				offset += MODEBITSIZE;
			}
	}

	if (outfmt == SRECORD)
	{
		checksum = 3 + ((gnmodes >> 8) & 0xff) + (gnmodes & 0xff);
		checksum = ~checksum;
		fprintf(outfile, "S503%04X%02X\n", gnmodes, checksum);
		fputs("S9030000FC\n", outfile);
	}
}

int main(int argc, char *argv[])

{
	int i;
	int c;
	int outfmt = HEX;
	FILE *outfile;
	int rc;

/* Initialize */

	for (i = 0; i < MAXMODES; i++)
	{
		gscratchlist[i] = 0;
		initmode(&(gmodedef[i]));
	}
	initmode(&gscratchmodedef);
	greffreq = -1;
	gscratchlistsize = 0;
	glineno = 1;
	gnmodes = 32;
	gdebug = 0;

	if ((outfile = fdopen(fileno(stdout), "w")) == NULL)
	{
		perror(optarg);
		exit(errno);
	}

/* Command line */

	while ((c = getopt(argc, argv, "o:dhsxy")) != -1)
	{
		switch (c)
		{
			case 'o':
				if (freopen(optarg, "w", outfile) == NULL)
				{
					perror(optarg);
					exit(errno);
				}
				break;
			case 'd':
				gdebug = 1;
				break;
			case 'x':
				outfmt = HEX;
				break;
			case 's':
				outfmt = SRECORD;
				break;
			case 'y':
				yydebug = 1;
				break;
			case 'h':
			default:
				fprintf(stderr, "usage: %s [-dhsxy] [-o outfile]\n", argv[0]);
				exit(EINVAL);
		}
	}

/* Read a definition */

	rc = yyparse();

/* Output requested products */

	if (gdebug)
		dumpmodes();

	if (! rc)
		writeplug(outfmt, outfile);

/* Done */

	exit(0);
}
