## Process this file with automake to produce Makefile.in
PFLAGS=-module -avoid-version -no-undefined

if WALL_PLUGIN
libwall_la_LDFLAGS = $(PFLAGS)
libwall_la_LIBADD = @COMPIZ_LIBS@ @WALL_LIBS@
libwall_la_SOURCES = wall_options.c wall.c
endif

INCLUDES =                              \
	@COMPIZ_CFLAGS@                  \
	@WALL_CFLAGS@			\
	-DDATADIR='"$(datadir)"'          \
	-DLIBDIR='"$(libdir)"'              \
	-DLOCALEDIR="\"@datadir@/locale\""  \
	-DIMAGEDIR='"$(imagedir)"'          \
	-I$(top_srcdir)/include

moduledir = $(plugindir)

if WALL_PLUGIN
module_LTLIBRARIES = libwall.la
endif

CLEANFILES = *_options.c *_options.h

%_options.h: ../../metadata/%.xml
		$(BCOP_BIN) --header $@ $<

%_options.c: ../../metadata/%.xml %_options.h
		$(BCOP_BIN) --source $@ $<