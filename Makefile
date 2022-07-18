cc = g++

CFLAGS= -std=c++14

all: codeTester

codeBasic.o: codeBasic.cpp codeBasic.h
	$(cc) $(CFLAGS) -c codeBasic.cpp

hammingCode.o: hammingCode.cpp codeBasic.h hammingCode.h
	$(cc) $(CFLAGS) -c hammingCode.cpp

golayCode.o: golayCode.cpp codeBasic.h golayCode.h
	$(cc) $(CFLAGS) -c golayCode.cpp

codeTester.o: codeTester.cpp codeBasic.h golayCode.h hammingCode.h
	$(cc) $(CFLAGS) -c codeTester.cpp

codeTester: codeTester.o codeBasic.o golayCode.o hammingCode.o
	$(cc) codeTester.o codeBasic.o golayCode.o hammingCode.o -larmadillo -o codeTester

clean:
	rm -f *.o codeTester
