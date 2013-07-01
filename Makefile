# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                                                                           #
#                            MetaBax - Makefile                             #
#                                                                           #
# This is a Makefile for Linux/UNIX-based systems which builds mbtv using   #
# the libmetabax library.  Note that as of writing this, libmetabax is      #
# linked statically, so no additional library compilation is required.      #
#                                                                           #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Copyright (c) 2013, Brandon "Breakthrough" Castellano.                    #
#                                                                           #
# libmetabax is licensed under the BSD 2-Clause License; see the included   #
# COPYRIGHT file, or visit http://github.com/Breakthrough/MetaBax.          #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #


all: libmetabax mbtv

libmetabax: ./libmetabax/MetaBax.o
mbtv:       ./mbtv/mbtv


./libmetabax/MetaBax.o:
	g++ -Wall -c -o ./libmetabax/MetaBax.o ./libmetabax/MetaBax.cpp 


./mbtv/mbtv:
	g++ `pkg-config --cflags sdl` -I ./libmetabax -c ./mbtv/main.cpp -o ./mbtv/main.o
	g++ ./mbtv/main.o ./libmetabax/MetaBax.o -o ./mbtv/mbtv `pkg-config --libs sdl`


clean:
	rm -f ./mbtv/mbtv
	rm -f ./libmetabax/MetaBax.o
