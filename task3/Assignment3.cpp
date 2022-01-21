#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <list>
#include <sstream>
#include <typeinfo>
using namespace std;
// overloaded the + operator for vector bools
// see comments in the big int + for comments
std::vector<bool> operator + (std::vector<bool> &lhs,const std::vector<bool> &rhs){
        if (lhs.size() < rhs.size()){ 
            cout << "Error: RHS Big int is larger than LHS";
        }
 
        bool carry = false;
        int diff = lhs.size() - rhs.size();
        for (int j = int(rhs.size())-1; j >=0 ; j--)
        {
            
            if(lhs[j+diff] == 0 && rhs[j] == 0 && carry ==1){
               lhs[j+diff] = true;
                carry = false;
            }
            else if(lhs[j+diff] == 0 && rhs[j] == 0){
                lhs[j+diff] = false;
            }         
            else if((lhs[j+diff] == 1 && rhs[j] == 0 && carry == 1) || (lhs[j+diff] == 0 && rhs[j] == 1 && carry == 1)){
                lhs[j+diff] = false;
                carry = true;
            } 
            else if((lhs[j+diff] == 1 && rhs[j] == 0) || (lhs[j+diff] == 0 && rhs[j] == 1)){
                lhs[j+diff] = true;
            }
            else if((lhs[j+diff] == 1 && rhs[j] == 1 && carry == 1)){
                lhs[j+diff] = true;
                carry = 1;
            }
            else if(lhs[j+diff] == 1 && rhs[j]==1){
                lhs[j+diff] = false;
                carry = 1;
            }
            if (j==0 && carry==1){
                diff --;
                while (diff >= 0){
                    if(lhs[diff] == 1 && carry == 1){
                        lhs[diff] = 0;
                    }
                    else if(lhs[diff] == 0 && carry == 1){
                        carry = 0;
                        lhs[diff] = 1;
                    }
                    if (carry == 0){
                        break;
                    }
                    diff --;
                }
                
            }
            
        }
        return lhs;
    }

// overloaded the - operator for vector bools
// see comments in the big int - for comments
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

// the comparison operator == was overloaded to compare two binary numbers 
// for this a mathmatical XOR was done on the numbers
bool operator == (const std::vector<bool> &lhs,const std::vector<bool> &rhs){
    // this operator works with different size operators
    // given that the larger operator doesn't have any 1's after the conlusion of the other side
    if (lhs.size()>rhs.size()){
        int diff = lhs.size() - rhs.size();
        for (int j = int(rhs.size())-1; j >=0 ; j--){
            // if one of the binary digits does not match up with its equivilent false is returned
            if ((rhs[j] == 1 && lhs[j+diff] == 0) || (rhs[j] == 0 && lhs[j+diff] == 1)){
                return false;
            }              
        }
        // two numbers of different sizes may still be equal given that there are no 1s after the conclusion of one of them
        // so  00101 ==  101
        // this for loops checks if there are any 1s after the conclusion of the rhs
        // and if so returns a false
        for (int i = diff - 1; i >= 0 ; i--){
            if (lhs[i] == 1){
                return false;
            }
        }
    }
    // if rhs is larger than lhs
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
    // if all the above tests are passe the two binaries are equal and true is returned
    return true;
}

// overloading for the < operator for vector bools
// the lhs is minused from the rhs if the resulting binary is greater than 0
// then the lhs is greater and false is returned
// otherwise true is returned 
bool operator < (const std::vector<bool> &lhs,const std::vector<bool> &rhs){
    vector<bool> hold = lhs;
    // rhs is minused from lhs
    vector<bool> temp = hold - rhs;
    for (int j = int(temp.size())-1; j >=0 ; j--)
    {
        // if any bit is found that is not 0 then the lhs is larger than the rhs
        if(temp[j] == true){
            return false;
        }
    }
    return true;
}


