## Process this file with automake to produce Makefile.in
PFLAGS=-module -avoid-version -no-undefined

if SCALEADDON_PLUGIN
libscaleaddon_la_LDFLAGS = $(PFLAGS)
libscaleaddon_la_LIBADD = @COMPIZ_LIBS@ @SCALE_LIBS@
nodist_libscaleaddon_la_SOURCES = scaleaddon_options.c scaleaddon_options.h
dist_libscaleaddon_la_SOURCES = scaleaddon.c
endif

BUILT_SOURCES = $(nodist_libscaleaddon_la_SOURCES)

INCLUDES =                              \
	-I$(top_srcdir)/include         \
	@COMPIZ_CFLAGS@                  \
	@SCALE_CFLAGS@                   \
	-DDATADIR='"$(compdatadir)"'        \
	-DLIBDIR='"$(libdir)"'              \
	-DLOCALEDIR="\"@datadir@/locale\""  \
	-DIMAGEDIR='"$(imagedir)"'          

moduledir = $(plugindir)

if SCALEADDON_PLUGIN
module_LTLIBRARIES = libscaleaddon.la
endif

CLEANFILES = *_options.c *_options.h

scaleaddon_options.h: ../../metadata/scaleaddon.xml.in
		$(BCOP_BIN) --header $@ $<

scaleaddon_options.c: ../../metadata/scaleaddon.xml.in scaleaddon_options.h
		$(BCOP_BIN) --source $@ $<
