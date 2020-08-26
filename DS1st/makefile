# Define the symbols we might want to change:
CC=gcc
OBJECTS=ch6_Simulation.o ch6_QArray.o TStoixeiouOuras.o TController.o

# comment
# (note: the <tab> in the command line is necessary for make to work)
#target: dependency1 dependency2 ...
#<tab> command


my_progam: $(OBJECTS)
	$(CC) -o my_program $(OBJECTS) 

ch6_Simulation.o: ch6_Simulation.c
	$(CC) -c -o ch6_Simulation.o ch6_Simulation.c

ch6_QArray.o: ch6_QArray.c
	$(CC) -c -o ch6_QArray.o ch6_QArray.c

TStoixeiouOuras.o: TStoixeiouOuras.c
	$(CC) -c -o TStoixeiouOuras.o TStoixeiouOuras.c

TController.o: TController.c
	$(CC) -c -o TController.o TController.c

.PHONY: clean

clean:
	rm -f my_program my_program.o
	rm -f ch6_QArray.o
	rm -f ch6_Simulation.o
	rm -f TController.o
	rm -f TStoixeiouOuras.o

