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
        this->bits = bits;
    }
    myuint(vector<bool> binary){
        this->bits = bits;
        this->binary = binary;
    }
    myuint(int num){
        this->bits = bits;
        int hold = bits;
        while(hold>0){
            if(num>=pow(2,hold-1)){
                num -= pow(2,hold-1);
                this->binary.push_back(true);
            }
            else{
                this->binary.push_back(false);
            }
            hold--;
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
        int hold = bits;
        while(hold>int(stack.size())){
            this->binary.push_back(false);
            hold--;
        }

        for (int j = (int(stack.size()) - 1); j >= 0; j--)
        {
            binary.push_back(stack.at(j));
        }
    }
    void printBinary(){
        for (std::size_t j = 0; j < this->binary.size(); j++)
            {
                cout << this->binary[j] << " , ";
            }
    }
    myuint operator << (const int &value){
        for (int i = 0; i < value; i ++){
            this->binary.erase(this->binary.begin());
            this->binary.push_back(false);
        }
        return *this;
    }
    myuint operator >> (const int &value){
        for (int i = 0; i < value; i ++){
            this->binary.erase(this->binary.end());
            this->binary.insert(this->binary.begin(),false);
        }
        return *this;
        
    }
    template <int U>
    myuint operator + (const myuint<U> &obj){
        if (this->bits < obj.bits){ 
            cout << "Error: RHS Big int is larger than LHS";
        }
 
        bool carry = false;
        
        for (int j = int(obj.binary.size())-1; j >=0 ; j--)
        {
            if(this->binary[j] == 0 && obj.binary[j] == 0 && carry ==1){
               this->binary[j] = true;
                carry = false;
            }
            else if(this->binary[j] == 0 && obj.binary[j] == 0){
                this->binary[j] = false;
            }         
            else if((this->binary[j] == 1 && obj.binary[j] == 0) || (this->binary[j] == 0 && obj.binary[j] == 1)){
                this->binary[j] = true;
            }
            else if((this->binary[j] == 1 && obj.binary[j] == 1 && carry == 1)){
                this->binary[j] = true;
                carry = 1;
            }
            else if(binary[j] == 1 && obj.binary[j]==1){
                this->binary[j] = false;
                carry = 1;
            }
            
        }
        return *this;

        
    }

    template <int U>
    myuint operator - (const myuint<U> &obj){
        if (this->bits < obj.bits){ 
            cout << "Error: RHS Big int is larger than LHS";
        }
        for (int j = int(obj.binary.size())-1; j >=0 ; j--)
        {
            if(this->binary[j] == 0 && obj.binary[j] == 0){
                this->binary[j] = false;
            }    
            else if(this->binary[j] == 1 && obj.binary[j] == 0){
                this->binary[j] = true;
            }
            else if(binary[j] == 1 && obj.binary[j]==1){
                this->binary[j] = false;
            }
            else if(binary[j] == 0 && obj.binary[j]==1){
                for (int i = j-1; i >=0 ; i--)
                {
                    if(this->binary[i] == 1){
                        this->binary[i] = false;
                        i++;
                        while(i!=j){
                            this->binary[i] = true;
                            i++;
                        }
                        break;
                    }
                }
                this->binary[j] = true;
            }
        }
        return *this;
    }

    template <int U>
    myuint operator = (const myuint<U> &obj){
        if (this->bits < obj.bits){ 
            cout << "Error: RHS Big int is larger than LHS";
        }
        for (int j = int(obj.binary.size())-1; j >=0 ; j--)
        {
            this->binary[j] = obj.binary[j];
        }
        return *this;
    }
    // template <class L>
    // void template_convert_to(){
    // }
    
    // template <>
    int template_convert_to(){
        int ans = 0;
        int opposite = 0;
        for (int j = int(this->binary.size())-1; j >=0 ; j--)
        {
            if(this->binary[j] == 1){
                ans += pow(2,opposite);
            }
            opposite ++;
        }
        return ans;
    }
};
 


int main(){
    //17498005798264095394980017816940970922825355447145699491406164851279623993595007385788105416184430591
    // myuint<334> i("17498005798264095394980017816940970922825355447145699491406164851279623993595007385788105416184430591");
    myuint<4> a(8);
    myuint<4> b(1);
    myuint<4> c(0);

    a.printBinary();
    cout << "\n";
    b.printBinary();
    cout << "\n";
    c = a - b - b;
    c.printBinary();
    int ans = c.template_convert_to();
    cout << "\n";
    cout << ans <<"\n";
}




















