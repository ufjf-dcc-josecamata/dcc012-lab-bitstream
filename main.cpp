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
    while(!inStream.eof())
    {
        cout <<  inStream.readBit();
    }
    cout << endl;
    inStream.close();
    return 0;
}
