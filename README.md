![WiiSXR logo](./logo.png)

Fork of wiisx, a GameCube/Wii/Wii U PSX emulator.

The starting point for this code base will be daxtsu's libwupc mod of wiisx, which is in turn based off of Matguitarist's "USB mod5"

Please see the following link for details:

http://www.gc-forever.com/forums/viewtopic.php?t=2524

WiiSX is GNU GPL and the source can be found here:

https://code.google.com/p/pcsxgc/downloads/list

LibWupc is also GPL, which can be found here:

https://github.com/FIX94/libwupc

Please contact me if you have licensing concerns. I will try to make this as GPL2+/3+ compliant as possible.

## Downloads

All downloads can be found here:

https://github.com/Mystro256/wiisxr/releases

## Reporting Bugs

Feel free to report bugs, but if you can, please test pcsxr first, to eliminate redundant bugs. If it's not a bug in pcsxr, but a bug here, report it here if desired. I would hope this can be as aligned with pcsxr as possible, so any bugs in pcsxr will be inherited unfortunately. If it is a bug in pcsxr, feel free to report bugs with pcsxr... Please note that I am not affiliated with them, so mentioning me or wiisxr is unnecessary and unadvised to avoid confusion.

As well, I can't guarentee this project will be a success, unless I can get some help! So if you have any programming skill, feel free to fork me and check the Goals section!

## Goals

The aim of this project is to maintain, update and improve the wiisx code to comply with building with the latest devkitPro (PPC), website can be found here:
http://sourceforge.net/projects/devkitpro/files/devkitPPC/

Some Goals in mind:

- Fix gcc build warnings (see build.log for details). Not sure how much the punned pointers will effect optimization, but no warnings is always better than any at all IMHO.
- Update with any code from pcsxr (Take as much as possible from pcsxr development... unfortunately the wii is limited and some things cannot be ported: http://pcsxr.codeplex.com). As well, most the focus of their development is for x86, leaving not much to take for PPC/Wii. Any fixes can be ported to PCSXR if desired or applicable as well.
- Improve plugins (perhaps replace them?)... e.g. cdrmooby28 has some optimization and possible memory issues. As well, maybe an opengl plugin can be ported to gx (with the help of something like gl2gx, WIP see gxrender branch), and a sound plugin with the help of a SDL layer (or ported?).
- A new GUI with libwiigui, and in turn remove all the Gamecube specific code, to simplify things. It will be easier to change, update and fix. Plus it doesn't involve having unmaintainable assembly code. It seems like everything breaks in the GUI when I change minor things, so this maybe a necessity... it maybe somewhere in the assembly that's messing things up.
- More controller support, i.e. gamecube, hid, etc... the wii u pro controller is supported but very buggy.

Don't forget to fork me if you want to contribute! :)
I'm open to collaborators!
Unfortunately its a lot of work and I'm limited on time as is, so any help is appreciated.

## How to Build

If don't have the build system setup yet, see "Build System Guide" first

For the Wii version, just cd into the wiisxr folder and run

```bash
make Wii
```

or to build it for GameCube:

```bash
make GC
```

If you're going to do some development, I would suggest always making a clean build and regenerating build.log.
To do this, just call the make command like so and it'll do the rest for you:

```bash
make
```

To make a zip file to redistribute:

```bash
make dist
```

## Build System Guide
    
I realize many people know how to build on devkitPro, but here's a guide for noobies:

1. Download devkitPro (PPC version for your system) from here: http://sourceforge.net/projects/devkitpro/files/devkitPPC/
If you're using Windows, it's suggested to use the auto installer instead. After installing it, skip to step 7 (note that the default devkitPro folder is C:\devkitPro):
http://sourceforge.net/projects/devkitpro/files/Automated%20Installer/

2. Extract the devkitPPC folder from the file you downloaded into a folder called **devkitPro** (your file system should look like this: **devkitPro/devkitPPC/**, make the **devkitPro** folder where ever you want, I used ~/devkitPro)

3. Download libogc: http://sourceforge.net/projects/devkitpro/files/libogc/

4. Make a folder called libogc in the **devkitPro** folder like so: **devkitPro/libogc**

5. Extract the libogc include and lib folders into the **devkitPro/libogc** folder.

6. Download libfatmod: https://github.com/Mystro256/libfatmod/releases

7. Extract the libfatmod include and lib folders into the **devkitPro/libogc** folder.

9. Download zlib from here: http://sourceforge.net/projects/devkitpro/files/portlibs/ppc/

10. Download libwupc: https://github.com/FIX94/libwupc/archive/master.zip

11. Download libwiidrc: https://github.com/FIX94/libwiidrc/releases

12. Make a portlibs folder in the devkitPro folder, then a ppc in the portlibs folder, like so: **devkitPro/portlibs/ppc**

13. Extract the include, lib and share folders from zlib, libwupc, and libwiidrc into the **devkitPro/portlibs/ppc** folder.

14. On Linux or Mac OSX only, make sure you specify the environment variables, like so (I used ~/devkitPro for the location; replace this with what you used):

```bash
export DEVKITPRO=$HOME/devkitPro
export DEVKITPPC=$DEVKITPRO/devkitPPC
export PATH=$PATH:$DEVKITPPC/bin
```

and if you want to add the manpage path too:

```bash
export MANPATH=$MANPATH:$DEVKITPPC/share/man
```

You can add this to your ~/.bashrc so you don't have to change them every time you open a new terminal, but be careful, as this can interfere with other build systems.
