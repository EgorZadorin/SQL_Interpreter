# Makefile for Model_SQL_server project

ModelSQLserver: main.o libsock.a libinterpreter.a libtableint.a  
	g++ -fsanitize=address,undefined -std=c++11 -o ModelSQLserver main.o -L. -lsock -linterpreter -ltableint 

main.o: main.cpp
	g++ -fsanitize=address,undefined -std=c++11 -c -g main.cpp

libsock.a: sock.o
	ar cr libsock.a sock.o

libtableint.a: tableint.o
	ar cr libtableint.a tableint.o

libinterpreter.a: interpreter.o
	ar cr libinterpreter.a interpreter.o

sock.o: sock.cpp
	g++ -fsanitize=address,undefined -std=c++11 -c -g sock.cpp

interpreter.o: interpreter.cpp
	g++ -fsanitize=address,undefined -std=c++11 -c -g interpreter.cpp

tableint.o: tableint.cpp
	g++ -fsanitize=address,undefined -std=c++11 -c -g tableint.cpp

clean:
	rm -f *.o *.a *~ *.un~ ModelSQLserver
