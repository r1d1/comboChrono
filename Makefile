VERSION= b.0 
BINARY= comboChrono
SOURCE= ./src/
BUILDDIR= ./obj/
SRCE= $(wildcard *.cpp)
#OBJS= $(SRCE:%.cpp=%.o)
OBJS=main.o Chrono.o ChronoDuration.o
LIBS=-lsfml-system -lsfml-graphics -lsfml-network -lsfml-audio -lsfml-window
PATHTOSFML=/usr/local/SFML-2.2

all: $(OBJS) 
	g++ $^ -o $(BINARY)_$(VERSION) $(LIBS) #-L${PATHTOSFML}/lib 

#$(OBJS): src/$(SRCE)
#	g++ -c $^ 

# We should really improve this Makefile for generating objects :
main.o: main.cpp
	g++ -c main.cpp #-I${PATHTOSFML}/include

Chrono.o: Chrono.cpp Chrono.h
	g++ -c Chrono.cpp #-I${PATHTOSFML}/include

ChronoDuration.o: ChronoDuration.cpp ChronoDuration.h
	g++ -c ChronoDuration.cpp #-I${PATHTOSFML}/include

# Because listing each file is long, painful, non maintenable, and stupid !

clean :
	rm *.o
	rm -f $(BINARY)_$(VERSION)
