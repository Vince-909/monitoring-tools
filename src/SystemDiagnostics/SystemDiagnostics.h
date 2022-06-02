#ifndef __SYSTEM__
#define __SYSTEM__

#include <windows.h>
#include <fstream>
#include <cstring>
#include <ctime>

using namespace std;

string base64_decode(string& encoded_string);

static const string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
};

#endif
