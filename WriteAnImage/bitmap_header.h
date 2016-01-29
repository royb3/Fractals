struct BitmapHeader {
    unsigned short signature = 0x4D42;
    unsigned int fileSize;
    unsigned int reserved;
    unsigned int imageDataOffset = 54;
    unsigned int bitmapInfoHeaderSize = 40;
    unsigned int width;
    unsigned int height;
    unsigned short numberOfPlanes = 1;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageDataSize;
    unsigned int horizontalResolution;
    unsigned int verticalResolution;
    unsigned int numberOfColors;
    unsigned int numberOfImportantColors;
};
