
#ifndef _BASICTYPES_H__
#define _BASICTYPES_H__

#ifdef COMPILER_MSVC
typedef __int64 int64;
#else
typedef long long int64;
#endif /* COMPILER_MSVC */
typedef long int32;
typedef short int16;
typedef char int8;

#ifdef COMPILER_MSVC
typedef unsigned __int64 uint64;
typedef __int64 int64;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
typedef unsigned long long uint64;
typedef long long int64;
typedef long long int64_t;
typedef unsigned long long uint64_t;
#endif /* COMPILER_MSVC */

typedef unsigned long uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned uint32_t;

#ifdef WIN32
typedef int socklen_t;
#endif

namespace _base {
  template<class T> inline T _min(T a, T b) { return (a > b) ? b : a; }
  template<class T> inline T _max(T a, T b) { return (a < b) ? b : a; }
}

#endif // _BASICTYPES_H__
