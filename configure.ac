#
# This file is protected by Copyright. Please refer to the COPYRIGHT file 
# distributed with this source distribution.
# 
# This file is part of REDHAWK core.
# 
# REDHAWK core is free software: you can redistribute it and/or modify it under 
# the terms of the GNU Lesser General Public License as published by the Free 
# Software Foundation, either version 3 of the License, or (at your option) any 
# later version.
# 
# REDHAWK core is distributed in the hope that it will be useful, but WITHOUT 
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
# details.
# 
# You should have received a copy of the GNU Lesser General Public License 
# along with this program.  If not, see http://www.gnu.org/licenses/.
#

AC_INIT(frontendInterfaces, 2.0.1)

AC_PREFIX_DEFAULT(${OSSIEHOME})

AM_INIT_AUTOMAKE(nostdinc)
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL

AM_PATH_PYTHON([2.3])

OSSIE_CHECK_OSSIE
OSSIE_OSSIEHOME_AS_PREFIX
OSSIE_PYTHON_INSTALL_SCHEME

AC_CORBA_ORB
AC_CHECK_PROG([IDL], [omniidl], [omniidl], [no])
if test "$IDL" = no; then
  AC_MSG_ERROR([cannot find omniidl program])
fi
AC_LANG_PUSH([C++])
PKG_CHECK_MODULES([OMNIORB], [omniORB4 >= 4.0.0])
PKG_CHECK_MODULES(OSSIE, ossie >= 1.7.0,,exit)

# If you depend on other IDL modules, such as CF or BULKIO add them here
PKG_CHECK_MODULES([BULKIO], [bulkioInterfaces >= 1.7])
AC_CHECK_PYMODULE(bulkio.bulkioInterfaces, [], [AC_MSG_ERROR([the python bulkio.bulkioInterfaces module is required])])

# Optionally include java support
AC_ARG_ENABLE([java], AS_HELP_STRING([--disable-java], [Disable framework java support]))

if test "x$enable_java" != "xno"; then
  AC_CHECK_PROG([IDLJ], [idlj], [idlj], [no])
  AC_CHECK_PROG([JAVAC], [javac], [javac], [no])
  AC_CHECK_PROG([JAR], [jar], [jar], [no])
  if test "$IDLJ" = no -o "$JAVAC" = no -o "$JAR" = no; then
    HAVE_JAVASUPPORT=no
    AC_MSG_WARN([Java support won't be built due to missing dependencies])
  else
    HAVE_JAVASUPPORT=yes
  fi
else
  HAVE_JAVASUPPORT=no
fi
AC_MSG_CHECKING([for framework java support])
AC_MSG_RESULT($HAVE_JAVASUPPORT)

AM_CONDITIONAL(HAVE_JAVASUPPORT, test $HAVE_JAVASUPPORT = yes)
# End optional java support

AC_CONFIG_FILES(Makefile)
AC_OUTPUT
