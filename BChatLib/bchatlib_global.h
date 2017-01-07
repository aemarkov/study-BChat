#pragma once

#include <QtCore/qglobal.h>

#ifndef QT_STATIC
# if defined(BCHATLIB_LIB)
#  define BCHATLIB_EXPORT Q_DECL_EXPORT
# else
#  define BCHATLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define BCHATLIB_EXPORT
#endif
