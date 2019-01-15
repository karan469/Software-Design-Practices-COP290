CC=g++
CFLAGS=-I.
DEPS = $(wildcard *.h)
SRCS = $(wildcard *.cpp)
OBJ = $(SRCS:%.cpp=%.o)

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY:clean
clean:
	rm -rvf *.o