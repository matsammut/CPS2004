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
    string divideString(string num){
        int carry = 0;
        string divided = "";
        for (size_t i = 0; i < num.length(); i ++){
            // even
            if ((num[i] - 48)%2 == 0 ){
                divided += (((num[i] - 48)/2)+carry)+48;
                carry = 0;
            }
            // odd
            else{
                divided += (((num[i] - 48)/2)+carry)+48;
                carry = 5;
            }
        }

        // remove front character if it is 0
        if (divided[0] == '0' && divided.length() > 1){
            divided = divided.substr(1);
        }

        return divided;
    }
    myuint(string num){
        this->bits = bits;
        
        std::vector<bool> stack;
        while (num != "0"){
            // odd numbers 1,3,5,7,9
            if(num.back() == 49 ||num.back() == 51 ||num.back() == 53 ||num.back() == 55 ||num.back() == 57){
                stack.push_back(true);
            }
            else{
                stack.push_back(false);
            }
            num = divideString(num);
        }

        while(bits>int(stack.size())){
            this->binary.push_back(false);
            bits--;
        }

        for (std::size_t j = (stack.size() - 1); j > 0; j--)
        {
            binary.push_back(stack.at(j));
        }
        binary.push_back(stack.back());

    }
    void printBinary(){
        for (std::size_t j = 0; j < this->binary.size(); j++)
            {
                cout << this->binary[j] << " , ";
            }
    }
    // myuint operator + (const myuint& obj){
    //     bool objsmaller = false;
    //     myuint tmp;
    //     int smaller;
    //     if (bits > obj.bits){
            
    //         smaller = obj.bits;
    //         objsmaller = true;
    //     }
    //     else{
    //         smaller = bits;         
    //     }

        
    //     bool carry = false;
    //     if(objsmaller == true){
    //         for (std::size_t j = 0; j < binary.size(); j++)
    //         {
    //             if (j<smaller){
    //                 if(binary[j] == 0 && obj.binary[j] == 0){
    //                     tmp.binary[j] = false;
    //                 }
    //                 else if(binary[j] == 0 && obj.binary[j] == 0 && carry ==1){
    //                     tmp.binary[j] = true;
    //                     carry = false;
    //                 }
    //                 else if((binary[j] == 1 && obj.binary[j] == 0) || (binary[j] == 0 && obj.binary[j] == 1)){
    //                     tmp.binary[j] = true;
    //                 }
    //                 else if((binary[j] == 1 && obj.binary[j] == 1 && carry == 1)){
    //                     tmp.binary[j] = true;
    //                     carry = 1;
    //                 }
    //                 else if(binary[j] == 1 && obj.binary[j]==1){
    //                     tmp.binary[j] = false;
    //                     carry = 1;
    //                 }
                
    //             }
    //         }
    //     }
    
        


    //     return tmp;
    // }
};
 


int main(){
    //17498005798264095394980017816940970922825355447145699491406164851279623993595007385788105416184430591
    // myuint<334> i("17498005798264095394980017816940970922825355447145699491406164851279623993595007385788105416184430591");
    i.printBinary();
    // cout << pow(2,1023);

    cout << "\n";
}
