#!/usr/bin/perl
# testfreqnew.pl, Boone, 07/23/02
# Generate new syntorxgen source for frequency "test ROM" code plug
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

	print stderr "Enter all frequencies in Hz.\n";
	$nmodes = &prompt("Number of modes: ");
	$mainlow = &prompt("Main bank low frequency: ");
	$mainstep = &prompt("Main bank step: ");
	$txvcosplit = &prompt("Transmit VCO split frequency: ") / 1000000.0;
	$rxvcosplit = &prompt("Receive VCO split frequency: ") / 1000000.0;

	$mainhigh = $mainlow + (($nmodes - 1) * $mainstep);

	printf stderr ("Main bank will cover %d to %d by %d\n",
		$mainlow, $mainhigh, $mainstep);

	print <<"EOF";
#!syntorxgen
# This is a syntorxgen input file for generating a test ROM designed
# to check frequency coverage.
EOF

	printf("nmodes %d;\n", $nmodes);
	printf("txvcosplit %7.3f;\n", $txvcosplit);
	printf("rxvcosplit %7.3f;\n", $rxvcosplit);

	for ($i = 0; $i < $nmodes; $i++)
	{
		$a = (($mainlow / 1000000) + ($i * ($mainstep / 1000000)));

		print "mode ", $i+1, "\n{\n";
		printf("\ttxfreq %7.3f;\n", $a);
		printf("\trxfreq %7.3f;\n", $a);
		print <<"EOF";
	txdplinv no;
	txmpl no;
	rxdplinv no;
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

	exit(0);

	sub prompt
	{
		my $prompt = shift;
		my $answer;

		$answer = "";
		while ($answer !~ /^[0-9.]+$/)
		{
			print stderr $prompt;
			chomp($answer = <>);
		}

		return($answer);
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

