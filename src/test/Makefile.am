bin_PROGRAMS = test_connect_pool
AM_CPPFLAGS=-I../include -I../connect_pool \
			`pkg-config --cflags libconfig++` \
			`pkg-config --libs libconfig++` \
			-O0 -g -static -fPIC -finline-functions -Werror -Winline -pipe \
			-Wreturn-type -Wtrigraphs -Wformat -Wparentheses -Wpointer-arith -Wall \
			--param large-function-growth=10000 --param inline-unit-growth=1000 \
			-D_XOPEN_SOURE=500 -D_GNU_SOURCE -std=c++0x


test_connect_pool_SOURCES = test_connect_pool.cpp ../connect_pool/connect_pool.cpp
