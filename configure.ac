dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.68)
AC_INIT([khazad-min], [0.1.0]) #set project name and version
AC_PROG_CC
# C++ used for testing with cxxtest
AC_PROG_CXX

#AC_CANONICAL_SYSTEM

# Put configuration results here, so we can easily #include them:
AC_CONFIG_HEADERS([config.h])

# Put autotools auxiliary files in subdirectories to reduce clutter:
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

# library version as current:revision:age
# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
AC_SUBST([LIB_SO_VERSION], [1:0:0])

# Enable "automake" to simplify creating makefiles:
AM_INIT_AUTOMAKE([foreign subdir-objects -Wall -Werror -Wno-portability])
AM_SILENT_RULES([yes])
AC_CONFIG_FILES([Makefile
		khazad-min.pc])

#dnl this allows us specify individual linking flags for each target
AM_PROG_CC_C_O 

dnl Initialize Libtool
LT_INIT

dnl Check if Libtool is present
dnl Libtool is used for building share libraries 
AC_PROG_LIBTOOL

AC_ARG_WITH([cxxtest], AS_HELP_STRING([--with-cxxtest], [Build with cxxtest library]))
AS_IF([test "x$with_cxxtest" = "xyes"], [
    AC_DEFINE([WITH_CXXTEST], [1], [Enable cxxtest for testing])
	AC_LANG_PUSH([C++])
	AC_CHECK_HEADERS([cxxtest/TestSuite.h], [],
		[AC_MSG_ERROR(You need the cxxtest library.)])
	AC_LANG_POP([C++])
	AC_PATH_PROG([CXXTESTGEN], [cxxtestgen], [no])
	AS_IF([test "${CXXTESTGEN}" == "no"], [AC_MSG_ERROR([cxxtest compiler "cxxtestgen" not found.])])
])
AM_CONDITIONAL([WITH_CXXTEST], [test "x$with_cxxtest" = "xyes"])

AC_ARG_ENABLE([sbox-small],
    AS_HELP_STRING([--enable-sbox-small], [Enable small S-box implementation]))
AS_IF([test "x$enable_sbox_small" = "xyes"], [
    AC_DEFINE([ENABLE_SBOX_SMALL], [1], [Enable small S-box implementation])
])
AM_CONDITIONAL([ENABLE_SBOX_SMALL], [test "x$enable_sbox_small" = "xyes"])

AC_ARG_ENABLE([long-test],
    AS_HELP_STRING([--enable-long-test], [Enable long-duration unit tests]))
AS_IF([test "x$enable_long_test" = "xyes"], [
    AC_DEFINE([ENABLE_LONG_TEST], [1], [Enable long-duration unit tests])
], [
    AC_DEFINE([ENABLE_LONG_TEST], [0], [Enable long-duration unit tests])
])
AM_CONDITIONAL([ENABLE_LONG_TEST], [test "x$enable_long_test" = "xyes"])

AC_OUTPUT

