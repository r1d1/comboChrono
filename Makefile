VERSION= b.0 
BINARY= comboChrono
SOURCE= ./src/
BUILDDIR= ./obj/
SRCE= $(wildcard *.cpp)
#OBJS= $(SRCE:%.cpp=%.o)
OBJS=main.o Chrono.o ChronoDuration.o
LIBS=-lsfml-system -lsfml-graphics -lsfml-network -lsfml-audio -lsfml-window

all: $(OBJS) 
	g++ $^ -o $(BINARY)_$(VERSION) $(LIBS)

#$(OBJS): src/$(SRCE)
#	g++ -c $^ 

# We should really improve this Makefile for generating objects :
main.o: main.cpp
	g++ -c main.cpp

Chrono.o: Chrono.cpp Chrono.h
	g++ -c Chrono.cpp

ChronoDuration.o: ChronoDuration.cpp ChronoDuration.h
	g++ -c ChronoDuration.cpp 

# Because listing each file is long, painful, non maintenable, and stupid !

clean :
	rm -f $(BINARY)_$(VERSION)
