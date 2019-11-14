CC = g++
CFLAGS = -g -c -Wall -std=c++11 -Og
OBJ = lab6.o ConditionCodes.o Memory.o RegisterFile.o Tools.o \
Loader.o

.C.o:
	$(CC) $(CFLAGS) $< -o $@

lab6: $(OBJ)

ConditionCodes.o: ConditionCodes.h Tools.h

Memory.o: Memory.h Tools.h

RegisterFile.o: RegisterFile.h Tools.h

Tools.o: Tools.h

lab6.o: Memory.h RegisterFile.h ConditionCodes.h Loader.h

Loader.o: Loader.h Memory.h

clean:
	rm $(OBJ) lab6

run:
	make clean
	make lab6
	./run.sh

