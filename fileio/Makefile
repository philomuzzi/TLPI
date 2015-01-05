CC = gcc

TLPI_PATH = ..

INCLUDES = -I $(TLPI_PATH)/lib 
CFLAGS = -g -Wall ${INCLUDES}

LIBS = -L.. -ltlpi
PROG = copy.exe


all : $(PROG)

$(PROG): copy.c
	$(CC) $(CFLAGS) copy.c -o $(PROG) $(LIBS)

clean :
	rm -rf *.exe
