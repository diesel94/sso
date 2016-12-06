all: bindir bank
bindir:
	if [ ! -d "bin" ]; then mkdir "bin"; fi
bank:
	gcc src/bank.c -o bin/bank -Wall -lpthread
