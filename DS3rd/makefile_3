# Define the symbols we might want to change:
CC=gcc
OBJECTS=ch8_AVLpointer.o ch8_BSTpointer.o Evretirio.o TSDDA.o TSEvr.o  main.o

# comment
# (note: the <tab> in the command line is necessary for make to work)
#target: dependency1 dependency2 ...
#<tab> command


my_progam: $(OBJECTS)
	$(CC) -o my_program $(OBJECTS)

main.o: main.c
	$(CC) -c -o main.o main.c

TSDDA.o: TSDDA.c
	$(CC) -c -o TSDDA.o TSDDA.c

TSEvr.o: TSEvr.c
	$(CC) -c -o TSEvr.o TSEvr.c

Evretirio.o: Evretirio.c
	$(CC) -c -o Evretirio.o Evretirio.c

ch8_BSTpointer.o: ch8_BSTpointer.c
	$(CC) -c -o ch8_BSTpointer.o ch8_BSTpointer.c

ch8_AVLpointer.o: ch8_AVLpointer.c
	$(CC) -c -o ch8_AVLpointer.o ch8_AVLpointer.c

.PHONY: clean

clean:
	rm -f my_program my_program.o
	rm -f main.o
	rm -f Evretirio.o
	rm -f ch8_AVLpointer.o
	rm -f ch8_BSTpointer.o
	rm -f TSDDA.o
	rm -f TSEvr.o


