# $Id: Makefile 2 2008-06-10 15:32:27Z bill.cotton $
#-----------------------------------------------------------------------
#;  Copyright (C) 2002-2017
#;  Associated Universities, Inc. Washington DC, USA.
#;
#;  This program is free software; you can redistribute it and/or
#;  modify it under the terms of the GNU General Public License as
#;  published by the Free Software Foundation; either version 2 of
#;  the License, or (at your option) any later version.
#;
#;  This program is distributed in the hope that it will be useful,
#;  but WITHOUT ANY WARRANTY; without even the implied warranty of
#;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#;  GNU General Public License for more details.
#;
#
#;  You should have received a copy of the GNU General Public
#;  License along with this program; if not, write to the Free
#;  Software Foundation, Inc., 675 Massachusetts Ave, Cambridge,
#;  MA 02139, USA.
#;
#;  Correspondence concerning this software should be addressed as follows:
#;         Internet email: bcotton@nrao.edu
#;         Postal address: W. D. Cotton
#;                         National Radio Astronomy Observatory
#;                         520 Edgemont Road
#;                         Charlottesville, VA 22903-2475 USA
#-----------------------------------------------------------------------
#    Makefile to build library
#    Obit: Merx mollis mortibus nuper
#
#   Expects RANLIB to be set by either environment variable  or Make argument
#     RANLIB is the library "ranomizer".
#
#------------------------------------------------------------------------
# targets to build
TARGETS =  libObitSD.a
SHTARGETS = libObitSD.so

# list of object modules
OBJECTS := $(wildcard *.o)

all:  $(TARGETS)
share: $(SHTARGETS)

#  build Obit library
libObitSD.a: ${OBJECTS}
	ar rv libObitSD.a ${OBJECTS}
	${RANLIB} libObitSD.a

#  build shared Obit library, put in dependencies library
libObitSD.so: ${OBJECTS}
	gcc -shared -o libObitSD.so  ${OBJECTS}
	cp libObitSD.so ../../../deps/lib

clean:
	rm -f $(TARGETS)


