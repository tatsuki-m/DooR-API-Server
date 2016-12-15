#!/bin/sh

g++ -c -fPIC ./src/shared_memory.cpp
g++ -c -fPIC ./src/shared_packet_information.cpp
g++ -c -fPIC ./src/shared_key.cpp
g++ -c -fPIC ./src/dpi.cpp

g++ -shared -o libdoorshm.so -fPIC shared_memory.o shared_packet_information.o shared_key.o dpi.o

rm -f shared_memory.o shared_packet_information.o shared_key.o dpi.o

