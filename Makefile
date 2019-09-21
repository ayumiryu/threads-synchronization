yi: yi.o
	gcc yi.o -o yi -pthread 
yi.o: yiOne.c
	gcc -c yiTwo.c -o yi.o -pthread 

.PHONY: clean
clean:
	rm -rf *.o
