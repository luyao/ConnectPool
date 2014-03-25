#!/bin/sh
# Program:
# 		
# History:
# Author: luyao(yaolu1103@gmail.com)
# Date:  2014/03/19 14:17:38

PATH=/bin:/sbin:/usr/bin:~/bin:/usr/local/bin:/usr/local/sbin
export PATH

#compile
#libtool --mode=compile gcc -c compress.c
#
##link
#libtool --mode=link gcc -o libcompress.la compress.lo -rpath /tmp -lz
#
##install
#libtool --mode=install install -c libcompress.la /tmp
#
##finish
#libtool -n --mode=finish /tmp
#

case $1 in
clean)
        rm -rf aclocal.m4 \
                auto* \
                config.* \
                configure configure.scan \
                AUTHORS COPYING INSTALL NEWS ChangeLog \
                missing \
                depcomp \
                ltmain.sh \
                Makefile \
                install-sh
        find ./ -name "Makefile.in"|xargs rm
        ;;
build)
        #autoscan
        touch NEWS README ChangeLog AUTHORS

        `autoreconf -i -s`

        ./configure

        make
        ;;
esac


