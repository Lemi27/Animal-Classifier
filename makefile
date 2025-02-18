miyuLemiA1: miyuLemiA1.o miyuLemiA1Main.o
	gcc miyuLemiA1.o miyuLemiA1Main.o -o miyuLemiA1 -lm

miyuLemiA1.o: miyuLemiA1.c givenA1.h helper.h
	gcc -Wall -std=c99 -c miyuLemiA1.c

miyuLemiA1Main.o: miyuLemiA1Main.c givenA1.h helper.h
	gcc -Wall -std=c99 -c miyuLemiA1Main.c

clean:
	rm *.o miyuLemiA1