 CC= g++
 CFLAGS= -Wall -Wextra -g
 DEPS = $(wildcard *.h)
 export ${MKLROOT} = ~/intel/mkl/
# %.out: %.cpp $(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAGS)
all: 	
		rm -rf *o lenet.out
		python preprocess.py > image.txt
		g++ -pthread -o lenet.out lenet1.cpp -DMKL_ILP64 -m64 -I${MKLROOT}/include  -Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_ilp64.a ${MKLROOT}/lib/intel64/libmkl_sequential.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -lpthread -lm -ldl ; ./lenet.out




# main.o: main.cpp
# 	g++ -c main.cpp
clean: 
		rm -rf *o lenet.out
