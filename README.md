MetaBax
=======

**MetaBax** is an analog video signal emulation library (`libmetabax`), which can be integrated with an existing application to recreate the retro feel of analog video broadcasting. Also included is **MetaBaxTV** (`mbtv`), which demonstrates the effect of the MetaBax library on a particular video/image, and can be used to generate "presets" for the MetaBax library (by offering user control over the various parameters).  This application works very similar to Trevor Blackwell's `xanalogtv` screensaver, although using the cross-platform SDL library instead.

Note that the techniques used in this application do not follow any particular analog television broadcast specification, but *have* been heavily influenced by the very common NTSC/PAL formats (with some tasteful modifications along the way :).

Right now, images are parsed as SDL surfaces in software.  There are significant opportunities for speedups in the future (especially if certain parameters are fixed, which is often the case when combining MetaBax with an emulator as a "filter"), although the primary focus right now is on correct functionality and an appropriate analog/retro *feel*.