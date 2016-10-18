all: bindir writer reader mplayer-frontend
bindir:
	if [ ! -d "bin" ]; then mkdir "bin"; fi
writer:
	gcc -ansi src/writer.c -o bin/writer -Wall
reader:
	gcc -ansi src/reader.c -o bin/reader -Wall
mplayer-frontend:
	gcc -ansi src/mplayer-frontend.c -o bin/mplayer-frontend -Wall
