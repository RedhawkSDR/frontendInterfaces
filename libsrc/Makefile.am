###############################################################################
# C++ (via automake and libtool)
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = frontend.pc

## Place generated object files (.o) into the same directory as their source
## files, in order to avoid collisions when non-recursive make is used.
AUTOMAKE_OPTIONS = subdir-objects

## Additional flags to pass to aclocal when it is invoked automatically at
## make time. The ${ACLOCAL_FLAGS} variable is picked up from the environment
## to provide a way for the user to supply additional arguments.
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

lib_LTLIBRARIES = libfrontend-@FRONTEND_API_VERSION@.la
libfrontend_@FRONTEND_API_VERSION@_la_LDFLAGS = -version-info $(FRONTEND_SO_VERSION)

libfrontend_@FRONTEND_API_VERSION@_la_SOURCES = \
    cpp/fe_rfsource_port_impl.cpp \
    cpp/fe_tuner_port_impl.cpp \
    cpp/fe_tuner_device.cpp

## Define the list of public header files and their install location.
library_includedir = $(includedir)/frontend
library_include_HEADERS = \
	cpp/fe_gps_port_impl.h \
	cpp/fe_navdata_port_impl.h \
	cpp/fe_port_impl.h \
	cpp/fe_rfinfo_port_impl.h \
	cpp/fe_rfsource_port_impl.h \
	cpp/fe_tuner_device.h \
        cpp/fe_tuner_device.cpp \
	cpp/fe_tuner_port_impl.h \
	cpp/fe_tuner_struct_props.h \
	cpp/frontend.h \
	cpp/fe_types.h \
        cpp/fe_base.h

## The generated configuration header is installed in its own subdirectory of
## $(libdir).  The reason for this is that the configuration information put
## into this header file describes the target platform the installed library
## has been built for.  Thus the file must not be installed into a location
## intended for architecture-independent files, as defined by the Filesystem
## Hierarchy Standard (FHS).
## The nodist_ prefix instructs Automake to not generate rules for including
## the listed files in the distribution on 'make dist'.  Files that are listed
## in _HEADERS variables are normally included in the distribution, but the
## configuration header file is generated at configure time and should not be
## shipped with the source tarball.
#frontend_libincludedir = $(libdir)/frontend-$(FRONTEND_API_VERSION)/include

libfrontend_@FRONTEND_API_VERSION@_la_CXXFLAGS = -Wall -I./cpp -DLOGGING $(FRONTEND_INF_INCLUDES) $(BOOST_CPPFLAGS) $(OMNIORB_CFLAGS) $(OSSIE_CFLAGS)

###############################################################################
# Python

all-python: build-python

build-python:
	python setup.py build

install-python:
	test -n "$(DESTDIR)" && buildroot="--root=$(DESTDIR)"; \
	  python setup.py install $$buildroot --prefix=$(prefix) --install-purelib=$(prefix)/lib/python --force

clean-python:
	python setup.py clean --all

###############################################################################
# Java

if HAVE_JAVASUPPORT

JAVA_DIR := java
JAVA_SRCDIR := $(JAVA_DIR)/src
JAVA_BINDIR := $(JAVA_DIR)/bin
CLASSPATH := $(OSSIE_HOME)/lib/CFInterfaces.jar:$(OSSIE_HOME)/lib/ossie.jar:$(OSSIE_HOME)/lib/log4j-1.2.15.jar:$(OSSIE_HOME)/lib/BULKIOInterfaces.jar:$(top_builddir)/FRONTENDInterfaces.jar:
BINARY_JAR := $(JAVA_DIR)/frontend.jar
SOURCE_JAR := $(JAVA_DIR)/frontend.src.jar

JAVA_SRCS := \
InAnalogTunerPort.java \
OutAnalogTunerPort.java \
AnalogTunerDelegate.java \
InDigitalTunerPort.java \
OutDigitalTunerPort.java \
DigitalTunerDelegate.java \
InFrontendTunerPort.java \
OutFrontendTunerPort.java \
FrontendTunerDelegate.java \
InGPSPort.java \
OutGPSPort.java \
GPSDelegate.java \
InNavDataPort.java \
OutNavDataPort.java \
NavDataDelegate.java \
InRFInfoPort.java \
OutRFInfoPort.java \
RFInfoDelegate.java \
InRFSourcePort.java \
OutRFSourcePort.java \
RFSourceDelegate.java \
FrontendTunerStructProps.java \
FrontendTunerDevice.java
JAVA_SRCS_ABS := $(addprefix $(JAVA_SRCDIR)/frontend/, $(JAVA_SRCS))

javalibdir = $(prefix)/lib
javalib_DATA = $(BINARY_JAR) $(SOURCE_JAR)

# An intermediate file (used to get from *.java to a .jar). Intermediate
# indicates it's not important in and of itself - only necessary to get to the
# .jar
.INTERMEDIATE: $(JAVA_DIR)/java.files
$(JAVA_DIR)/java.files: $(JAVA_SRCS_ABS)
	echo $(JAVA_SRCS_ABS) > $@

# The jar depends on the file list, which depends on the .java files
$(BINARY_JAR): $(JAVA_DIR)/java.files $(JAVA_DIR)/META-INF/MANIFEST.MF $(top_builddir)/FRONTENDInterfaces.jar
	mkdir -p $(JAVA_BINDIR)
	$(JAVAC) -cp $(CLASSPATH) -target 1.6 -source 1.6 -d $(JAVA_BINDIR) @$(JAVA_DIR)/java.files
	$(JAR) cmf $(JAVA_DIR)/META-INF/MANIFEST.MF $(BINARY_JAR) -C $(JAVA_BINDIR) .

$(SOURCE_JAR): $(JAVA_DIR)/java.files $(JAVA_DIR)/META-INF/MANIFEST.MF.src
	$(JAR) cmf $(JAVA_DIR)/META-INF/MANIFEST.MF.src $(SOURCE_JAR) -C $(JAVA_SRCDIR) .

clean-java:
	rm -rf $(JAVA_BINDIR) $(BINARY_JAR) $(SOURCE_JAR)

else

clean-java:
	@echo "Java support is disabled"

endif

###############################################################################
# General
#

.PHONY: all-local all-python build-python install-python clean-python all-java install-java clean-java reallyclean reallyclean-java

all-local: all-python

install-exec-hook: install-python

clean-local: clean-python clean-java

reallyclean: distclean
	rm -f Makefile.in
