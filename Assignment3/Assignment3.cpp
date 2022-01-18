#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <list>
#include <sstream>
#include <typeinfo>
using namespace std;
std::vector<bool> operator + (std::vector<bool> &lhs,const std::vector<bool> &rhs){
        if (lhs.size() < rhs.size()){ 
            cout << "Error: RHS Big int is larger than LHS";
        }
 
        bool carry = false;
        
        for (int j = int(rhs.size())-1; j >=0 ; j--)
        {
            if(lhs[j] == 0 && rhs[j] == 0 && carry ==1){
               lhs[j] = true;
                carry = false;
            }
            else if(lhs[j] == 0 && rhs[j] == 0){
                lhs[j] = false;
            }         
            else if((lhs[j] == 1 && rhs[j] == 0) || (lhs[j] == 0 && rhs[j] == 1)){
                lhs[j] = true;
            }
            else if((lhs[j] == 1 && rhs[j] == 1 && carry == 1)){
                lhs[j] = true;
                carry = 1;
            }
            else if(lhs[j] == 1 && rhs[j]==1){
                lhs[j] = false;
                carry = 1;
            }
            
        }
        return lhs;
    }

std::vector<bool> operator - (std::vector<bool> &lhs,const std::vector<bool> &rhs){
    if (lhs.size() < rhs.size()){ 
        cout << "Error: RHS Big int is larger than LHS";
    }
    int diff = lhs.size() - rhs.size();
    
    for (int j = int(rhs.size())-1; j >=0 ; j--)
    {
        if(lhs[j+diff] == 0 && rhs[j] == 0){
            lhs[j+diff] = false;
        }    
        else if(lhs[j+diff] == 1 && rhs[j] == 0){
            lhs[j+diff] = true;
        }
        else if(lhs[j+diff] == 1 && rhs[j]==1){
            lhs[j+diff] = false;
        }
        else if(lhs[j+diff] == 0 && rhs[j]==1){
            bool found = false;
            for (int i = j+diff-1; i >=0 ; i--)
            {
                if(lhs[i] == 1){
                    found = true;
                    lhs[i] = false;
                    i++;
                    while(i!=j+diff){
                        lhs[i] = true;
                        i++;
                    }
                    break;
                }
            }
            lhs[j+diff] = true;
            if (found == false){
                for (int i = int(lhs.size())-1; i >=0 ; i--)
                {
                    lhs[i] = false;
                }
                return lhs;
            }
        }
    }
    return lhs;
}
bool operator == (const std::vector<bool> &lhs,const std::vector<bool> &rhs){
    if (lhs.size()>rhs.size()){
        int diff = lhs.size() - rhs.size();
        for (int j = int(rhs.size())-1; j >=0 ; j--){
            if ((rhs[j] == 1 && lhs[j+diff] == 0) || (rhs[j] == 0 && lhs[j+diff] == 1)){
                return false;
            }              
        }
        for (int i = diff - 1; i >= 0 ; i--){
            if (lhs[i] == 1){
                return false;
            }
        }
    }
    else{
        int diff =  rhs.size() - lhs.size();
        for (int j = int(lhs.size())-1; j >=0 ; j--)
        {
            if ((rhs[j+diff] == 1 && lhs[j] == 0) || (rhs[j+diff] == 0 && lhs[j] == 1)){
                return false;
            }              
        }
        for (int i = diff - 1; i >= 0 ; i--){
            if (rhs[i] == 1){
                return false;
            }
        }
    }
    return true;
}
bool operator < (const std::vector<bool> &lhs,const std::vector<bool> &rhs){
    vector<bool> hold = lhs;
    vector<bool> temp = hold - rhs;
    for (int j = int(temp.size())-1; j >=0 ; j--)
    {
        if(temp[j] == true){
            return false;
        }
    }
    return true;
}


