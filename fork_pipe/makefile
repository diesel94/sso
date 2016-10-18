all: dirs pipe_overflow minishell
dirs:
	if [ ! -d "bin" ]; then mkdir "bin"; fi
pipe_overflow:
	gcc -ansi src/pipe_overflow.c -o bin/pipe_overflow -Wall
	
minishell:
	gcc -ansi src/minishell.c -o bin/minishell -Wall
	
