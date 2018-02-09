.SUFFIXES : .c .o 

CC     = gcc 
OBJS   = prtfmt.o util.o mini_.o 
SRCS   = $(OBJS:.o=.c)
TARGET = miniprintf
BASE   = ${shell pwd}
INCLUDE= -I${BASE}/include

CFLAGS= -c -g -Wall 

.c.o: 
	$(CC) $(INCLUDE) $(CFLAGS) $<

.PHONY: all
all: clean install

.PHONY: install
install: $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

.PHONY: clean
clean:
	rm -f ${OBJS} ${TARGET}

