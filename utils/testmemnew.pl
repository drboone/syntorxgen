#!/usr/bin/perl

print "nmodes 32;\n";
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

