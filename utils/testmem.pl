#!/usr/bin/perl

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
