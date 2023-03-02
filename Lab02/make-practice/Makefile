main: main.o fun2.o fun1.o ./lib/libdy.so
	gcc -o main ./src/main.o ./src/fun1.o ./src/fun2.o -L ./lib -ldy -I ./include

main.o: ./src/main.c 
	gcc -c ./src/main.c -I ./include -o ./src/main.o
fun1.o:./src/fun1.c ./include/fun1.h
	gcc -c ./src/fun1.c -o ./src/fun1.o -I ./include
fun2.o:./src/fun2.c ./include/fun2.h
	gcc -c ./src/fun2.c -o ./src/fun2.o -I ./include

clean:
	rm main
	rm ./src/main.o
	rm ./src/fun1.o
	rm ./src/fun2.o
