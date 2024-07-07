CC = g++
FLAGS = -std=c++20  -Wall -Wextra -I./include
TEST_FLAGS = -lgtest -lgtest_main -lpthread
ORCHID_DEPS = src/orchid.cc module/orchid/socket.o module/orchid/utils.o module/orchid/marshall.o module/orchid/event_dispatcher.o module/ds/linked_list.o module/ds/hash_map.o module/config/generator.o
ORCHID_CLI_DEPS = src/orchid-cli.cc module/orchid/socket.o module/orchid/marshall.o module/orchid/utils.o module/config/generator.o

BSD_DEPS = module/orchid/jam/kqueue.o

LINUX_DEPS = module/orhcid/jam/epoll.o

all: clean config module/orchid/socket.o module/orchid/event_dispatcher.o module/orchid/utils.o module/orchid/marshall.o module/orchid/jam/epoll.o module/ds/linked_list.o module/ds/hash_map.o module/config/generator.o src/linux/orchid src/linux/orchid-cli move

linux: clean config module/orchid/socket.o module/orchid/event_dispatcher.o module/orchid/utils.o module/orchid/marshall.o module/orchid/jam/epoll.o module/ds/linked_list.o module/ds/hash_map.o module/config/generator.o src/linux/orchid src/linux/orchid-cli move

bsd: clean config module/orchid/socket.o module/orchid/event_dispatcher.o module/orchid/utils.o module/orchid/marshall.o module/orchid/jam/kqueue.o module/ds/linked_list.o module/ds/hash_map.o module/config/generator.o src/bsd/orchid src/bsd/orchid-cli move

config:
	@if [ ! -f orchid.conf ]; then \
		cp -f module/config/orchid.conf orchid.conf; \
	else \
		echo "orchid.conf already exists"; \
	fi

orchid.conf: module/config/orchid.conf
	cp -f module/config/orchid.conf orchid.conf

src/linux/orchid:
	@if [ ! -f src/linux ]; then \
		mkdir -p src/linux; \
		$(CC) $(ORCHID_DEPS) $(LINUX_DEPS) -o src/linux/orchid $(FLAGS); \
	else \
		$(CC) $(ORCHID_DEPS) $(LINUX_DEPS) -o src/linux/orchid $(FLAGS); \
	fi

src/linux/orchid-cli:
	@if [ ! -f src/linux ]; then \
		mkdir -p src/linux; \
		$(CC) $(ORCHID_CLI_DEPS) $(LINUX_DEPS) -o src/linux/orchid-cli $(FLAGS); \
	else \
		$(CC) $(ORCHID_CLI_DEPS) $(LINUX_DEPS) -o src/linux/orchid-cli $(FLAGS); \
	fi

src/bsd/orchid:
	@if [ ! -f src/bsd ]; then \
		mkdir -p src/bsd; \
		$(CC) $(ORCHID_DEPS) $(BSD_DEPS) -o src/bsd/orchid $(FLAGS); \
	else \
		$(CC) $(ORCHID_DEPS) $(BSD_DEPS) -o src/bsd/orchid $(FLAGS); \
	fi

src/bsd/orchid-cli:
	@if [ ! -f src/bsd ]; then \
		mkdir -p src/bsd; \
		$(CC) $(ORCHID_CLI_DEPS) $(BSD_DEPS) -o src/bsd/orchid-cli $(FLAGS); \
	else \
		$(CC) $(ORCHID_CLI_DEPS) $(BSD_DEPS) -o src/bsd/orchid-cli $(FLAGS); \
	fi

module/orchid/socket.o:
	$(CC) -c module/orchid/socket.cc -o module/orchid/socket.o $(FLAGS)

module/orchid/event_dispatcher.o:
	$(CC) -c module/orchid/event_dispatcher.cc -o module/orchid/event_dispatcher.o $(FLAGS)

module/orchid/utils.o:
	$(CC) -c module/orchid/utils.cc -o module/orchid/utils.o $(FLAGS)

module/orchid/jam/epoll.o:
	$(CC) -c module/orchid/jam/epoll.cc -o module/orchid/jam/epoll.o $(FLAGS)

module/orchid/jam/kqueue.o:
	$(CC) -c module/orchid/jam/kqueue.cc -o module/orchid/jam/kqueue.o $(FLAGS)

module/orchid/marshall.o:
	$(CC) -c module/orchid/marshall.cc -o module/orchid/marshall.o $(FLAGS)

module/ds/linked_list.o:
	$(CC) -c module/ds/linked_list.cc -o module/ds/linked_list.o $(FLAGS)

module/ds/hash_map.o:
	$(CC) -c module/ds/hash_map.cc -o module/ds/hash_map.o $(FLAGS)

module/config/generator.o:
	$(CC) -c module/config/generator.cc -o module/config/generator.o $(FLAGS)

test/main_test:
	$(CC) test/main_test.cc test/orchid_socket_test.cc test/orchid_event_dispatcher_test.cc test/orchid_utils_test.cc test/orchid_marshall_test.cc test/ds_linked_list_test.cc test/ds_hash_map_test.cc test/config_generator_test.cc module/orchid/socket.cc module/orchid/event_dispatcher.cc module/orchid/utils.cc module/orchid/marshall.cc module/ds/linked_list.cc module/ds/hash_map.cc module/config/generator.cc -o test/main_test $(FLAGS) $(TEST_FLAGS)

test: clean test/main_test

move:
	@if [ -f src/linux/orchid ]; then \
		mv -f src/linux/orchid src/orchid; \
		mv -f src/linux/orchid-cli src/orchid-cli; \
		rm -rf src/linux; \
	else \
		mv -f src/bsd/orchid src/orchid; \
		mv -f src/bsd/orchid-cli src/orchid-cli; \
		rm -rf src/bsd; \
	fi

clean:
	rm -rf **/**/*.o **/*.o *.o src/orchid src/orchid-cli src/linux src/bsd test/*_test
