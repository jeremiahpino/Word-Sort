all: fw

fw: fw.o readWord.o hashTable.o
	gcc -o fw -ansi -Wall -pedantic -g fw.o readWord.o hashTable.o
fw.o: fw.c
	gcc -ansi -Wall -pedantic -g -c fw.c
readWord.o: readWord.c readWord.h
	gcc -ansi -Wall -pedantic -g -c readWord.c
hashTable.o: hashTable.c hashTable.h
	gcc -ansi -Wall -pedantic -g -c hashTable.c
clean:
	rm *.o fw
handin:
	scp fw.c readWord.c hashTable.c readWord.h hashTable.h Makefile README jpino01@unix1.csc.calpoly.edu:./assign2
test:
	./fw -n 10 INPUT
