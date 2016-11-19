all: bindir philosophers
bindir:
	if [ ! -d "bin" ]; then mkdir "bin"; fi
philosophers:
	gcc src/philosophers.c -o bin/philosophers -Wall -lpthread
