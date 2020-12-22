
#ifndef _BYTEORDER_H__
#define _BYTEORDER_H__

#include "basictypes.h"

#ifdef POSIX
extern "C" {
#include <arpa/inet.h>
}
#endif

#ifdef WIN32
#include <winsock2.h>
#endif

namespace _base {

inline uint16 HostToNetwork16(uint16 n) {
  return htons(n);
}

inline uint32 HostToNetwork32(uint32 n) {
  return htonl(n);
}

inline uint16 NetworkToHost16(uint16 n) {
  return ntohs(n);
}

inline uint32 NetworkToHost32(uint32 n) {
  return ntohl(n);
}

} // namespace _base

#endif //_BYTEORDER_H__
