#pragma once

#include <QtCore/qglobal.h>

#ifndef QT_STATIC
# if defined(BCHATTEST_LIB)
#  define BCHATTEST_EXPORT Q_DECL_EXPORT
# else
#  define BCHATTEST_EXPORT Q_DECL_IMPORT
# endif
#else
# define BCHATTEST_EXPORT
#endif
