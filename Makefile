cc = g++

CFLAGS= -std=c++14

all: HammingCodeTester GolayCodeTester

codeBasic.o: codeBasic.cpp codeBasic.h
	$(cc) $(CFLAGS) -c codeBasic.cpp

noise.o: noise.cpp noise.h
	$(cc) $(CFLAGS) -c noise.cpp

hammingCode.o: hammingCode.cpp codeBasic.h hammingCode.h
	$(cc) $(CFLAGS) -c hammingCode.cpp

golayCode.o: golayCode.cpp codeBasic.h golayCode.h
	$(cc) $(CFLAGS) -c golayCode.cpp

codeTester.o: codeTester.cpp codeTester.h codeBasic.h noise.h
	$(cc) $(CFLAGS) -c codeTester.cpp

HammingCodeTester: codeTester.o codeBasic.o noise.o hammingCode.o
	$(cc) codeTester.o codeBasic.o noise.o hammingCode.o -larmadillo -o HammingCodeTester

GolayCodeTester: codeTester.o codeBasic.o noise.o golayCode.o
	$(cc) codeTester.o codeBasic.o noise.o golayCode.o -larmadillo -o GolayCodeTester

clean:
	rm -f *.o HammingCodeTester GolayCodeTester