template<int T>
class myuint{
    // myuint has two values, the number of bits in it and a binary number
    // in actualoty the bits variable went a bit unused
    // if this were attempted again it may have been ommitted
    // however then i could have ommitted this class entirely and just overloaded the vector bools
    public:  
    int bits = T;
    std::vector<bool> binary;
    // if nothing is parsed in the parameters an empty binary is created
    myuint(){
        // a compilation error is presented if the passed binary number is not an exponent if 2
        if(floor(log2(T))!=log2(T)){
            cout << "Comppilation Error : " << T << " is not an exponenet of 2\n";
            return;
        }
        // an empty binary number of T bits is created
        this->bits = bits;
        while(bits>0){
            this->binary.push_back(false);
            bits--;
        }
        this->bits = bits;
    }
    // if a vector bool is parsed then it initilised to that vector bool
    myuint(vector<bool> binary){
        if(floor(log2(T))!=log2(T)){
            cout << "Comppilation Error : " << T << " is not an exponenet of 2\n";
            return;
         }
        this->bits = bits;
        this->binary = binary;
    }
    // if an integer is parsed it is initilised to that integer
    myuint(int num){
        if(floor(log2(T))!=log2(T)){
            cout << "Comppilation Error : " << T << " is not an exponenet of 2\n";
            return;
        }
        this->bits = bits;
        // an integer hold the bits
        int hold = bits;
        while(hold>0){
            // it checks if it can subtract the bits value from the number to be initilised
            if(num>=pow(2,hold-1)){
                // bits value is 2^(n-1)
                num -= pow(2,hold-1);
                // if it can 1 is added to the binary number
                this->binary.push_back(true);
            }
            else{
                // otherwise 0 is added
                this->binary.push_back(false);
            }
            hold--;
        }
    }
    // this function is used for when the big int is initilised to a string
    
    string divideString(string num){
        // when dividing an even number by two the answer is alwayts a whole number
        // for example  4/2 = 2.0
        // while dividing an odd number buy 2 results in a .5
        // 3/2 = 1.5
        // the carry hold a 0 or a 5 depending on if the number was odd or even
        int carry = 0;
        // an empty string is created that will hold the 
        string divided = "";
        for (size_t i = 0; i < num.length(); i ++){
            // even
            if ((num[i] - 48)%2 == 0 ){
                // the ascii value of the character is editied to reflect it being divided
                // 48 is the digits offset from 0 in asccii
                divided += (((num[i] - 48)/2)+carry)+48;
                // becuase it was an even number the carry holds 0
                carry = 0;
            }
            // odd
            else{
                divided += (((num[i] - 48)/2)+carry)+48;
                // the carry is 5 because it was an odd number
                carry = 5;
            }
        }

        // remove front character if it is 0
        // this way we prevent the string from becoming a string of 0's like "00000"
        if (divided[0] == '0' && divided.length() > 1){
            divided = divided.substr(1);
        }

        return divided;
    }
    // when a string is parsed to be intilised to
    myuint(string num){
        this->bits = bits;    
        std::vector<bool> stack;
        // it loops until the string is empty "0"
        while (num != "0"){
            // checks if the last digit in the string is odd or even
            // odd numbers 1,3,5,7,9
            if(num.back() == 49 ||num.back() == 51 ||num.back() == 53 ||num.back() == 55 ||num.back() == 57){
                // if it is odd it pushes back a 1
                stack.push_back(true);
            }
            else{
                // otherwise it pushes back a 0
                stack.push_back(false);
            }
            // the string is then divided by two using the above function
            num = divideString(num);
        }
        // it checks whether any more 0 needs to be added after the number is initilised
        // if so it adds them to the binary
        int hold = bits;
        while(hold>int(stack.size())){
            this->binary.push_back(false);
            hold--;
        }

        // until now the binary number is reversed so this function flips the binary number
        for (int j = (int(stack.size()) - 1); j >= 0; j--)
        {
            binary.push_back(stack.at(j));
        }
    }
    // this function prints out the binary number
    void printBinary(){
        for (std::size_t j = 0; j < this->binary.size(); j++)
            {
                cout << this->binary[j] << " , ";
            }
        cout << "\n";
    }
    // shifting operator which takes the about of bits it should be shifted by on the lhs
    myuint operator << (const int &value){
        for (int i = 0; i < value; i ++){
            // a bit is removed from the front and a 0 is added to the back
            this->binary.erase(this->binary.begin());
            this->binary.push_back(false);
        }
        return *this;
    }
    // shifting operator which takes the about of bits it should be shifted by on the lhs
    myuint operator >> (const int &value){
        for (int i = 0; i < value; i ++){
            // a bit is removed from the back and a 0 is appended to the front
            this->binary.erase(this->binary.end());
            this->binary.insert(this->binary.begin(),false);
        }
        return *this;
        
    }

