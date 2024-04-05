#include <iostream>
#include <string>
#include <unordered_set>
#include <queue>
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

    vector<int> topKFrequent_sort(vector<int> &nums, int k)
    {
        unordered_map<int, int> cnts;
        for (int i = 0; i < nums.size(); i++)
        {
            if (cnts.count(nums[i]) == 0)
                cnts[nums[i]] = 1;
            else
                cnts[nums[i]] += 1;
        }
        vector<pair<int, int>> pairs(cnts.begin(), cnts.end());
        sort(pairs.begin(), pairs.end(),
             [](pair<int, int> &a, pair<int, int> &b) -> bool
             { return a.second > b.second; });
        vector<int> res(k);
        for (int i = 0; i < k; i++)
        {
            res[i] = pairs[i].first;
        }
        return res;
    }

    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> cnts;
        for (int i = 0; i < nums.size(); i++)
        {
            if (cnts.count(nums[i]) == 0)
                cnts[nums[i]] = 1;
            else
                cnts[nums[i]] += 1;
        }

        // 优先队列
        auto cmp = [](pair<int, int> &a, pair<int, int> &b) -> bool
        { return a.second > b.second; };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
        for (auto &p : cnts)
        {
            pq.push(p);
            if (pq.size() > k)
                pq.pop();
        }
        vector<int> res(k);
        for (int i = 0; i < k; i++)
        {
            res[i] = pq.top().first;
            pq.pop();
        }

        return res;
    }
};

int main(int argc, char const *argv[])
{
    Solution s;
    // cout << s.lengthOfLongestSubstring("au") << endl;
    vector<int> inputs{1, 1, 1, 2, 2, 3};
    auto res = s.topKFrequent(inputs, 2);
    for (auto i : res)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
