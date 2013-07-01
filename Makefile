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

all:
	g++ `pkg-config --cflags sdl` -I ./libmetabax ./mbtv/main.cpp -o ./mbtv/mbtv

clean:
	rm -f ./mbtv/mbtv
