Cfiles := ./src/main.c
Includes := -I./include/

main: $(Cfiles)
	cc $(Cfiles) -o main $(Includes)
