# Define the symbols we might want to change:
CC=gcc
OBJECTS=Session.o main.o

# comment
# (note: the <tab> in the command line is necessary for make to work)
#target: dependency1 dependency2 ...
#<tab> command


my_progam: $(OBJECTS)
	$(CC) -o my_program $(OBJECTS) 

main.o: main.c
	$(CC) -c -o main.o main.c

Session.o: Session.c
	$(CC) -c -o Session.o Session.c

.PHONY: clean

clean:
	rm -f my_program my_program.o
	rm -f main.o
	rm -f Session.o
	