    // + operator is overloaded to accept integers
    myuint operator + (const int &obj){
        myuint<0> x(obj);
        *this + x;
        return *this;
    }
    template <int U>
    myuint operator + (const myuint<U> &obj){
        // checks if the rhs is larger than the lhs if so a Warning is presented
        if (this->bits < obj.bits){ 
            cout << "Warning at +: RHS Big int is larger than LHS";
        }
        
        // carry used in binary +
        bool carry = false;
        int diff = this->bits - obj.bits;
        // addition is done for the big integers
        for (int j = int(obj.binary.size())-1; j >=0 ; j--)
        {
            // if both bits are 0 but there is something in the carry
            // then the bit is 1 and the carry is emptied
            if(this->binary[j+diff] == 0 && obj.binary[j] == 0 && carry ==1){
               this->binary[j+diff] = true;
                carry = false;
            }
            // otherwise the bit is 0 
            // 0 + 0 = 0
            else if(this->binary[j+diff] == 0 && obj.binary[j] == 0){
                this->binary[j+diff] = false;
            }  
            else if((this->binary[j+diff] == 1 && obj.binary[j] == 0 && carry == 1) || (this->binary[j+diff] == 0 && obj.binary[j] == 1 && carry == 1)){
                this->binary[j+diff] = false;
                carry = true;
            }  
            // if one of them is true then it is set to true     
            else if((this->binary[j+diff] == 1 && obj.binary[j] == 0) || (this->binary[j+diff] == 0 && obj.binary[j] == 1)){
                this->binary[j+diff] = true;
            }
            // if both are ones and the carry is one
            // the ans is one carry one
            else if((this->binary[j+diff] == 1 && obj.binary[j] == 1 && carry == 1)){
                this->binary[j+diff] = true;
                carry = 1;
            }
            // if both are 1s but the carry isn't then it's 0 carry 1
            else if(this->binary[j+diff] == 1 && obj.binary[j]==1 && carry == 0){
                this->binary[j+diff] = false;
                carry = 1;
            }
            // if there is still something still in the carry if statement ensures it is emptied if possible
            if (j==0 && carry==1){
                diff --;
                while (diff >= 0){
                    if(this->binary[diff] == 1 && carry == 1){
                        this->binary[diff] = 0;
                    }
                    else if(this->binary[diff] == 0 && carry == 1){
                        carry = 0;
                        this->binary[diff] = 1;
                    }
                    if (carry == 0){
                        break;
                    }
                    diff --;
                }
                
            }
            
        }
        return *this;
    }

    // - operator is overloaded to accept integers
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

