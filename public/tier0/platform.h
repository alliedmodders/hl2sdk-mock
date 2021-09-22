// vim: set sts=4 ts=8 sw=4 tw=99 et:
#pragma once

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# define NOMINMAX
# include <Windows.h>
#endif

typedef char tchar;

#ifdef _WIN32
# define DLL_EXPORT extern "C" __declspec(dllexport)
#else
# define DLL_EXPORT extern "C"
# define MAX_PATH PATH_MAX
#endif

typedef intptr_t intp;
typedef uint8_t byte;
typedef uint32_t uint32;
typedef uint64_t uint64;

#define ALIGN_VALUE(size, bytes) (((size) + (bytes) - 1) & ~((bytes) - 1))

#if defined(_MSC_VER)
# define stackalloc(size) _alloca(ALIGN_VALUE((size), 16))
#else
# define stackalloc(size) alloca(ALIGN_VALUE((size), 16))
#endif

#define LittleDWord(val) val
#define abstract_class class

double Plat_FloatTime();
