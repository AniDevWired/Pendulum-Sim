v1: src/v1.c 
	gcc -o bin/sim.o src/v1.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

v2: src/v2.c 
	gcc -o bin/sim.o src/v2.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 

test: src/test.c 
	gcc -o bin/test.o src/test.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 

run: 
	./bin/sim.o

testR: 
	./bin/test.o

clean: 
	rm -rf bin/sim.o