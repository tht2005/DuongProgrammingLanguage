Cfiles := ./src/main.c
Hfiles := ./include/debug.h ./include/defs.h ./include/lexer.h ./include/vector.h
Includes := -I./include/

main: $(Cfiles) $(Hfiles)
	cc $(Cfiles) -o main $(Includes)
