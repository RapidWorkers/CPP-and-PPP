#include "LZ77.h"

void LZ77::encode() {
    //read data first to fill the buffer
    inFile.read(slidingWnd+BLOCKSZ, BLOCKSZ);
    currLAWndSize = inFile.gcount();

    while(currLAWndSize){//loop till any data is in lookahead window
        int distance = 0;
        int length = 0;
        char lastByte = slidingWnd[BLOCKSZ];

        //check for any prefix exists in view window
        for(int i = BLOCKSZ - currViewSize; i < BLOCKSZ; i++){

        }

        //out to vector
        prefixDist.push_back(distance);
        prefixLen.push_back(length);
        encodedData.push_back(lastByte);

        //slide left the window
        this->slideWnd(1);

        //fill buffer
        if(!inFile.eof())
            inFile.read(slidingWnd+BLOCKSZ*2-1, 1);//read single byte
        else
            currLAWndSize--;

    }

    //flush data
    this->writeResult();

}

void LZ77::slideWnd(int amount) {

}

void LZ77::writeResult() {

}
