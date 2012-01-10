CC = g++
CFLAGS = -g -Wall
SRCS = main.cc polynomial.cc
OBJS = $(SOURCES:.cpp=.o)
EXEC = poly

all: $(SRCS) $(EXEC)
	
$(EXEC): $(OBJS) 
	$(CC) $(OBJS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
