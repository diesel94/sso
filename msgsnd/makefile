all: bindir sender reader
bindir:
	if [ ! -d "bin" ]; then mkdir "bin"; fi
sender:
	gcc -ansi src/sender.c -o bin/sender -Wall
reader:
	gcc -ansi src/reader.c -o bin/reader -Wall
