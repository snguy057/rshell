CC=g++
CC_FLAGS=-Wall -Werror -ansi -pedantic -g
PARAMS=main.o Command.o AND.o OR.o SemiColon.o Paren.o Left.o Right.o Dright.o Pipe.o

all: $(PARAMS)
	mkdir -p ./bin
	$(CC) $(CC_FLAGS) $(PARAMS) -o ./bin/rshell
	rm *o

main.o: src/main.cpp
	$(CC) $(CC_FLAGS) src/main.cpp -c

Command.o: src/Command.cpp
	$(CC) $(CC_FLAGS) src/Command.cpp -c

AND.o: src/AND.cpp
	$(CC) $(CC_FLAGS) src/AND.cpp -c

OR.o: src/OR.cpp
	$(CC) $(CC_FLAGS) src/OR.cpp -c

SemiColon.o: src/SemiColon.cpp
	$(CC) $(CC_FLAGS) src/SemiColon.cpp -c

Paren.o: src/Paren.cpp
	$(CC) $(CC_FLAGS) src/Paren.cpp -c

Left.o: src/Left.cpp
	$(CC) $(CC_FLAGS) src/Left.cpp -c

Right.o: src/Right.cpp
	$(CC) $(CC_FLAGS) src/Right.cpp -c

Dright.o: src/Dright.cpp
	$(CC) $(CC_FLAGS) src/Dright.cpp -c

Pipe.o: src/Pipe.cpp
	$(CC) $(CC_FLAGS) src/Pipe.cpp -c


clean:
	rm -rf bin
