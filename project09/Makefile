#
# Macro definitions
#
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -fstack-protector-all -Werror 

all: public01.x public02.x public03.x public04.x public05.x public06.x \
     public07.x public08.x public09.x public10.x 

public01.x: simple-sserver.o public01.o simple-sserver.h \
     simple-sserver-datastructure.h safe-fork.h split.h
	$(CC) simple-sserver.o public01.o safe-fork.o split.o -o public01.x

public02.x: simple-sserver.o public02.o simple-sserver.h \
     simple-sserver-datastructure.h safe-fork.h split.h
	$(CC) simple-sserver.o public02.o safe-fork.o split.o -o public02.x

public03.x: simple-sserver.o public03.o simple-sserver.h \
     simple-sserver-datastructure.h memory-checking.o memory-checking.h \
     safe-fork.h split.h
	$(CC) simple-sserver.o public03.o safe-fork.o split.o memory-checking.o -o public03.x

public04.x: simple-sserver.o public04.o simple-sserver.h \
     simple-sserver-datastructure.h safe-fork.h split.h
	$(CC) simple-sserver.o public04.o safe-fork.o split.o -o public04.x

public05.x: simple-sserver.o public05.o simple-sserver.h \
     simple-sserver-datastructure.h safe-fork.h split.h
	$(CC) simple-sserver.o public05.o safe-fork.o split.o -o public05.x

public06.x: simple-sserver.o public06.o simple-sserver.h \
     simple-sserver-datastructure.h memory-checking.o memory-checking.h \
     safe-fork.h split.h 
	$(CC) simple-sserver.o public06.o safe-fork.o split.o memory-checking.o -o public06.x

public07.x: simple-sserver.o public07.o simple-sserver.h \
     simple-sserver-datastructure.h safe-fork.h split.h
	$(CC) simple-sserver.o public07.o safe-fork.o split.o -o public07.x

public08.x: simple-sserver.o public08.o simple-sserver.h \
     simple-sserver-datastructure.h safe-fork.h split.h
	$(CC) simple-sserver.o public08.o safe-fork.o split.o -o public08.x

public09.x: simple-sserver.o public09.o simple-sserver.h \
     simple-sserver-datastructure.h safe-fork.h split.h
	$(CC) simple-sserver.o public09.o safe-fork.o split.o -o public09.x

public10.x: simple-sserver.o public10.o simple-sserver.h \
     simple-sserver-datastructure.h safe-fork.h split.h
	$(CC) simple-sserver.o public10.o safe-fork.o split.o -o public10.x

student.x: simple-sserver.o student.o simple-sserver.h \
            simple-sserver-datastructure.h memory-checking.h memory-checking.o
	$(CC) simple-sserver.o student.o safe-fork.o split.o memory-checking.o -o student.x

simple-sserver.o: simple-sserver.c simple-sserver.h simple-sserver-datastructure.h \
     safe-fork.h split.h
	$(CC) $(CFLAGS) -c simple-sserver.c
 
public01.o: public01.c simple-sserver.h simple-sserver-datastructure.h \
            safe-fork.h split.h
	$(CC) $(CFLAGS) -c public01.c

public02.o: public02.c simple-sserver.h simple-sserver-datastructure.h \
            safe-fork.h split.h
	$(CC) $(CFLAGS) -c public02.c

public03.o: public03.c simple-sserver.h simple-sserver-datastructure.h \
            safe-fork.h split.h memory-checking.h
	$(CC) $(CFLAGS) -c public03.c
 
public04.o: public04.c simple-sserver.h simple-sserver-datastructure.h \
            safe-fork.h split.h
	$(CC) $(CFLAGS) -c public04.c
 
public05.o: public05.c simple-sserver.h simple-sserver-datastructure.h \
            safe-fork.h split.h
	$(CC) $(CFLAGS) -c public05.c
 
public06.o: public06.c simple-sserver.h simple-sserver-datastructure.h \
            safe-fork.h split.h memory-checking.h
	$(CC) $(CFLAGS) -c public06.c
 
public07.o: public07.c simple-sserver.h simple-sserver-datastructure.h \
            safe-fork.h split.h
	$(CC) $(CFLAGS) -c public07.c
 
public08.o: public08.c simple-sserver.h simple-sserver-datastructure.h \
            safe-fork.h split.h
	$(CC) $(CFLAGS) -c public08.c
 
public09.o: public09.c simple-sserver.h simple-sserver-datastructure.h \
            safe-fork.h split.h
	$(CC) $(CFLAGS) -c public09.c
 
public10.o: public10.c simple-sserver.h simple-sserver-datastructure.h \
            safe-fork.h split.h
	$(CC) $(CFLAGS) -c public10.c
 
student.o: student.c simple-sserver.h simple-sserver-datastructure.h \
            safe-fork.h split.h
	$(CC) $(CFLAGS) -c student.c


#
# 
#
clean:
	rm -f *.x simple-sserver.o public01.o public02.o public03.o public04.o \
        public05.o public06.o public07.o public08.o public09.o public10.o \
        student.o