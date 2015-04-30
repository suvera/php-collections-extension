dnl $Id$
dnl config.m4 for extension collections

PHP_ARG_ENABLE(collections, whether to enable collections support,
[  --enable-collections           Enable collections support])

if test "$PHP_COLLECTIONS" != "no"; then

  PHP_REQUIRE_CXX()
  PHP_SUBST(IPV6_CPP_SHARED_LIBADD)
  PHP_ADD_LIBRARY(stdc++, 1, IPV6_CPP_SHARED_LIBADD)

  dnl -Wall -g -std=c++0x   (or)   -Wall -g -std=c++11
  PHP_NEW_EXTENSION(collections, collections.cpp, $ext_shared,, "-std=c++0x", "yes")(collections, collections.cpp, $ext_shared)
fi
