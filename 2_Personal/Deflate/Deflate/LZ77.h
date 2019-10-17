#ifndef DEFLATE_LZ77_H
#define DEFLATE_LZ77_H

#include <vector>
#include <memory>
#include <fstream>
#include <exception>
#include <array>

class LZ77{
    static const int BLOCKSZ = 65536;//64KiB
    using BYTE = char;
private:
    BYTE* slidingWnd;//window size is 2x of provided block size
    int currLAWndSize {0};
    int currViewSize {0};

    std::vector<int> prefixDist;
    std::vector<int> prefixLen;
    std::vector<BYTE> encodedData;
    std::ifstream inFile;

    void writeResult();
    void slideWnd(int amount);

public:
    explicit LZ77(const std::string &filepath): inFile{filepath, std::ios::binary}, slidingWnd{} {
        if(!inFile.is_open()) throw std::runtime_error("LZ77: Cannot open file %s" + filepath);
        slidingWnd = new BYTE[BLOCKSZ*2];
        if(slidingWnd == nullptr) throw std::runtime_error("LZ77: Memory allocation fail");
    };
    void encode();
};

#endif //DEFLATE_LZ77_H
