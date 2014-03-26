all:	 TestMessage TestRedirection

message.o: message.c message.h
	gcc -Wall -c message.c

alea.o: alea.h alea.c
	gcc -Wall -c alea.c

TestMessage: message.o alea.o TestMessage.c
	gcc TestMessage.c message.o alea.o -o  TestMessage

TestRedirection: TestRedirection.c
	gcc TestRedirection.c -o  TestRedirection

clean:	
	rm -f *.o *~
