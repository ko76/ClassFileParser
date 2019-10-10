#include "classStream.hpp"
#include <iostream>

using namespace std;
int position;
stringstream ss;
int size;


classStream::classStream(vector<char> s){
    classfile = s;
    position = 0;
    for (auto& el : s){
		ss << setfill('0') << setw(2) << hex << (0xff & (unsigned int)el);
	}
}
classStream::classStream(){

}

void classStream::setStream(vector<char> s){
    classfile = s;
    position = 0;
    for (auto& el : s){
		ss << setfill('0') << setw(2) << hex << (0xff & (unsigned int)el);
	}
}


void classStream::print(){
    cout << ss.str() << "\n";
}

void classStream::nextInHex(char* s, int size){
    for (int i = 0; i < size-1; i++){
        ss.get(s[i]);
    }
    s[size-1] = '\0';
}

void classStream::nextInBytes(char *s, int size){
    for (int i = 0; i < size*2; i++){
        ss.get(s[i]);
    }
    s[size*2] = '\0';
}

int classStream::nextInt(){
    char k[9];
    for (int i = 0; i < 8; i++){
        ss.get(k[i]);
    }
    k[8] = '\0';
    int s = toInt(k);
    return s;
}

short classStream::nextShort(){
    char k[5];
    for (int i = 0; i < 4; i++){
        ss.get(k[i]);
    }
    k[4] = '\0';
    short s = toShort(k);
    return s;
}
