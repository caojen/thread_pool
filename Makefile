CC = gcc
CFLAG = -lpthread -Iinclude

obj/job.o: src/job.c include/job.h
	$(CC) $(CFLAG) -o $@ -c $<

clean:
	rm -rf obj/*.o
