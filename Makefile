CXX = g++

CXXFLAGS = -Wall -Wno-uninitialized

BINARIES = fb

all: ${BINARIES}

clean:
	rm -f ${BINARIES} *.o \#*\#