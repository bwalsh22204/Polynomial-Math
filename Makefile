CC = g++
CFLAGS = -Wall -g
SRCS = main.cc polynomial.cc
OBJS = ${SRCS:.cc=.o}

a.out: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)

$(OBJS):
	$(CC) $(CFLAGS) -c $*.cc

depend:
	$(CC) -MM $(SRCS) > Makefile.dep

clean:
	rm -f $(OBJS) a.out core

include Makefile.dep
