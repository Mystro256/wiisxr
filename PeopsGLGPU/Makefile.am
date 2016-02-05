AM_CPPFLAGS = -DPIXMAPDIR=\"${datadir}/pixmaps/\" \
	-DLOCALE_DIR=\"${datadir}/locale/\" \
	-DDATADIR=\"${datadir}/psemu/\" \
	$(GTK3_CFLAGS) \
	-I../../libpcsxcore -I../../include

bindir = @libdir@/games/psemu/
libdir = @libdir@/games/psemu/

lib_LTLIBRARIES = libpeopsxgl.la

libpeopsxgl_la_SOURCES = cfg.c draw.c fps.c gpu.c key.c menu.c \
	prim.c soft.c texture.c gte_accuracy.c
libpeopsxgl_la_LDFLAGS = -module -avoid-version
libpeopsxgl_la_LIBADD = -lX11 -lXxf86vm -lGL -lm

bin_PROGRAMS = cfgpeopsxgl
cfgpeopsxgl_SOURCES = gpucfg/main.c
cfgpeopsxgl_LDADD = $(GTK3_LIBS)

glade_DATA = gpucfg/peopsxgl.ui
gladedir = $(datadir)/psemu/
EXTRA_DIST = $(glade_DATA)
