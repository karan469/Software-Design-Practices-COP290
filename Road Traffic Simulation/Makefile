 CC= g++
 CFLAGS= -Wall -Wextra -g
 DEPS = $(wildcard *.h)
# %.out: %.cpp $(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAGS)
all: 	
		rm -rf gl
		g++ -o gl gl.cpp -lGL -lGLU -lglut



run: 
		./gl
# main.o: main.cpp
# 	g++ -c main.cpp
clean: 
		rm -rf gl