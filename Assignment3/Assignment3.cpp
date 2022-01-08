#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <list>

using namespace std;

template<int T>
class myuint{
    public:
    int bits = T;
    std::vector<bool> binary;
    myuint(int num){
        this->bits = bits;
        while(bits>=0){
            int power = pow(2,bits);
            if(num>=power){
                num -= power;
                this->binary.push_back(true);
            }
            else{
                this->binary.push_back(false);
            }
            bits--;
        }
    }
    void printBinary(){
        for (std::size_t j = 0; j < this->binary.size(); j++)
            {
                cout << this->binary[j] << " , ";
            }
    }
};


int main(){
    myuint<64> i(27);
    i.printBinary();

}