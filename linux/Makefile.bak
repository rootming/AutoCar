all:server client

server:server.o
	g++ server.o -g -o server -pthread

server.o:server.cpp data.h
	g++ server.cpp -c -o server.o -Wall -Werror -g -std=c++11 
client:client.o
	g++ client.o -g -o client -pthread

client.o:client.cpp data.h
	g++ client.cpp -c -o client.o -Wall -Werror -g -std=c++11 

clean:
	rm -f server client *.o
