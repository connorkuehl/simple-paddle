LIBS       = -lm -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS     = -c -std=c++11 -Wall 
OBJS       = main.o Ball.o Paddle.o GameObject.o
EXECUTABLE = simplepaddle

CC         = g++

all: $(EXECUTABLE)

debug: CFLAGS += -g
debug: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) 
	$(CC) $(OBJS) $(LIBS) -o $(EXECUTABLE)

main.o: main.cpp
	$(CC) main.cpp $(CFLAGS)

Ball.o: Ball.cpp Ball.h
	$(CC) Ball.cpp $(CFLAGS)

Paddle.o: Paddle.cpp Paddle.h
	$(CC) Paddle.cpp $(CFLAGS)

GameObject.o: GameObject.cpp GameObject.h
	$(CC) GameObject.cpp $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(EXECUTABLE)