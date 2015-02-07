#server side
SOURCES = sources/server.c sources/encryption.c
HEADERS = headers/encryption.h

#target: dependency_list
#<tab>	command_list

server: server.a(server.o) server.a(encryption.o)
	cc -o server server.a -lm

server.a(server.o): sources/server.c headers/encryption.h
	cc -c sources/server.c
	ar rv server.a server.o
	rm server.o

server.a(encryption.o): sources/encryption.c headers/encryption.h
	cc -c sources/encryption.c
	ar rv server.a encryption.o
	rm encryption.o
#note:encryption.c(dependency file) not needed to be described in dependency list coz dependency file and target(encryption.o) have same name

clean:
	rm *.o

tar:
	tar -cvf server.tar $(SOURCES) $(HEADERS) Makefile server.a
