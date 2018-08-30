CPP=g++
CPPFLAGS = -std=c++11 -lGL -lGLU -lglut -ljpeg -O2 -Wall -Wextra
OBJ = GL.o Texture.o Robby.o ArTur.o T800.o RobotB9.o TestMaze.o main.o

all: main

%.o: %.c
	$(CPP) -c -o $@ $< $(CPPFLAGS)

main: $(OBJ)
	$(CPP) -o $@ $^ $(CPPFLAGS)

clean:
	rm -f *.o main