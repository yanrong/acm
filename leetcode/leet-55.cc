#include <vector>
using std::vector;
using std::max;
using std::min;

class Solution {
public:
    
    bool canJump(vector<int>& nums) {
        int len = nums.size(), prevJump, maxJump = 0 ,start = 0, end = 1, step;
        
        if(len <= 1) return true;
        // from 0 the len - 1
        while(end < len){
            maxJump = 0;
            for(int j = start; j < end; j++){
                if(maxJump < j + nums[j]){
                    maxJump = j + nums[j];
                    step = j;
                }
            }
            if(maxJump >= len - 1) return true;
            if(maxJump == prevJump) break;
            prevJump = maxJump;

            start = step;
            end = maxJump + 1;
        }
        return false;
    }

    bool canJump(vector<int>& nums){
        int end = 0;
        int maxPos = 0;
        int n = nums.size();
        for (int i = 0; i <= n - 1; i++){
            //num[i] + i is reached max distance ,get the greatest one in this range
            maxPos = max(nums[i] + i, maxPos);
            if(maxPos >= n - 1) return true;
            if (i == end) {//if reach the end
                if(end == maxPos && maxPos < n - 1) break;
                end = maxPos; // record the next end; 
            }
        }
        return false;
    }

    bool canJump(vector<int>& nums){
        int maxlen = 0; // ��ǰ����������Զ�±�
        for(int i=0; i<nums.size(); ++i){
            if(i>maxlen) return false; // ��ǰ�������±곬����֮ǰ����������Զ�±괦
            maxlen = nums[i]+i > maxlen ? nums[i]+i : maxlen; // �ڵ�ǰ�ڵ����maxlen
            if(maxlen>=nums.size()) return true;
        }
        return true;
    }
    //genius
    bool canJump(vector<int>& nums) {
        int k = 0;
        for (int i = 0; i < nums.size(); i++){
            if (i > k) return false;
            k = max(k, i + nums[i]);
        }
        return true;
    }
};

//official solution by leetcode
class Solution {
public:
//----------------------------------------------------------------------
    //����ģ��ӵ�һ��λ���������λ�õ����з������ӵ�һ��λ�ÿ�ʼ��ģ�����п���������λ�ã�
    //Ȼ��ӵ�ǰλ���ظ�������������û�а취��������ʱ��
    bool canJump(vector<int>& nums) {
        return canJumpFromPosition(0, nums);
    }
    
    bool canJumpFromPosition(int position, vector<int>& nums){
        if(position == nums.size() - 1) {
            return true;
        }
        
        int furthestJump = min(position + nums[position],  (int)nums.size() - 1);
        //FAST in some situation,only recurse if postion jump length is great than current postion
        //for(int nextPosition = furthestJump; nextPosition > position; nextPosition--)
        //in position jump max range, recurse
        for(int nextPosition = position + 1; nextPosition <= furthestJump; nextPosition++){
            if(canJumpFromPosition(nextPosition, nums)){
                return true;
            }
        }
        return false;
    }
    //----------------------------------------------------------------------
    // �Զ����µĶ�̬�滮�������ɻ��ݷ���һ���Ż������Ƿ��ֵ�һ�������Ѿ���ȷ��Ϊ�� / ��֮��
    // ����Ͳ���ı��ˣ�����ζ�����ǿ��Լ�¼��������ÿ�β������¼���
    enum Index {GOOD, BAD, UNKOWN};
    vector<Index> memo;
    bool canJumpFromPosition(int position, vector<int>& nums, vector<Index>& memo){
        
        if(memo[position] != UNKOWN){
            return memo[position] == GOOD ? true : false;
        }
        int furthestJump = min(position + nums[position], (int)nums.size() - 1);
        for(int nextPosition = position + 1; nextPosition <= furthestJump; nextPosition++){
            if(canJumpFromPosition(nextPosition, nums)){
                memo[position] = GOOD;
                return true;
            }
        }
        memo[position] = BAD;
        return false;
    }
    
    bool canJump(vector<int>& nums) {
        vector<Index> memo(nums.size(), UNKOWN);
        
        memo[memo.size() - 1] = GOOD;
        return canJumpFromPosition(00, nums, memo);
    }
    //----------------------------------------------------------------------
    //�����е�ÿ��Ԫ�أ�����Ϊ i����Ҫ�����ұ����ڵ� nums[i] ��Ԫ�ز����Ƿ��� GOOD
    bool canJump(vector<int>& nums) {
        vector<Index> memo(nums.size(), UNKOWN);
        memo[memo.size() - 1] = GOOD;
        
        for(int i = nums.size() - 2; i >= 0; i--){
            int furthestJump = min(i + nums[i], (int)nums.size() - 1);
            for(int j = i + 1; j < furthestJump; j++){
                if(memo[j] == GOOD){
                    memo[i] = GOOD;
                }
            }
        }
        return memo[0] == GOOD;
    }
    
    //----------------------------------------------------------------------
    /**
    * ��ĳ��λ�ó���������ֻ��Ҫ�ҵ���һ�����Ϊ GOOD �����꣨������ѭ���������ɵã���
    * Ҳ����˵�ҵ�����ߵ��Ǹ����ꡣ���������һ�������ı�������¼����ߵ� GOOD λ�ã�
    * ���ǾͿ��Ա��������������飬��������ʡ������ memo ���顣
    *
    * �����������������ÿ���ڵ����Ǽ���Ƿ����һ����Ծ���Ե��� GOOD ��λ��
    * ��currPosition + nums[currPosition] >= leftmostGoodIndex����������Ե��
    * ��ǰλ��Ҳ���Ϊ GOOD ��ͬʱ�����λ�ý���Ϊ�µ�����ߵ� GOOD λ�ã�
    * һֱ�ظ�������Ŀ�ͷ�������һ��������Ϊ GOOD ��ζ�ſ��Դӵ�һ��λ����������λ�á�
    **/
    //greedy strategy
    bool canJump(vector<int>& nums) {
        int lastPos = nums.size() - 1;
        for(int i = nums.size() - 1; i >= 0; i--){
            if(i + nums[i] >= lastPos){
                lastPos = i;
            }
        }
        return lastPos == 0;
    }
};