all: bindir client server
bindir:
	if [ ! -d "bin" ]; then mkdir "bin"; fi
client:
	gcc src/client.c -o bin/client -Wall -lpthread
server:
	gcc src/server.c -o bin/server -Wall -lpthread
