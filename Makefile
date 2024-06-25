CC=g++
FLAGS= -Wall -Wextra -I./include

all: clean module/orchid/socket.o module/em/em.o src/orchid

src/orchid: module/orchid/socket.o
	$(CC) src/orchid.cc module/orchid/socket.o module/em/em.o -o src/orchid $(FLAGS)

module/orchid/socket.o:
	$(CC) -c module/orchid/socket.cc -o module/orchid/socket.o $(FLAGS)

module/em/em.o:
	$(CC) -c module/em/em.cc -o module/em/em.o $(FLAGS)

clean:
	rm -rf **/**/*.o **/*.o *.o src/orchid src/orchid-cli
