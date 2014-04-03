bin_PROGRAMS = test_double_buffered test_connect_pool
AM_CPPFLAGS=-I../include -I../connect_pool -I../utility\
			-O0 -g -static -fPIC -finline-functions -Werror -Winline -pipe \
			-Wreturn-type -Wtrigraphs -Wformat -Wparentheses -Wpointer-arith -Wall \
			--param large-function-growth=10000 --param inline-unit-growth=1000 \
			-D_XOPEN_SOURE=500 -D_GNU_SOURCE -std=c++0x \
			-D_GLIBCXX_USE_NANOSLEEP \
			`pkg-config --cflags libconfig++`

test_connect_pool_LDFLAGS= `pkg-config --libs libconfig++`
test_connect_pool_LDADD = -L../connect_pool -lconnect_pool  -L../utility/ -lutility
test_connect_pool_SOURCES = test_connect_pool.cpp 

test_double_buffered_LDFLAGS= `pkg-config --libs libconfig++`
test_double_buffered_LDADD = -L../utility/ -lutility -lpthread
test_double_buffer_SOURCES= test_double_buffer.cpp

