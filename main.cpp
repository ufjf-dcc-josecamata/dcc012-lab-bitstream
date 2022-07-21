#include <iostream>
#include <fstream>

#include "bitstream.h"

int main()
{

    outPutBitStream outStream("test.bin");
    outStream.writeBit(1);
    outStream.writeBit(0);
    outStream.writeBit(0);
    outStream.writeBit(0);
    outStream.writeBit(1);
    outStream.writeBit(0);
    outStream.writeBit(1);
    outStream.writeBit(0);
    outStream.writeBit(1);
    outStream.writeBit(0);
    outStream.close();

    inPutBitStream inStream("test.bin");
    uint8_t bit = inStream.readBit();
    while(!inStream.eof())
    {
        if(bit)
        {
            cout << "1";
        }
        else
        {
            cout << "0";
        }
        bit = inStream.readBit();
    }
    cout << endl;
    inStream.close();
    return 0;
}