### Makefile --- 

## Author: bean@beanmoon.local
## Version: $Id: Makefile,v 0.0 2015/05/16 03:19:36 bean Exp $
## Keywords: 
## X-URL: 

ifndef CC
	CC = gcc
endif

CFLAGS = -Wall -Wextra -Ibitarr -Lbitarr


mainv5: mainv5.cpp mybitarray.c mybitarray.h
	$(CXX)  -o mainv5 mainv5.cpp mybitarray.c

mainv6: mainv6.cpp mybitarray.c mybitarray.h
	$(CXX)  -o mainv6 mainv6.cpp mybitarray.c
mainv7: mainv7.cpp mybitarray.c mybitarray.h
	$(CXX)  -o mainv7 mainv7.cpp mybitarray.c

mainv7_1: mainv7_1.cpp mybitarray.c mybitarray.h
	$(CXX)  -g -o mainv7_1 mainv7_1.cpp mybitarray.c
mainv7_2: mainv7_2.cpp mybitarray.c mybitarray.h
	$(CXX)  -g -o mainv7_2 mainv7_2.cpp mybitarray.c


mainv5.1: mainv5.1.cpp mybitarray.c mybitarray.h
	$(CXX)  -o mainv5.1 mainv5.1.cpp mybitarray.c

test4: test4.cpp
	$(CXX) -o test4 test4.cpp -std=c++11

test7_1: test7_1.cpp
	$(CXX) -o test7_1 test7_1.cpp -std=c++0x -lboost_serialization

test7_2: test7_2.cpp
	$(CXX) -o test7_2 test7_2.cpp -std=c++0x -lboost_serialization

test11: test11.cpp
	$(CXX) -g -o test11 test11.cpp

mainv4: mainv4.cpp bitarr/libbitarr.a
	$(CXX) $(CFLAGS) -o mainv4 mainv4.cpp -lbitarr

bitarr/bit_array.o: bitarr/bit_array.c bitarr/bit_array.h bitarr/bit_macros.h

bitarr/libbitarr.a: bitarr/bit_array.o
	ar -csru bitarr/libbitarr.a bitarr/bit_array.o

bitarr/%.o: bitarr/%.c bitarr/%.h
	$(CC) $(CFLAGS) $(OBJFLAGS) -c $< -o $@

mybitarray: mybitarray.c
	$(CC) -o mybitarray mybitarray.c
test: test.c
	$(CC) -o test test.c

clean:
	rm -rf mainv4.o

.PHONY: clean test


### Makefile ends here
