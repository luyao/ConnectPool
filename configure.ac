#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])

AM_INIT_AUTOMAKE([-Wall]) 
# 这是在 Autoconf 中使用 Libtool 唯一必须的宏
AC_PROG_LIBTOOL

AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX(${HOME}/bin/g++)
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB

# Checks for libraries.
PKG_CHECK_MODULES([LIBCONFIGXX], [libconfig++ >= 1.4],,
                  AC_MSG_ERROR([libconfig++ 1.4 or newer not found.])
                  )
# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/connect_pool/Makefile
                 src/utility/Makefile
                 src/test/Makefile])
AC_OUTPUT