        // the difference between the two bits is aqcuired to adjust for the different lengths of the vectors
        int diff = this->bits - obj.bits;
        for (int j = int(obj.binary.size())-1; j >=0 ; j--)
        {
            // 0 - 0 = 0
            if(this->binary[j+diff] == 0 && obj.binary[j] == 0){
                this->binary[j+diff] = false;
            }    
            // 1 - 0 = 1
            else if(this->binary[j+diff] == 1 && obj.binary[j] == 0){
                this->binary[j+diff] = true;
            }
            // 1 - 1 = 0
            else if(this->binary[j+diff] == 1 && obj.binary[j]==1){
                this->binary[j+diff] = false;
            }
            // 0 - 1 = ?
            // we need to borrow
            else if(this->binary[j+diff] == 0 && obj.binary[j]==1){
                bool found = false;
                // the function loops foward in the lhs checking if there exists a 1 it can borrow
                for (int i = j+diff-1; i >=0 ; i--)
                {
                    // if it finds one it is borrowed
                    if(this->binary[i] == 1){
                        found = true;
                        // the found 1 is set to 0 because it has been borrowed
                        this->binary[i] = false;
                        i++;
                        // all the bits between the borrowed 1 and the bit are set to 1
                        while(i!=j+diff){
                            this->binary[i] = true;
                            i++;
                        }
                        break;
                    }
                }
                // the bit is set to 1
                this->binary[j+diff] = true;
                // if it doesn't find one then the lhs is negative
                // this big int is only designed for positive numbers so instead it is set to 0
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

    // = operator is overloaded to accept integers
    myuint operator = (const int &obj){
        myuint<0> x(obj);
        *this = x;
        return *this;
    }
    template <int U>
    // the rhs binary is coppied to the lhs
    myuint operator = (const myuint<U> &obj){
        if (this->bits < obj.bits){ 
            cout << "Warning = OP: RHS Big int is larger than LHS";
        }
        int diff = this->bits - obj.bits;
        for (int j = int(obj.binary.size())-1; j >=0 ; j--)
        {
            // values in the rhs binary are transfered to the lhs
            this->binary[j+diff] = obj.binary[j];
        }
        return *this;
    }

    // * operator is overloaded to accept integers
    myuint operator * (const int &obj){
        myuint<0> x(obj);
        *this * x;
        return *this;
    }
    template <int U>
    myuint operator * (const myuint<U> &obj){
        vector<bool> hold = this->binary;
        vector<bool> ans = this->binary;
        // an empty binary number is created to hold the answer 
        for (int j = int(this->binary.size())-1; j >=0 ; j--)
        {
            ans[j] = false;
        }

        // take 10 * 101
        // we add 10 shifted by how many bits it is offset by in the rhs
        // and depending if the bit on the rhs is 0 or 1 it is added to the answer
        // so 1(10) + 0(100) + 1(1000) = 1010
        // 2 * 5 = 10
        for (int j = int(obj.binary.size())-1; j >=0 ; j--)
        {
            // it checks if it is a 1 
            // if so it will add the lhs to the answer
            if (obj.binary[j] == 1){
                ans = ans+hold;
            }
            // the lhs is shifted left by 1
            hold.erase(hold.begin());
            hold.push_back(false);
        }
        // answer is set to the binary number
        this->binary=ans;
        return *this;
    }

    // == operator is overloaded to accept integers
    // the comparison operator == was overloaded to compare two binary numbers 
    // for this a mathmatical XOR was done on the numbers
    // see similar function for overloadeing the vecotr bool for comments
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

    // / operator is overloaded to accept integers
    myuint operator / (const int &obj){
        myuint<0> x(obj);
        *this / x;
        return *this;
    }
    template <int U>
    // division can be translated to how many times can this number fit in this number
    // this function counts that by storing the times in a variable called ans
    // a variable increment holds 1 to increment ans every pass
    // and minusing the rhs from the lhs until the lhs is empty(or less than the rhs in that case u have a remainder)
    myuint operator / (const myuint<U> &obj){
        vector<bool> hold = this->binary;
        vector<bool> ans = this->binary;
        vector<bool> increment = this->binary;
        // two bools are emptied to hold the answer
        for (int j = int(this->binary.size())-1; j >=0 ; j--)
        {
            ans[j] = false;
            increment[j] = false;
        }
        increment.erase(increment.begin());
        increment.push_back(true);
        // the function loops until no more rhs can fit in lhs
        for(;;){
            // every time it removes the rhs from the lhs and increments the counter (ans)
            hold - obj.binary;
            // ans is incremented
            ans = ans + increment;
            // if the lhs == rhs then 1 more can be fit before it breaks
            if (hold == obj.binary){
                ans = ans + increment;
                break;
            }
            // otherwise there is a remainder and it breaks anyway
            else if(hold < obj.binary){
                break;
            }
        }
        this->binary=ans;
        return *this;
    }

    // overloading the operator to accept integers
    myuint operator % (const int &obj){
        myuint<0> x(obj);
        *this % x;
        return *this;
    }
    // function is similar to the above function
    // however it returns what is still in the hold variable
    // obviously the increment function isn't needed so it was removed
    template <int U>
    myuint operator % (const myuint<U> &obj){
        vector<bool> hold = this->binary;
        for(;;){
            hold - obj.binary;
            if (hold == obj.binary || hold < obj.binary){
                break;
            }
        }
        // if the remainder is = to the rhs then the remainder is 0
        vector<bool> empty;
        empty.push_back(false);
        if (hold == obj.binary){
            for (int j = int(this->binary.size())-1; j >=0 ; j--)
            {
                hold[j] = false;
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


 
// this function is used to overload all of the above operators to accept integers
template<> myuint<0>::myuint(int num){
    // an integer is 16 bits, so the binary number is first set to 16 bits
    this->bits = 16;
    int hold = 16;
    // the bionary number is created similar to the implementation in the normal integer function
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
    // 16 bits would be a waste of space if the user just wanted to add 4 for example
    // so every unused bit infront of the number is removed
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
    myuint<4> b(3);
    myuint<16> c(0);

    a.printBinary();
    b.printBinary();
    c = a % b;
    c.printBinary();
    int ans = c.template_convert_to();

    cout << ans <<"\n";
}