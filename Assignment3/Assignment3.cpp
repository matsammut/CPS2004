#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <list>

using namespace std;

template<int T>
class myuint{
    private:   
    int bits = T;
    std::vector<bool> binary;
    public:
    myuint(int n) : bits(n) {
        myuint(bits,n);
    }
    myuint(int bits,int num){
        while(bits>=0){
            int power = pow(2,bits);
            if(num>=power){
                num -= power;
                binary.push_back(true);
            }
            else{
                binary.push_back(false);
            }
            bits--;
        }
        for (std::size_t j = 0; j < binary.size(); j++)
            {
                cout << binary[j] << " , ";
            }
    }
    void printBinary(){
        for (std::size_t j = 0; j < binary.size(); j++)
            {
                cout << binary[j] << " , ";
            }
    }
};


int main(){
    myuint<1024> i(5);
    i.printBinary();
    printf("hello");
}