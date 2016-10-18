all: dirs writer reader 
dirs:
	if [ ! -d "bin" ]; then mkdir "bin"; fi
writer:
	gcc -ansi src/writer.c -o bin/writer -Wall
reader:
	gcc -ansi src/reader.c -o bin/reader -Wall
