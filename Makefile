cc = g++

all: codeTester

codeBasic.o: codeBasic.cpp codeBasic.h encodeBasic.h decodeBasic.h
	$(cc) -c codeBasic.cpp

codeTester.o: codeTester.cpp codeBasic.h
	$(cc) -c codeTester.cpp

codeTester: codeTester.o codeBasic.o
	$(cc) codeTester.o codeBasic.o -larmadillo -o codeTester

clean:
	rm -f *.o codeTester
