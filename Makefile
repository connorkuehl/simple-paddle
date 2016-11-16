LIBS=-lm -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS=-c -std=c++11
OBJS=main.o Ball.o Paddle.o GameObject.o
EXECUTABLE=simplepaddle

all: $(EXECUTABLE)

debug: CFLAGS += -g
debug: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) 
	g++ $(OBJS) $(LIBS) -o $(EXECUTABLE)

main.o: main.cpp
	g++ main.cpp $(CFLAGS)

Ball.o: Ball.cpp Ball.h
	g++ Ball.cpp $(CFLAGS)

Paddle.o: Paddle.cpp Paddle.h
	g++ Paddle.cpp $(CFLAGS)

GameObject.o: GameObject.cpp GameObject.h
	g++ GameObject.cpp $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(EXECUTABLE)