bin_PROGRAMS = test_connect_pool
AM_CPPFLAGS=-I../include -I../connect_pool -I../utility\
			`pkg-config --cflags libconfig++` \
			-O0 -g -static -fPIC -finline-functions -Werror -Winline -pipe \
			-Wreturn-type -Wtrigraphs -Wformat -Wparentheses -Wpointer-arith -Wall \
			--param large-function-growth=10000 --param inline-unit-growth=1000 \
			-D_XOPEN_SOURE=500 -D_GNU_SOURCE -std=c++0x
test_connect_pool_LDFLAGS= `pkg-config --libs libconfig++`
test_connect_pool_LDADD = -L../connect_pool -lconnect_pool  -L../utility/ -lutility

test_connect_pool_SOURCES = test_connect_pool.cpp 
