TLPI_PATH = ..

INCLUDES = -I $(TLPI_PATH)/lib
LIBS = -static -ltlpi
CXXFLAGS = -g -Wall ${INCLUDES}  -L.. -L.

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%,$(SRCS))

.PHONY: all clean

all: $(OBJS)

%:%.c
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)

clean :
	rm -rf $(OBJS)
