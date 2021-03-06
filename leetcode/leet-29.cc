#include <iostream>
#include <climits>

using std::cout;
using std::endl;

class Solution {
public:
    int divide(int dividend, int divisor) {
        bool flag;
        long s, k, ret = 0; 
        
        if(divisor == 0) return INT_MAX;
        //xor operation, same is true, differ is false
        flag = (dividend < 0 ^ divisor < 0) ? true :false;
        
        k = labs(dividend); 
        s = labs(divisor);
        
        while(s <= k){
            long div = s, t = 1;//count steps; a / b = b*2^n + k, 
            //add to k / 2
            while(k > (div << 1)){
                div <<= 1; //every step multiply itself
                t <<= 1; //store how many steps has been done
            }
            //reduce the k and record the times
            k -= div;
            ret += t;
        }
        //define the sign
        ret = flag ? -ret : ret;
        return ret > INT_MAX ? INT_MAX : ret; 
    }
};

int main(int argc, const char** argv) {
    Solution s;
    cout <<s.divide(INT_MIN, 1) <<endl;
    return 0;
}