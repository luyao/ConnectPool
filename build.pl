#!/usr/bin/perl
# Program:
# 		
# History:
# Author: luyao(yaolu1103@gmail.com)
# Date:  2014/03/27 17:53:31

use strict;

sub clean($){
    return if (@_ != 1);
    open(FILE, shift) || die"cant open $!\n";
    my %file_dict;
    while (<FILE>) {
       chomp;
       $file_dict{$_} = 1;
    }
    close FILE;

    my @files = `ls`;
    foreach(@files){
        chomp;
        if (exists($file_dict{$_})) {
            print "Find $_\n";
        }else{
            system "rm -rf $_";
        }
    }
}

sub build{
    system "touch NEWS ChangeLog";
    system "autoreconf --install";
    system "./configure";
    system "make";
}

my $command = shift || die "build.pl build | clean\n";

if ($command eq "build") {
    build();
}else{
    clean("file_list");
}


#vim: set expandtab ts=256 sw=4 sts=4 tw=100 noet:
