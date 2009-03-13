#
# FILE             $Id$
#
# DESCRIPTION      Project makefile template.
#
# PROJECT          Shared memory STL allocator.
#
# AUTHOR           Michal Bukovsky <michal.bukovsky@firma.seznam.cz>
#
# LICENSE          see COPYING
#
# Copyright (C) Seznam.cz a.s. 2007
# All Rights Reserved
#
# HISTORY
#       2007-04-25 (bukovsky)
#                  First draft.
#

# warn on all
AM_CXXFLAGS = -Wall -g ${AM_CXXEXTRAFLAGS}

# path to includes
AM_CPPFLAGS = -I$(srcdir)../include

# build this library
lib_LTLIBRARIES = libshallocator.la
libshallocator_la_SOURCES = shallocator.cc
libshallocator_la_LDFLAGS = @VERSION_INFO@

# example programs
noinst_PROGRAMS = example
example_SOURCES = example.cc
example_LDADD = libshallocator.la

