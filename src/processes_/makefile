CC= gcc
CFLAGS= -I -W -Wall -pedantic
DEPS = processes.h
RUN = processes

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

processes: processes.o processes_utils.o
	gcc -o processes processes.o processes_utils.o

clean: 
	rm -f $(RUN) *.o s