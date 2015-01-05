TLPI_PATH = ..

INCLUDES = -I $(TLPI_PATH)/lib 
LIBS = -static -ltlpi 

PROG = copy.exe
CFILES = copy.c

CXXFLAGS = -g -Wall -fPIC ${INCLUDES} -o $(PROG) -L.. -L.

all : 
	$(CXX) $(CXXFLAGS) $(CFILES) $(LIBS)

clean :
	rm -rf *.exe
