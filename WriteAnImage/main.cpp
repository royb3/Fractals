
#include <iostream>
#include <fstream>
#include "bitmap_header.h"
#include "color.h"
#include "alignmentPadding.h"

using namespace std;
const int width = 2560, height = 1080;
BitmapHeader createHeader(int width, int height) {
    BitmapHeader header;
    header.width = width;
    header.height = height;
    header.imageDataSize = width * height * 4;
    header.fileSize = header.imageDataSize + header.imageDataOffset;
    header.reserved = 0;
    header.bitsPerPixel = 24;
    header.compression = 0;
    header.horizontalResolution = 0;
    header.verticalResolution = 0;
    header.numberOfColors = 0;
    header.numberOfImportantColors = 0;
    return header;
}
int main() {
    cout << "Hi!";
    ofstream outFile("C:\\Users\\Roy\\Desktop\\bla.bmp", ofstream::binary|ofstream::out);
    BitmapHeader header = createHeader(width, height);
    outFile.write((char *)&header, sizeof(BitmapHeader));
    Color bluePixel;
    bluePixel.blue = 255;
    bluePixel.green = 0;
    bluePixel.red = 0;
    AlignmentPadding padding;
//  bool writePadding = false;
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            outFile.write((char *)&bluePixel, sizeof(Color));
        }
/*
        if(writePadding) {
            outFile.write((char *)&padding, sizeof(AlignmentPadding));
        }
*/
    }

    outFile.close();
    return 0;
}
