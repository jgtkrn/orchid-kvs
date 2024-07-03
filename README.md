![orchid-kvs-logo](./doc/images/orchid-kvs-logo-nbg.png)

# Orchid KVS

Orchid KVS (Key-Value Store) is an experimental *key-value* in-memory database. The motivation behind Orchid KVS is to explore architecture and memory management behind data intensive softwares. Orchid KVS is developed under the vision of [STTUNK](https://www.linkedin.com/company/sttunk), a local group of technology enthusiasts dedicated to computing technologies exploration.

# Requirements

> - *Linux* x64
> - *GCC* Compiler with *C++20* or above
> - *libgtest-dev* library if you want to run unit test
> - any text editor
> - *make* if you dont want to build manually

# How to Run

## Clone This Repository

First clone this repository
> [clone orchid-kvs](https://github.com/jgtkrn/orchid-kvs.git) && cd orchid-kvs

## Build Project

Install using make, just simply run
> make

## Run Executable

There will be two output in *src* directory, *orchid* and *orchid-cli*.
*orchid* is used for database server, and *orchid-cli* is used for
command line to send command to server.

# How to Use

## Commands

There will be three kind of commands, with this following format:
> COMMAND KEY VALUE

COMMAND can be all *lowercase* or *uppercase*.

## Kind of Commands
### SET
SET command is used to store VALUE based on KEY specified.
> SET KEY VALUE

### GET
GET command is used to get VALUE based on KEY specified.
> GET KEY

### DEL
DEL command is used to delete VALUE based on KEY specified.
> DEL KEY

# Source Code Layout

Orchid KVS repository has this following directories:
`doc`       : storing all the documentation needs.
`include`   : storing all header file, including code documentation.
`module`    : storing all code implementation for the headers.
`src`       : main directory for the executable code, and module implementation.
`test`      : testing directory, you can find testing usage in `test/README.md` file.

# Components

Orchid KVS main part is hash table [`include/ds/hash_table.hh`] which is managed by event dispathcer [`include/orchid/event_dispatcher.hh`]. Orchid KVS using TCP as protocol [`include/orchid/socket.hh`] for simple data request management, combined with simple serialization [`include/orchid/marshall.hh`] which is explained in header file.

# Data Structures

## Chaining Hash Table

The main data structure on this database is hash table. There are several options can be used like the closest good choice the AVL tree data structure. The reason I use hash table over AVL tree is because I probably add temporary data backup feature in the future, so I need data structure that use less file IO. Hash table use less file IO than AVL tree since, since AVL tree has to do a lot of balancing operation which affect more file IO.

Hash table also have several issues like data collision problem. For this issue I choose chaining method for simple table management and better memory allocation for each data. Open addressing method has a lot of decision to make especially for probing method. Let’s say we have to take care of 18 data, and we have initial size 16 for each method. On chaining method we just need to attach to the available linked list inside the table till the table limit is reached before doing re hashing, but for open addressing we have to rehash immediately, and allocate more empty space that we don’t use yet. So, I think there will be a lot of wasted memory when we use open addressing method over chaining method, even probably data access will be faster when we use open addressing, since each data will have their own table.

## IO Model

### Event Loop

IO Multiplexing is one of method for IO management, especially of less memory footprint over multithreading. Poll is one example, the use loop over file descriptor to manage event so less thread used here. Poll also portable, because it is available over Linux OSes and BSDs. Downside of poll is they will loop over and over again depend on file descriptor count connected. So I think there will be a lot of operation waste, even we have more control over file descriptor data. For this situation epoll and kqueue are better choice, since they only execute based on file descriptor event triggered, so there will be operations if an event hit from specific request. Yet I have to manage both for different OS but still worth it.

# What's Next?

Yet this is not perfect example for in-memory database, but from this repository we can explore about how a simple in-memory database works. There will still be a lot we can explore and add as a feature for this project :D.