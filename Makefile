CC = gcc
CFLAG = -lpthread -Iinclude

all: main

obj/job.o: src/job.c include/job.h
	$(CC) $(CFLAG) -o $@ -c $<

obj/manager.o: src/manager.c include/manager.h
	$(CC) $(CFLAG) -o $@ -c $<

obj/worker.o: src/worker.c include/worker.h
	$(CC) $(CFLAG) -o $@ -c $<

obj/main.o: src/main.c
	$(CC) $(CFLAG) -o $@ -c $<

main: obj/job.o obj/manager.o obj/worker.o obj/main.o
	$(CC) $^ -o $@

clean:
	rm -rf obj/*.o
