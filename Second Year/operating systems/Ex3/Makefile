CC = gcc -std=c++11
LIBS = -lstdc++ -pthread
main: main.o Producer.o BoundedBuffer.o UnboundedBuffer.o
	$(CC) main.o Producer.o BoundedBuffer.o UnboundedBuffer.o -o ex3.out $(LIBS)

main.o: main.cpp Producer.h BoundedBuffer.h UnboundedBuffer.h
	$(CC) -c main.cpp
Producer.o: Producer.cpp Producer.h BoundedBuffer.h
	$(CC) -c Producer.cpp
BoundedBuffer.o: BoundedBuffer.cpp BoundedBuffer.h
	$(CC) -c BoundedBuffer.cpp
UnboundedBuffer.o: UnboundedBuffer.cpp UnboundedBuffer.h
	$(CC) -c UnboundedBuffer.cpp

clear:
	rm main.o Producer.o BoundedBuffer.o UnboundedBuffer.o