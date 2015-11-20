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

##Downloads

I'll try to keep the latest working build in the Gamecube folder. Please note this is a big work in progress and is not guaranteed to work.

Here's the link, just replace your current boot.dol file in the apps/wiisx folder (I'll get a better download going later on):

https://github.com/Mystro256/wiisxr/raw/master/Gamecube/WiiSX.dol

##Reporting Bugs

Feel free to report bugs, but if you can, please test pcsxr first, to eliminate redundant bugs. If it's not a bug in pcsxr, but a bug here, report it here if desired. I would hope this can be as aligned with pcsxr as possible, so any bugs in pcsxr will be inherited unfortunately. If it is a bug in pcsxr, feel free to report bugs with pcsxr... Please note that I am not affiliated with them, so mentioning me or wiisxr is unnecessary and unadvised to avoid confusion.

As well, I can't guarentee this project will be a success, unless I can get some help! So if you have any programming skill, feel free to fork me and check the Goals section!

##Goals

The aim of this project is to maintain, update and improve the wiisx code to comply with building with the latest devkitPro (PPC), website can be found here:
http://sourceforge.net/projects/devkitpro/files/devkitPPC/

Some Goals in mind:

- Fix build warnings and errors (see Gamecube/build.log for details, seems like it could be optimized better too)
- Remove Gamecube specific code and remake gui with libwiigui (easier to change, update and fix. Plus it's all draw with gx. Also this needs to be rebranded, as the wiisx logo and name does not belong to me)
- Update with code from pcsxr (Take as much as possible from pcsxr development... unfortunately the wii is limited and some fixes cannot be ported: http://pcsxr.codeplex.com)
- Improve plugins (perhaps replace them?)... e.g. cdrmooby28 has some optimization and possible heap issues. As well, maybe an opengl plugin can be ported to gx (with the help of something like gl2gx), and a sound plugin with the help of a SDL layer (or ported?).

Don't forget to fork me if you want to contribute! :)
I'm open to collaborators!

##How to Build

If don't have the build system setup yet, see "Build System Guide" first

For the Wii version, just cd into the Gamecube folder and run

```bash
make -f Makefile_Wii
```

or to build it for GameCube:

```bash
make -f Makefile_GC
```

##Build System Guide
    
I realize many people know how to build on devkitPro, but here's a guide for noobies:

1. Download devkitPro (PPC version for your system) from here: http://sourceforge.net/projects/devkitpro/files/devkitPPC/
If you're using Windows, it's suggested to use the auto installer instead and after installing it, skip to step 7 (note that the default devkitPro folder is C:\devkitPro):
http://sourceforge.net/projects/devkitpro/files/Automated%20Installer/

2. Extract the devkitPPC folder from the file you downloaded into a folder called devkitPro (your file system should look like this: devkitPro/devkitPPC/, make the devkitPro where ever you want, I used ~/devkitPro)

3. Download libfat-ogc: http://sourceforge.net/projects/devkitpro/files/libfat/

4. Download libogc: http://sourceforge.net/projects/devkitpro/files/libogc/

5. Make a folder called libogc in the devkitPro folder like so: devkitPro/libogc

6. Extract the include and lib folders from libogc and libfat-ogc into the libogc folder.

7. Download zlib from here: http://sourceforge.net/projects/devkitpro/files/portlibs/ppc/

8. Download libwupc: https://github.com/FIX94/libwupc

9. Make a portlibs folder in the devkitPro folder, then a ppc in the portlibs folder, like so: devkitPro/portlibs/ppc

10. Extract the include, lib and share folders from zlib and libwupc into the ppc folder.

11. On Linux or Mac OSX only, make sure you specify the environment variables, like so (I used ~/devkitPro for the location; replace this with what you used):

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
