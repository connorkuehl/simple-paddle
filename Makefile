LIBS       = -lm -lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS   = -std=c++11 -Wall 
OBJS       = main.o Ball.o Paddle.o GameObject.o
EXECUTABLE = simplepaddle

CXX        = g++

all: $(EXECUTABLE)

debug: CFLAGS += -g
debug: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) 
	$(CXX) $(OBJS) $(LIBS) -o $(EXECUTABLE)

main.o:       main.cpp
Ball.o:       Ball.cpp Ball.h
Paddle.o:     Paddle.cpp Paddle.h
GameObject.o: GameObject.cpp GameObject.h

.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(EXECUTABLE)