template<int T>
class myuint{
    public:  
    int bits = T;
    std::vector<bool> binary;
    myuint(){
        if(floor(log2(T))!=log2(T)){
            cout << "Comppilation Error : " << T << " is not an exponenet of 2\n";
            return;
        }
        this->bits = bits;
        while(bits>0){
            this->binary.push_back(false);
            bits--;
        }
        this->bits = bits;
    }
    myuint(vector<bool> binary){
        if(floor(log2(T))!=log2(T)){
            cout << "Comppilation Error : " << T << " is not an exponenet of 2\n";
            return;
         }
        this->bits = bits;
        this->binary = binary;
    }
    myuint(int num){
        if(floor(log2(T))!=log2(T)){
            cout << "Comppilation Error : " << T << " is not an exponenet of 2\n";
            return;
        }
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

    myuint operator + (const int &obj){
        myuint<0> x(obj);
        *this + x;
        return *this;
    }
    template <int U>
    myuint operator + (const myuint<U> &obj){
        if (this->bits < obj.bits){ 
            cout << "Error: RHS Big int is larger than LHS";
        }
 
        bool carry = false;
        int diff = this->bits - obj.bits;
        for (int j = int(obj.binary.size())-1; j >=0 ; j--)
        {
            if(this->binary[j+diff] == 0 && obj.binary[j] == 0 && carry ==1){
               this->binary[j+diff] = true;
                carry = false;
            }
            else if(this->binary[j+diff] == 0 && obj.binary[j] == 0){
                this->binary[j+diff] = false;
            }         
            else if((this->binary[j+diff] == 1 && obj.binary[j] == 0) || (this->binary[j+diff] == 0 && obj.binary[j] == 1)){
                this->binary[j+diff] = true;
            }
            else if((this->binary[j+diff] == 1 && obj.binary[j] == 1 && carry == 1)){
                this->binary[j+diff] = true;
                carry = 1;
            }
            else if(this->binary[j+diff] == 1 && obj.binary[j]==1){
                this->binary[j+diff] = false;
                carry = 1;
            }
            
        }
        return *this;
    }

    myuint operator - (const int &obj){
        myuint<0> x(obj);
        *this - x;
        return *this;
    }
    template <int U>
    myuint operator - (const myuint<U> &obj){
        if (this->bits < obj.bits){ 
            cout << "Error - OP: RHS Big int is larger than LHS";
        }
        int diff = this->bits - obj.bits;
        for (int j = int(obj.binary.size())-1; j >=0 ; j--)
        {
            
            if(this->binary[j+diff] == 0 && obj.binary[j] == 0){
                this->binary[j+diff] = false;
            }    
            else if(this->binary[j+diff] == 1 && obj.binary[j] == 0){
                this->binary[j+diff] = true;
            }
            else if(this->binary[j+diff] == 1 && obj.binary[j]==1){
                this->binary[j+diff] = false;
            }
            else if(this->binary[j+diff] == 0 && obj.binary[j]==1){
                bool found = false;
                for (int i = j+diff-1; i >=0 ; i--)
                {
                    if(this->binary[i] == 1){
                        found = true;
                        this->binary[i] = false;
                        i++;
                        while(i!=j+diff){
                            this->binary[i] = true;
                            i++;
                        }
                        break;
                    }
                }
                this->binary[j+diff] = true;
                if (found == false){
                    for (int i = int(this->binary.size())-1; i >=0 ; i--)
                    {
                        this->binary[i] = false;
                    }
                    return *this;
                }
            }
        }
        return *this;
    }

    myuint operator = (const int &obj){
        myuint<0> x(obj);
        *this = x;
        return *this;
    }
    template <int U>
    myuint operator = (const myuint<U> &obj){
        if (this->bits < obj.bits){ 
            cout << "Error = OP: RHS Big int is larger than LHS";
        }
        int diff = this->bits - obj.bits;
        for (int j = int(obj.binary.size())-1; j >=0 ; j--)
        {
            this->binary[j+diff] = obj.binary[j];
        }
        return *this;
    }

    
    myuint operator * (const int &obj){
        myuint<0> x(obj);
        *this * x;
        return *this;
    }
    template <int U>
    myuint operator * (const myuint<U> &obj){
        vector<bool> hold = this->binary;
        vector<bool> ans = this->binary;
        for (int j = int(this->binary.size())-1; j >=0 ; j--)
        {
            ans[j] = false;
        }
        for (int j = int(obj.binary.size())-1; j >=0 ; j--)
        {
            if (obj.binary[j] == 1){
                ans = ans+hold;
            }
            hold.erase(hold.begin());
            hold.push_back(false);
        }
        this->binary=ans;
        return *this;
    }

    myuint operator == (const int &obj){
        myuint<0> x(obj);
        *this == x;
        return *this;
    }
    template <int U>
    bool operator == (const myuint<U> &obj){
        vector<bool> lhs = this->binary;
        vector<bool> rhs = obj.binary;
        if (this->bits>obj.bits){
            int diff = this->bits - obj.bits;
            for (int j = int(obj.binary.size())-1; j >=0 ; j--){
                if ((obj.binary[j] == 1 && this->binary[j+diff] == 0) || (obj.binary[j] == 0 && this->binary[j+diff] == 1)){
                    return false;
                }              
            }
            for (int i = diff - 1; i >= 0 ; i--){
                if (this->binary[i] == 1){
                    return false;
                }
            }
        }
        else{
            int diff =  obj.bits - this->bits;
            for (int j = int(this->binary.size())-1; j >=0 ; j--)
            {
                if ((obj.binary[j+diff] == 1 && this->binary[j] == 0) || (obj.binary[j+diff] == 0 && this->binary[j] == 1)){
                    return false;
                }              
            }
            for (int i = diff - 1; i >= 0 ; i--){
                if (obj.binary[i] == 1){
                    return false;
                }
            }
        }
        return true;
    }

    myuint operator / (const int &obj){
        myuint<0> x(obj);
        *this / x;
        return *this;
    }
    template <int U>
    myuint operator / (const myuint<U> &obj){
        vector<bool> hold = this->binary;
        vector<bool> ans = this->binary;
        vector<bool> increment = this->binary;
        for (int j = int(this->binary.size())-1; j >=0 ; j--)
        {
            ans[j] = false;
            increment[j] = false;
        }
        increment.erase(increment.begin());
        increment.push_back(true);
        for(;;){
            hold - obj.binary;
            ans = ans + increment;
            if (hold == obj.binary){
                ans = ans + increment;
                break;
            }
            else if(hold < obj.binary){
                break;
            }
        }
        this->binary=ans;
        return *this;
    }

    myuint operator % (const int &obj){
        myuint<0> x(obj);
        *this % x;
        return *this;
    }
    template <int U>
    myuint operator % (const myuint<U> &obj){
        vector<bool> hold = this->binary;
        for(;;){
            hold - obj.binary;
            if (hold == obj.binary || hold < obj.binary){
                break;
            }
        }
        this->binary=hold;
        return *this;
    }
    // template <typename L>
    // void template_convert_to(){
    // }
    // template<int> myuint<T>::
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


 

template<> myuint<0>::myuint(int num){
    this->bits = 16;
    int hold = 16;
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
    for (int i = 0; i< int(this->binary.size());){
        if(this->binary[i]==true){
            this->bits = int(this->binary.size());
            break;
        }
        else{
            this->binary.erase(this->binary.begin());
        }
    }
};


int main(){
    //17498005798264095394980017816940970922825355447145699491406164851279623993595007385788105416184430591
    // myuint<334> i("17498005798264095394980017816940970922825355447145699491406164851279623993595007385788105416184430591");
    myuint<8> a(21);
    myuint<4> b(8);
    myuint<16> c(0);

    a.printBinary();
    cout << "\n";
    b.printBinary();
    cout << "\n";
    c = a - 8;
    c.printBinary();
    int ans = c.template_convert_to();
    cout << "\n";
    cout << ans <<"\n";
}