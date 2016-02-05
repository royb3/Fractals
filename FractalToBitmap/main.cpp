#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include "bitmap_header.h"
#include "color.h"
#include "alignmentPadding.h"

using namespace std;
int width, height;
const int depth = 128;
Color *colors[128];
Color blackColor;
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

void createColors() {
    for(int i = 0; i < 32; i++) {
        Color *color = new Color();
        color->red = 8*i;
        color->green = 128-4*i;
        color->blue = 255-8*i;
        colors[i] = color;
    }

    for(int i = 0; i < 32; i++) {
        Color *color = new Color();
        color->red = 255;
        color->green = 8*i;
        color->blue = 0;
        colors[32 + i] = color;
    }

    for(int i = 0; i < 32; i++) {
        Color *color = new Color();
        color->red = 128-4*i;
        color->green = 255;
        color->blue = 255-8*i;
        colors[64 + i] = color;
    }

    for(int i = 0; i < 32; i++) {
        Color *color = new Color();
        color->red = 0;
        color->green = 255-4*i;
        color->blue = 8*i;
        colors[96+i] = color;
    }
    blackColor.red = 0;
    blackColor.blue = 0;
    blackColor.green = 0;
}
int main(int argc, char** argv) {
    createColors();
    char *widthArgument = argv[1];
    char *heightArgument = argv[2];
    char *offsetArgument = argv[3];
    width = atoi(widthArgument);
    height = atoi(heightArgument);
    int offset = atoi(offsetArgument);
    ofstream outFile("bla.bmp", ofstream::binary|ofstream::out);
    BitmapHeader header = createHeader(width, height);
    outFile.write((char *)&header, sizeof(BitmapHeader));
    AlignmentPadding padding;
    char extention[5] = ".dat";
    char folder[6] = "data/";
//outFile.write((char*)&padding, sizeof(AlignmentPadding));
  bool writePadding = false;
    for(int y = height-offset; y >= offset; y--) {
        char filename[50];
        string s = to_string(y);
        strcpy(filename, folder);
        strcat(filename, s.c_str());
        strcat(filename, extention);

        cout << filename << endl;
        ifstream inFile(filename, ifstream::binary|ifstream::in);
        char color;
        while(inFile.get(color)) {
          if(color <= 127) {
            outFile.write((char *)colors[color], sizeof(Color));
          } else {
            outFile.write((char *)&blackColor, sizeof(Color));
          }
        }


        inFile.close();
    }

    outFile.close();
    return 0;
}
