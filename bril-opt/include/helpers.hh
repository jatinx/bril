#pragma once

#include "nlohmann/json.hpp"
#include <cstdarg>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

using json = nlohmann::json;

static void print_(const char *format, ...) {
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  std::cout << std::endl;
  va_end(args);
}

static void errorAndCrash(const char *msg) {
  print_("%s", msg);
  exit(1);
}

#if (defined(DEBUG))
#define printDebug(format, ...) print_(format, __VA_ARGS__)
#else
#define printDebug(format, ...)
#endif