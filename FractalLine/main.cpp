#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv) {
    if(argc != 4) {
        ofstream errFile("err.log", ofstream::app|ofstream::out);
        errFile << "The amount of parameters is wrong."<<endl;
        errFile.close();
        return 1;
    }
    return 0;
}
