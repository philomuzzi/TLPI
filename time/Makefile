TLPI_PATH = ..

INCLUDES = -I $(TLPI_PATH)/lib
LIBS = -static -ltlpi
CXXFLAGS = -fpermissive -g -Wall ${INCLUDES}  -L.. -L.

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.exe,$(SRCS))

.PHONY: all clean

all: $(OBJS)

%.exe:%.c
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)

clean :
	rm -rf $(OBJS)
