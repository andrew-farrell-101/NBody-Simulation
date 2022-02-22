CC = g++
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS = -g -Wall -Werror -pedantic --std=c++14
PROG = Nbody

all: $(PROG)

$(PROG): main.o Universe.h Universe.cpp CelestialBody.cpp CelestialBody.h
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

# PhotoMagic.o: PhotoMagic.cpp 
# 	$(CC) $(CFLAGS) -c $< 

# FibLFSR.o: FibLFSR.cpp
# 	$(CC) $(CFLAGS) -c $< 
	
clean:
	rm *.o $(PROG)

