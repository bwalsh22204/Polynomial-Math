CC = g++
CFLAGS = -Wall -g
SRCS = main.cc polynomial.cc
OBJS = ${SRCS:.cc=.o}

poly: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)

$(OBJS):
	$(CC) $(CFLAGS) -c $*.cc

depend:
	$(CC) -MM $(SRCS) > Makefile.dep

clean:
	rm -f $(OBJS) poly core

include Makefile.dep
