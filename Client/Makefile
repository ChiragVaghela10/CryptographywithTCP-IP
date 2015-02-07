#client side
SOURCES = sources/client.c sources/decryption.c sources/key_generate.c sources/my_modular_arith.c
HEADERS = headers/decryption.h headers/key_generate.h headers/my_modular_arith.h

#target: dependency_list
#<tab>	command_list

client: client.a(client.o) client.a(decryption.o) client.a(key_generate.o) client.a(my_modular_arith.o)
	cc -o client client.a -lm
	
client.a(client.o): sources/client.c headers/key_generate.h headers/decryption.h
	cc -c sources/client.c
	ar rv client.a client.o
	rm client.o

client.a(key_generate.o): sources/key_generate.c headers/key_generate.h headers/my_modular_arith.h
	cc -c sources/key_generate.c
	ar rv client.a key_generate.o
	rm key_generate.o

client.a(decryption.o): sources/decryption.c headers/decryption.h headers/my_modular_arith.h
	cc -c sources/decryption.c
	ar rv client.a decryption.o
	rm decryption.o

client.a(my_modular_arith.o): sources/my_modular_arith.c headers/my_modular_arith.h
	cc -c sources/my_modular_arith.c
	ar rv client.a my_modular_arith.o
	rm my_modular_arith.o
	
clean:
	rm *.o

tar:
	tar -cvf client.tar $(SOURCES) $(HEADERS) Makefile client.a
