# these two lines specify make "variables"
# makes it easy to change to a different compiler and
# change the flags.  Notice the variables are "expanded"
# with a $ sign.
CC=gcc 
FLAGS=-Wall

ll_tst: llist.o ll_tst.c
	$(CC) $(FLAGS) ll_tst.c llist.o -o ll_tst

llist.o: list.h llist.c
	$(CC) $(FLAGS) -c llist.c

clean:
	rm -f *.o ll_tst

