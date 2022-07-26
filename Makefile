cc = g++

CFLAGS= -std=c++14

all: HammingCodeTester GolayCodeTester

codeBasic.o: codeBasic.cpp codeBasic.h
	$(cc) $(CFLAGS) -c codeBasic.cpp

noise.o: noise.cpp noise.h
	$(cc) $(CFLAGS) -c noise.cpp

md5.o: md5.cpp md5.h
	$(cc) $(CFLAGS) -c md5.cpp

hammingCode.o: hammingCode.cpp codeBasic.h hammingCode.h
	$(cc) $(CFLAGS) -c hammingCode.cpp

golayCode.o: golayCode.cpp codeBasic.h golayCode.h
	$(cc) $(CFLAGS) -c golayCode.cpp

codeTester.o: codeTester.cpp codeTester.h codeBasic.h noise.h md5.h
	$(cc) $(CFLAGS) -c codeTester.cpp

HammingCodeTester: codeTester.o codeBasic.o noise.o md5.o hammingCode.o
	$(cc) codeTester.o codeBasic.o noise.o md5.o hammingCode.o -larmadillo -o HammingCodeTester

GolayCodeTester: codeTester.o codeBasic.o noise.o md5.o golayCode.o
	$(cc) codeTester.o codeBasic.o noise.o md5.o golayCode.o -larmadillo -o GolayCodeTester

clean:
	rm -f *.o HammingCodeTester GolayCodeTester
