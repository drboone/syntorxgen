#define MAXMODES 256
#define YYERROR_VERBOSE 1

#define MAXSTR 256

#define MODEBITSIZE 16

#define HEX 1
#define SRECORD 2

typedef struct
{
	int defined;
	int scanlistsize;
	int npscanlist[MAXMODES];
	int txdplflag;
	int txdpl;
	int txplflag;
	double txpl;
	int rxdplflag;
	int rxdpl;
	int rxplflag;
	double rxpl;
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
} Modestruct;

double greffreq = -1;
double gsplitfreq;
Modestruct gmodedef[MAXMODES];
Modestruct gscratchmodedef;
int gscratchlist[MAXMODES];
int gscratchlistsize = 0;
int glineno = 1;
int gnmodes = 32;
int gdebug = 0;

