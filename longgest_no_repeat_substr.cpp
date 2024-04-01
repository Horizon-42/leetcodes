#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

class Solution1
{
public:
    bool has_no_repeat(string const &s)
    {
        unordered_set<char> check;
        for (auto c : s)
        {
            if (check.count(c) > 0)
                return false;
            check.insert(c);
        }
        return true;
    }
    int lengthOfLongestSubstring(string s)
    {
        const int s_len = s.size();
        int w_size = s_len;
        while (w_size > 1)
        {
            for (int i = 0; i + w_size <= s_len; i++)
            {
                if (has_no_repeat(s.substr(i, w_size)))
                    return w_size;
            }
            w_size--;
        }
        return 1;
    }
};

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        if (s.size() < 2)
            return s.size();
        // 滑窗算法
        int last_seen[256];
        memset(last_seen, -1, sizeof(last_seen));
        int max_len = 0;
        int l = 0;
        for (int r = 0; r < s.size(); r++)
        {
            if (last_seen[s[r]] != -1)
            {
                if (last_seen[s[r]] < l)
                    last_seen[s[r]] = -1;
                else
                {

                    l = last_seen[s[r]] + 1;
                }
            }
            max_len = max(max_len, r - l + 1);
            last_seen[s[r]] = r;
        }
        return max_len;
    }
};

int main(int argc, char const *argv[])
{
    Solution s;
    cout << s.lengthOfLongestSubstring("au") << endl;
    return 0;
}
