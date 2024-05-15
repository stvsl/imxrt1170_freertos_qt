#ifndef __CORE_DEF_H__
#define __CORE_DEF_H__

#include <platforminterface/allocator.h>
#include <string>

typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;
typedef __SIZE_TYPE__ size_t;

typedef std::basic_string<char, std::char_traits<char>,
                          Qul::PlatformInterface::Allocator<char>>
    String;

#endif // __CORE_DEF_H__