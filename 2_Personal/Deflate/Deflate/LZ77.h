#ifndef DEFLATE_LZ77_H
#define DEFLATE_LZ77_H

#include <vector>
#include <memory>
#include <fstream>
#include <exception>

class LZ77{
    static const int BLOCKSZ = 65536;
    using BYTE = unsigned char;
private:
  BYTE inStream[BLOCKSZ];


public:
};

#endif //DEFLATE_LZ77_H
