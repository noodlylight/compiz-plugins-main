## Process this file with automake to produce Makefile.in
SUBDIRS = metadata src po include data images

EXTRA_DIST =               \
    VERSION                \
    compiz-animation.pc.in \
    compiz-mousepoll.pc.in \
    compiz-text.pc.in

DISTCLEANFILES =     \
    po/stamp-it \
    po/.intltool-merge-cache

if TEXT_PLUGIN
textdata = compiz-text.pc
endif

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = $(textdata) compiz-animation.pc compiz-mousepoll.pc
