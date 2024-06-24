CC=g++
FLAGS= -Wall -Wextra -I./include

all: clean modules/orchid/socket.o src/orchid

src/orchid: modules/orchid/socket.o
	$(CC) src/orchid.cc modules/orchid/socket.o -o src/orchid $(FLAGS)

modules/orchid/socket.o:
	$(CC) -c modules/orchid/socket.cc -o modules/orchid/socket.o $(FLAGS)

clean:
	rm -rf **/**/*.o **/*.o *.o src/orchid src/orchid-cli
