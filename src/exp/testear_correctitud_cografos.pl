use strict;
use warnings;
use Data::Dumper;
use File::ReadBackwards;

#!/usr/bin/perl

	my $absolut_dir = "../test/cografos/";
	opendir(my $dh, $absolut_dir) || die "Can't opendir: $!";;
	my @files = readdir($dh);
	closedir($dh);

	my @heuristicas = qw/0 1 2/; 

	foreach my $file (@files)	{

		foreach my $h (@heuristicas) {

			my $tmp_path = "salida.out";
			my $tmp_fh;
			open ($tmp_fh, $tmp_path) || die "Cannot open temporary file: $+!\n";

			next if  !($file =~ "^caso.+");
			my $abs_file_path = $absolut_dir . $file;

			system("../problema5 $h < $abs_file_path > $tmp_path");
			
			my $m_sol_exacta  = File::ReadBackwards->new($abs_file_path)->readline;
			chomp $m_sol_exacta;

			my $first_row = <$tmp_fh>;

		  my ($n_sol, $m_sol) = split(' ', $first_row);

		  my $diff = $m_sol_exacta - $m_sol;
		  print $file, "\t", $h, "\t", $m_sol_exacta, "\t", $m_sol, "\t", $diff, "\n";

			close $tmp_fh;
		}

	}

1;


