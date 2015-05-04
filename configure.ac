#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([game-life-screensaver], [1.0.0], [medved_cool@mail.ru], [], [https://github.com/Cactus64k/game-life-screensaver])
# AM_INIT_AUTOMAKE
# AC_CONFIG_SRCDIR([src/])
AC_CONFIG_HEADERS([src/config.h])

# Checks for programs.
AC_PROG_CC_C99

# Checks for libraries.
PKG_CHECK_MODULES([GLIB],		[glib-2.0 >= 2.32.4])
PKG_CHECK_MODULES([GTK],		[gtk+-3.0 >= 3.4.2])

# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h stddef.h stdint.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([memset setlocale])

AC_DEFINE_UNQUOTED([PACKAGE_VERSION],		"${PACKAGE_VERSION}")
AC_DEFINE_UNQUOTED([PACKAGE_NAME],		"${PACKAGE_NAME}")


AC_CONFIG_FILES([makefile])
AC_OUTPUT
