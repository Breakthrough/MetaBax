
MetaBax
=======


About
-----

**MetaBax** is an analog video signal emulation library (`libmetabax`), which can be integrated with an existing application to recreate the retro feel of analog video broadcasting. Also included is **MetaBaxTV** (`mbtv`), which demonstrates the effect of the MetaBax library on a particular video/image, and can be used to generate "presets" for the MetaBax library (by offering user control over the various parameters).  This application works very similar to Trevor Blackwell's `xanalogtv` screensaver, although using the cross-platform SDL library instead.

Note that the techniques used in this application do not follow any particular analog television broadcast specification, but *have* been heavily influenced by the very common NTSC/PAL formats (with some tasteful modifications along the way :).

Right now, images are parsed as SDL surfaces in software.  There are significant opportunities for speedups in the future (especially if certain parameters are fixed, which is often the case when combining MetaBax with an emulator as a "filter"), although the primary focus right now is on correct functionality and an appropriate analog/retro *feel*.


Building & System Requirements
------------------------------

For Linux/UNIX-based systems, you should be able to use the included Makefile (just call `make` from the root directory of the source tree).  Build instructions for Windows are coming soon, but you can build the project similar to any other SDL application.

`libmetabax` has no explicit dependencies, and although the included reference implementation works with SDL surfaces (and thus requires SDL), any library allowing pixel-level data manipulation will suffice with some minor modifications.

`mbtv` requires SDL, and will require Python when fully completed.  There are also plans to extend `mbtv` with FFmpeg once basic functionality is implemented.


Using
-----

Coming soon!


License
-------

MetaBax is released under the BSD 2-Clause License, and uses the following terms:

> Metabax is Copyright (c) 2013, Brandon "Breakthrough" Castellano.
> All rights reserved.
> 
> Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
> 
> * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
> * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
> 
> THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
