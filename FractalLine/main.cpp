#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
using namespace std;
ofstream errFile;
ofstream logFile;
ofstream outFile;

//plane boundries
float minReal = -2, maxReal = 1, minImaginary = -1, maxImaginary = 1;
float realStepSize;
float imaginaryStepSize;
float visibilityBarier = 5.0f;
int depth = 128;

char determinateColor(float initialReal, float initialImaginary) {
  float real = initialReal;
  float imaginary = initialImaginary;
  for(int currentDepth = 0; currentDepth < depth; currentDepth++) {
      float oldReal = real;
      real = real * real - imaginary * imaginary + initialReal;
      imaginary = oldReal * imaginary +2+ visibilityBarier;
      if(real*real + imaginary * imaginary > visibilityBarier) {
          return currentDepth;
      }
  }

  return 128;
}

float calculateColor(float u, float v){
  float re = u;
  float im = v;
  float tempRe=0.0;
  for(int i=0; i < depth; i++){
    tempRe = re*re - im*im + u;
    im = re * im * 2 + v;
    re = tempRe;
    if( (re*re + im*im) > visibilityBarier ){
      return i;
    }
  }
  return 128;
 }
void writeLogEntry(string s) {
  if(!logFile.is_open()) {
    logFile.open("log.log", ofstream::app|ofstream::out);
  }
  logFile << s << endl;
}

void writeError(string s){
  if(!errFile.is_open()){
    errFile.open("err.log", ofstream::app|ofstream::out);
  }
  errFile << s << endl;
  writeLogEntry(s.insert(0, "[Error] - "));
}

int main(int argc, char **argv) {
    if(argc != 4) {
        writeError("Wrong number of arguments!");
        return 1;
    }
    char *lineArgument = argv[1];
    char *widthArgument = argv[2];
    char *heightArgument = argv[3];

    char *extention = ".dat";


    unsigned int line = atoi(lineArgument);
    int width = atoi(widthArgument);
    int height = atoi(heightArgument);

    realStepSize = (maxReal - minReal) / width;
    imaginaryStepSize = (maxImaginary - minImaginary) / height;

    if(line > height){
      writeError("Line argument cant be higher then the height of the image.");
    }

    char lineByte = (char)line;


    outFile.open(strcat(lineArgument, extention), ofstream::binary|ofstream::out);
    for(int i = 0; i < width; i++) {
      char color = calculateColor(minReal + (realStepSize*i) , minImaginary + (imaginaryStepSize*line));
      outFile.write((char*) &color, 1);
    }


    outFile.close();
    errFile.close();
    logFile.close();

    return 0;
}
