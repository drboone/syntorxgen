#!/usr/bin/perl
# testmemold.pl, Boone, 07/23/02
# Generate an old style syntorgen input file for a "test ROM" style code plug
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

for ($i = 0; $i < 32; $i++)
{
	$a = int((144.250 + ($i * 0.75)) * 1000.0);
	print "MODE\n";
	printf("\t%06d %06d\n", $a, $a);
	print <<"EOF";
	0 NO 0.0 NO
	0 NO 0.0 NO
	0 0
	HIGH NONE NO 1 1 ANDOR FIXED
END
EOF
}

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
