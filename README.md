    
MetaBax
=======


About
-----

**MetaBax** is an analog video signal emulation library (`libmetabax`), which can be integrated with an existing application to recreate the retro feel of analog video broadcasting. Also included is **MetaBaxTV** (`mbtv`), which demonstrates the effect of the MetaBax library on a particular video/image, and can be used to generate "presets" for the MetaBax library (by offering user control over the various parameters).  This application works very similar to Trevor Blackwell's `xanalogtv` screensaver, although using the cross-platform SDL library instead.

Note that the techniques used in this application do not follow any particular analog television broadcast specification, but *have* been heavily influenced by the very common NTSC/PAL formats (with some tasteful modifications along the way :).    

Right now, images are parsed as SDL surfaces in software.  There are significant opportunities for speedups in the future (especially if certain parameters are fixed, which is often the case when combining MetaBax with an emulator as a "filter"), although the primary focus right now is on correct functionality and an appropriate analog/retro *feel*.


Downloading
-----------

Currently, `mbtv` and `libmetabax` are in a pre-alpha state (read: under heavy development and not recommended for use at the moment).  When it is considered good enough for alpha usage/testing, I will remove the previous message, and one can follow the building instructions provided below.

When `mbtv` is in a state considered good enough for general use and testing, I will provide binaries (compiled on VS2010) for Windows users.  Linux/UNIX-based systems will find compiling from source rather easy given the few and well-known dependencies.


Building & System Requirements
------------------------------

Build instructions for Windows are coming soon (I hope to provide a Visual Studio solution), but you can build the project similar to any other SDL application (and it would require the same level of user configuration anyways).  The dependencies for Windows are the same as Linux.

For Linux/UNIX-based systems, you should be able to use the included Makefile (just call `make` from the root directory of the source tree), once all the dependencies are available.

`mbtv` requires `SDL` and `libmetabax`, and will require Python when fully completed.  For package-based distributions, you can get all the current dependencies by simply downloading the development library package (e.g. `libsdl1.2-dev` with `apt` on Ubuntu).

`libmetabax` has no explicit dependencies, and although the included reference implementations were made in mind to works with SDL surface formats; any library allowing pixel-level data access will work with `libmetabax` with little modification (none if the pixels are stored in the same provided pixel formats).


Using
-----

Coming soon!


License
-------

MetaBax is released under the BSD 2-Clause License, and uses the following terms:

> MetaBax is Copyright (c) 2013, Brandon "Breakthrough" Castellano.
> All rights reserved.
> 
> Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
> 
> * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
> * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
> 
> THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
