CC=g++
FLAGS= -std=c++20  -Wall -Wextra -I./include
TEST_FLAGS = -lgtest -lgtest_main -lpthread

all: clean module/orchid/socket.o module/em/em.o src/orchid src/orchid-cli

src/orchid: module/orchid/socket.o
	$(CC) src/orchid.cc module/orchid/socket.o module/em/em.o -o src/orchid $(FLAGS)

src/orchid-cli: module/orchid/socket.o
	$(CC) src/orchid-cli.cc module/orchid/socket.o module/em/em.o -o src/orchid-cli $(FLAGS)

module/orchid/socket.o:
	$(CC) -c module/orchid/socket.cc -o module/orchid/socket.o $(FLAGS)

module/em/em.o:
	$(CC) -c module/em/em.cc -o module/em/em.o $(FLAGS)

test/main_test:
	$(CC) test/main_test.cc test/orchid_socket_test.cc -o test/main_test $(FLAGS) $(TEST_FLAGS)

test: clean test/main_test

clean:
	rm -rf **/**/*.o **/*.o *.o src/orchid src/orchid-cli test/*_test
