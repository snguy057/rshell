CC=g++
CC_FLAGS=-Wall -Werror -ansi -pedantic
PARAMS=main.o Command.o AND.o OR.o SemiColon.o

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

clean:
	rm -rf bin
