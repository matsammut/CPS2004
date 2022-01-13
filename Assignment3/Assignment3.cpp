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
    myuint(){
        this->bits = bits;
        while(bits>0){
            this->binary.push_back(false);
            bits--;
        }
    }
    myuint(vector<bool> binary){
        this->bits = bits;
        this->binary = binary;
    }
    myuint(int num){
        this->bits = bits;
        while(bits>0){
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
    void operator << (const int &value){
        for (int i = 0; i < value; i ++){
            binary.erase(binary.begin());
            binary.push_back(false);
        }
        
    }
    void operator >> (const int &value){
        for (int i = 0; i < value; i ++){
            binary.erase(binary.end());
            binary.insert(binary.begin(),false);
        }
        
    }
    
};
 


int main(){
    //17498005798264095394980017816940970922825355447145699491406164851279623993595007385788105416184430591
    // myuint<334> i("17498005798264095394980017816940970922825355447145699491406164851279623993595007385788105416184430591");
    myuint<7> a(5);
    a >> 1;
    a.printBinary();

    cout << "\n";
}




















// myuint operator + (constexpr myuint &obj){
//         bool objsmaller = false;
//         if (this->bits > obj.bits){ 
//             objsmaller = true;
//         }
 
//         bool carry = false;
//         if(objsmaller == true){
//             myuint<obj.bits> tmp;
//             for (std::size_t j = 0; j < this->binary.size(); j++)
//             {
//                 if (j<obj.binary.size()){
//                     if(this->binary[j] == 0 && obj.binary[j] == 0){
//                         tmp.binary[j] = false;
//                     }
//                     else if(this->binary[j] == 0 && obj.binary[j] == 0 && carry ==1){
//                         tmp.binary[j] = true;
//                         carry = false;
//                     }
//                     else if((this->binary[j] == 1 && obj.binary[j] == 0) || (this->binary[j] == 0 && obj.binary[j] == 1)){
//                         tmp.binary[j] = true;
//                     }
//                     else if((this->binary[j] == 1 && obj.binary[j] == 1 && carry == 1)){
//                         tmp.binary[j] = true;
//                         carry = 1;
//                     }
//                     else if(binary[j] == 1 && obj.binary[j]==1){
//                         tmp.binary[j] = false;
//                         carry = 1;
//                     }
                
//                 }
//             }
//             return tmp;
//         }
        
//     }