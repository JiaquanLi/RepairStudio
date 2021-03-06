
#ifndef _BYTEBUFFER_H__
#define _BYTEBUFFER_H__

#include <string>
#include "basictypes.h"

namespace _base {

class ByteBuffer {
public:
  ByteBuffer();
  ByteBuffer(const char* bytes, size_t len);
  ByteBuffer(const char* bytes, size_t len, bool copy);
  ByteBuffer(const char* bytes); // uses strlen
  ~ByteBuffer();

  const char* Data() const { return bytes_ + start_; }
  size_t Length() { return end_ - start_; }
  size_t Capacity() { return size_ - start_; }

  bool ReadUInt8(uint8& val);
  bool ReadUInt16(uint16& val);
  bool ReadUInt32(uint32& val);
  bool ReadString(std::string& val, size_t len); // append to val
  bool ReadBytes(char* val, size_t len);

  void WriteUInt8(uint8 val);
  void WriteUInt16(uint16 val);
  void WriteUInt32(uint32 val);
  void WriteString(const std::string& val);
  void WriteBytes(const char* val, size_t len);

  void Resize(size_t size);
  void Shift(size_t size);

private:
  char* bytes_;
  size_t size_;
  size_t start_;
  size_t end_;
  bool copy_;
};

} // namespace _base

#endif //_BYTEBUFFER_H__
