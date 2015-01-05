TLPI_PATH = ..

INCLUDES = -I $(TLPI_PATH)/lib
LIBS = -static -ltlpi

PROG = copy.exe
CFILES = copy.c

CXXFLAGS = -g -Wall ${INCLUDES}  -L.. -L.

copy :
	$(CXX) $(CXXFLAGS) copy.c -o copy.exe $(LIBS)

seek_io :
	$(CXX) $(CXXFLAGS) seek_io.c -o seek_io.exe $(LIBS)

clean :
	rm -rf *.exe
