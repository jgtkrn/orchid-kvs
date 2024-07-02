CC = g++
FLAGS = -std=c++20  -Wall -Wextra -I./include
TEST_FLAGS = -lgtest -lgtest_main -lpthread
ORCHID_DEPS = src/orchid.cc module/orchid/socket.o module/orchid/utils.o module/orchid/marshall.o module/orchid/event_dispatcher.o module/ds/linked_list.o module/ds/hash_map.o
ORCHID_CLI_DEPS = src/orchid-cli.cc module/orchid/socket.o module/orchid/marshall.o module/orchid/utils.o

all: clean config module/orchid/socket.o module/orchid/event_dispatcher.o module/orchid/utils.o module/orchid/marshall.o module/ds/linked_list.o module/ds/hash_map.o src/orchid src/orchid-cli

config: module/config/orchid.conf
	cp -f module/config/orchid.conf orchid.conf
	
src/orchid: module/orchid/socket.o
	$(CC) $(ORCHID_DEPS) -o src/orchid $(FLAGS)

src/orchid-cli: module/orchid/socket.o
	$(CC) $(ORCHID_CLI_DEPS) -o src/orchid-cli $(FLAGS)

module/orchid/socket.o:
	$(CC) -c module/orchid/socket.cc -o module/orchid/socket.o $(FLAGS)

module/orchid/event_dispatcher.o:
	$(CC) -c module/orchid/event_dispatcher.cc -o module/orchid/event_dispatcher.o $(FLAGS)

module/orchid/utils.o:
	$(CC) -c module/orchid/utils.cc -o module/orchid/utils.o $(FLAGS)

module/orchid/marshall.o:
	$(CC) -c module/orchid/marshall.cc -o module/orchid/marshall.o $(FLAGS)

module/ds/linked_list.o:
	$(CC) -c module/ds/linked_list.cc -o module/ds/linked_list.o $(FLAGS)

module/ds/hash_map.o:
	$(CC) -c module/ds/hash_map.cc -o module/ds/hash_map.o $(FLAGS)

test/main_test:
	$(CC) test/main_test.cc test/orchid_socket_test.cc test/orchid_event_dispatcher_test.cc test/orchid_utils_test.cc test/orchid_marshall_test.cc test/ds_linked_list_test.cc test/ds_hash_map_test.cc module/orchid/socket.cc module/orchid/event_dispatcher.cc module/orchid/utils.cc module/orchid/marshall.cc module/ds/linked_list.cc module/ds/hash_map.cc -o test/main_test $(FLAGS) $(TEST_FLAGS)

test: clean test/main_test

clean:
	rm -rf **/**/*.o **/*.o *.o src/orchid src/orchid-cli test/*_test
