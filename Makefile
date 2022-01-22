UNAME := $(shell uname -s)
CC = g++
OBJ = main.o #pathfinder.o
LDFLAGS = -lGL -lGLU -lglut

# Mac OS
ifeq ($(UNAME), Darwin)
	LDFLAGS = -framework OpenGL -framework glut
endif

main : $(OBJ)
	$(CC) -o main $(OBJ) $(LDFLAGS)

main.o : main.cpp main.h #pathfinder.h
	$(CC) -c -g main.cpp

#pathfinder.o : pathfinder.cpp pathfinder.h main.h
#	$(CC) -c -g pathfinder.cpp

clean :
	rm $(OBJ)
