# Makefile to build class 'helloworld' for Pure Data.
# Needs Makefile.pdlibbuilder as helper makefile for platform-dependent build
# settings and rules.

# library name
lib.name = KNN

# input source file (class name == source file basename)
class.sources = KNN.c

# all extra files to be included in binary distribution of the library
# datafiles = README.md

# Location of PD package
PDINCLUDEDIR=/Applications/PureData.app/Contents/Resources/src

# include Makefile.pdlibbuilder from submodule directory 'pd-lib-builder'
PDLIBBUILDER_DIR=.
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder
