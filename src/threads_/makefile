CC= gcc
CFLAGS= -I -W -Wall -pedantic
LDFLAGS= -pthread
DEPS = threads.h
RUN = threads

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

threads: threads.o threads_utils.o
	gcc -o threads threads.o threads_utils.o $(LDFLAGS)

clean: 
	rm -f $(RUN) *.o s