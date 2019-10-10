#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

class classStream{
    public:
        classStream(std::vector<char> s);
        classStream();
        void setStream(std::vector<char> s);
        void nextInHex(char* s, int size);
        void nextInBytes(char* s, int size);
        int nextInt();
        short nextShort();
        void print();
        

    private:
        std::vector<char> classfile;
        unsigned int toInt(char* h){
            std::stringstream ss;
            unsigned int x;
            ss << std::hex << h;
            ss >> x;
            return x;
        }


        unsigned short toShort(char* h){
            std::stringstream ss;
            unsigned short x;
            ss << std::hex << h;
            ss >> x;
            return x;
        }

        unsigned char toChar(char* h){
            std::stringstream ss;
            char x;
            ss << std::hex << h;
            ss >> x;
            return x;
        }
};