#!/usr/bin/perl
# convert, Boone, 07/24/02
# Convert old-style input files to new-style
# Copyright (C) 2002, Dennis Boone, East Lansing, MI
#
# Modifications:
# 07/24/02 Boone      Initial coding
# End Modifications
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

	$/ = "";
	$file = <>;
	$file =~ tr/a-z/A-Z/;
	@tokens = split(/\s+/, $file);
	$in = 0;
	$n = 1;

	while (1)
	{
		$word = shift(@tokens);
		last if (! $word);
		if ($word ne "MODE") { die "expected MODE but got " . $word; }
		print "mode ", $n++, "\n{";
		($txfreq, $rxfreq, $txdpl, $txdplinv, $txpl, $txmpl,
			$rxdpl, $rxdplinv, $rxpl, $rxmpl, $tomins, $tosecs,
			$pwr, $scantype, $tbscan, $p1mode, $p2mode, $squelchtype,
			$scansource) = @tokens[0..18];
		$txdplinv += 0;
		$rxdplinv += 0;
		print "\ttxfreq ", $txfreq / 1000.0, ";\n";
		print "\trxfreq ", $rxfreq / 1000.0, ";\n";
		print "\ttxdpl ", $txdpl, ";\n" if ($txdpl);
		print "\ttxdplinv ", $txdplinv ? "yes" : "no", ";\n";
		print "\ttxpl ", $txpl, ";\n" if ($rxpl != 0.0);
		print "\trxdpl ", $txdpl, ";\n" if ($txdpl);
		print "\trxdplinv ", $rxdplinv ? "yes" : "no", ";\n";
		print "\trxpl ", $rxpl, ";\n" if ($rxpl != 0.0);
		print "\ttimeout ", (($tomins * 60) + $tosecs), ";\n";
		print "\ttxpower ", $pwr, ";\n";
		print "\tscantype ", $scantype, ";\n";
		print "\ttbscan ", $tbscan, ";\n";
		print "\tp1scanmode ", $p1mode, ";\n";
		print "\tp2scanmode ", $p2mode, ";\n";
		print "\tsquelchtype ", $squelchtype, ";\n";
		print "\tnpscansource ", $scansource, ";\n";
		for (1 .. 19)
		{
			shift(@tokens);
		}
		$first = 1;
		while (($word = shift(@tokens)) ne "END")
		{
			if ($first)
			{
				$first = 0;
				print "\tnpscanlist ";
			}
			else
			{
				print ", ";
			}
			print $word;
		}
		if (! $first)
		{
			print ";\n";
		}
		print "};\n";
	}

	print "nmodes ", $n-1, ";\n";

__END__
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

