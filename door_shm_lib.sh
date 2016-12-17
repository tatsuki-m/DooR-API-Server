#!/bin/sh

# create object file
g++ -c -fPIC ./src/shared_memory/shared_memory.cpp
g++ -c -fPIC ./src/shared_memory/shared_packet_information.cpp
g++ -c -fPIC ./src/shared_memory/shared_key.cpp
g++ -c -fPIC ./src/shared_memory/dpi.cpp

# create shared library
g++ -shared -o libdoorshm.so -fPIC shared_memory.o shared_packet_information.o shared_key.o dpi.o

# delete needless shared library
rm -f shared_memory.o shared_packet_information.o shared_key.o dpi.o

 

