#
# Makefile för brute force-lösning
#

CCC	= g++ -std=c++11 

all: encrypt brute decrypt

brute: brute.cpp Key.o
	$(CCC) -O3 $(LFLAGS) -o brute brute.cpp Key.o

encrypt: encrypt.cpp Key.o
	$(CCC) $(LFLAGS) -o encrypt encrypt.cpp Key.o

decrypt: decrypt.cpp Key.o
	$(CCC) $(LFLAGS) -o decrypt decrypt.cpp Key.o


Key.o: Key.cpp Key.h
	$(CCC) -c Key.cpp

clean:
	@ \rm -rf *.o *.gch core

zap: clean
	@ \rm -f brute encrypt *~
