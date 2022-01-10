#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <list>
#include <sstream>
#include <typeinfo>
using namespace std;

template<int T>
class myuint{
    public:
    int bits = T;
    std::vector<bool> binary;
    myuint(int num){
        this->bits = bits;
        while(bits>=0){
            if(num>=pow(2,bits)){
                num -= pow(2,bits);
                this->binary.push_back(true);
            }
            else{
                this->binary.push_back(false);
            }
            bits--;
        }
    }
    myuint(string num){
        int x = 0;
        while (!num.empty()){
            x*=10;
            x += num[0]-'0';
            num = num.substr(1);
        }
        cout << x;
    }
    void printBinary(){
        for (std::size_t j = 0; j < this->binary.size(); j++)
            {
                cout << this->binary[j] << " , ";
            }
    }
    myuint operator + (const myuint& obj){
        bool objsmaller = false;
        myuint tmp;
        int smaller;
        if (bits > obj.bits){
            
            smaller = obj.bits;
            objsmaller = true;
        }
        else{
            smaller = bits;         
        }

        
        bool carry = false;
        if(objsmaller == true){
            for (std::size_t j = 0; j < binary.size(); j++)
            {
                if (j<smaller){
                    if(binary[j] == 0 && obj.binary[j] == 0){
                        tmp.binary[j] = false;
                    }
                    else if(binary[j] == 0 && obj.binary[j] == 0 && carry ==1){
                        tmp.binary[j] = true;
                        carry = false;
                    }
                    else if((binary[j] == 1 && obj.binary[j] == 0) || (binary[j] == 0 && obj.binary[j] == 1)){
                        tmp.binary[j] = true;
                    }
                    else if((binary[j] == 1 && obj.binary[j] == 1 && carry == 1)){
                        tmp.binary[j] = true;
                        carry = 1;
                    }
                    else if(binary[j] == 1 && obj.binary[j]==1){
                        tmp.binary[j] = false;
                        carry = 1;
                    }
                
                }
            }
        }
    
        


        return tmp;
    }
};
 


int main(){
    //17498005798264095394980017816940970922825355447145699491406164851279623993595007385788105416184430592
    myuint<16> i("17498005798264095394980017816940970922825355447145699491406164851279623993595007385788105416184430592");
    i.printBinary();
    // cout << pow(2,1023);
    cout << "\n";
}
