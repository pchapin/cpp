
CXX=g++
CXXOPTS=-Wall -std=c++11
LD=g++

all:	references const

references:		references.o
	$(LD) -o references references.o
	
const:			const.o
	$(LD) -o const const.o


references.o:	references.cpp
	$(CXX) -c $(CXXOPTS) references.cpp
	
const.o:		const.cpp
	$(CXX) -c $(CXXOPTS) const.cpp


clean:
	rm -f *.o *.exe references
	