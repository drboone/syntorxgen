#!/usr/bin/perl
# testmemnew.pl, Boone, 07/23/02
# Generate a new syntorxgen source file for a "test ROM" style code plug
# Copyright (C) 2002, Dennis Boone, East Lansing, MI
#
# This file is part of syntorxgen.
# 
# Syntorxgen is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published
# by the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# Syntorxgen is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with syntorxgen; if not, write to the Free Software Foundation,
# Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

print <<"EOF";
nmodes 32;
txvcosplit 155.8;
rxvcosplit 150.0;
EOF
for ($i = 0; $i < 32; $i++)
{
	$a = (144.250 + ($i * 0.75));

	print "mode ", $i+1, "\n{\n";
	printf("\ttxfreq %7.3f;\n", $a);
	printf("\trxfreq %7.3f;\n", $a);
	print <<"EOF";
	txdpl 0;
	txdplinv no;
	txpl 0.0;
	txmpl no;
	rxdpl 0;
	rxdplinv no;
	rxpl 0.0;
	rxmpl no;
	timeout 0;
	txpower high;
	npscansource fixed;
	tbscan no;
	p1scanmode 1;
	p2scanmode 1;
	squelchtype andor;
	scantype none;
};
EOF
}

__END__

file formats

new
	nmodes 5;
	mode 1
	{
		txfreq 438.750;
		rxfreq 433.750;
		txdpl 345;
		rxpl 94.8;
		timeout 30;
		txpower high;
		scantype dblpri;
		npscanlist 1 2 3;
		p1scanmode 4;
		p2scanmode 5;
		squelchtype andstd;
	};

old
	MODE
	txfreq rxfreq
	txdpl txdplinv txpl txmpl 
	rxdpl rxdplinv rxpl rxmpl 
	tomins tosecs 
	pwr 
	scantype tbscan p1mode p2mode 
	squelchtype 
	scansource
	scanchannel ...
	END

