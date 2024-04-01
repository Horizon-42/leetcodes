#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    int pivotIndex(vector<int> &nums)
    {
        if (nums.size() == 1)
            return 0;
        int left_sum = 0, right_sum = 0;
        int l = 0, r = nums.size() - 1;
        while (l < r)
        {
            if (left_sum + nums[l] < right_sum + nums[r])
                left_sum += nums[l++];
            else if (left_sum + nums[l] > right_sum + nums[r])
                right_sum += nums[r--];
            else
            {
                left_sum += nums[l++];
                right_sum += nums[r--];
            }
        }
        if (left_sum != right_sum)
            return -1;
        return l;
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
