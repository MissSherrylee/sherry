CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = cc3k
OBJECTS = cc3k.o player.o enemy.o potion.o gold.o dragon.o GameBoard.o textdisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
