 CC= g++
 CFLAGS= -Wall -Wextra -g
 DEPS = $(wildcard *.h)
 export ${MKLROOT} = ~/intel/mkl/
# %.out: %.cpp $(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAGS)
all: 	
		rm -rf *o main.out
		g++ main.cpp -std=c++11 -o main.out -DMKL_ILP64 -m64 -I${MKLROOT}/include  -Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_ilp64.a ${MKLROOT}/lib/intel64/libmkl_sequential.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -lpthread -lm -ldl



# main.o: main.cpp
# 	g++ -c main.cpp
clean: 
		rm -rf *o main.out
