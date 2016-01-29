
#include <iostream>
#include <fstream>
#include "bitmap_header.h"

using namespace std;
const int width = 800, height = 600;

int main() {
    cout << "Hi!";
    ofstream outFile("C:\\Users\\wimbu\\Desktop\\bla.bmp", ofstream::out|ofstream::binary);
    BitmapHeader header;
    header.width = width;
    header.height = height;
    header.fileSize = (width * height * 3) + 54;
    outFile.write((char *)&header, sizeof(BitmapHeader));
    outFile.close();
    return 0;
}
