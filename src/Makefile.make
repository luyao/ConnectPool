CC=~/bin/g++

INCLUDES=-I./include
LIB_PATH=-L. -L./lib

CPPFLAGS=-O0 -g -static -fPIC -finline-functions -Werror -Winline -pipe \
        -Wreturn-type -Wtrigraphs -Wformat -Wparentheses -Wpointer-arith -Wall \
        --param large-function-growth=10000 --param inline-unit-growth=1000 \
        -D_XOPEN_SOURE=500 -D_GNU_SOURCE -std=c++0x \
        `pkg-config --cflags libconfig++`

LDFLAGS=`pkg-config --libs libconfig++`

all: connect_pool

%.o: %.cpp 
	$(CC) $(CPPFLAGS) $(INCLUDES) -c $< -o $@ 

connect_pool: ./src/connect_pool.o test/test_connect_pool.o 
	$(CC) -o $@ $^ $(INCLUDES) $(LIB_PATH) $(LDFLAGS)

clean:
	rm -rf src/*.o test/*.o connect_pool

