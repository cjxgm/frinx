
#ifndef __KE_UTIL_H__
#define __KE_UTIL_H__

#include <stdlib.h>

#define NEW(TYPE)					malloc(sizeof(TYPE))
#define NEW_EMPTY(TYPE)				calloc(sizeof(TYPE), 1)

#define CREATE(TYPE, VAR)			TYPE * VAR = NEW(TYPE)
#define CREATE_EMPTY(TYPE, VAR)		TYPE * VAR = NEW_EMPTY(TYPE)

#endif

