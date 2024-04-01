#include <iostream>
#include <vector>
#include <functional>
using namespace std;

class Solution
{
public:
    vector<int> findDisappearedNumbers(vector<int> &nums)
    {

        vector<int> res;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] != i + 1)
                res.push_back(nums[i]);
        }
        return res;
    }

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
            else if (left_sum + nums[l] == right_sum + nums[r])
            {
                left_sum += nums[l++];
                right_sum += nums[r--];
            }
        }
        if (left_sum != right_sum)
            return -1;
        return l;
    }

    vector<int> findDiagonalOrder(vector<vector<int>> &mat)
    {
        vector<int> res;
        int m = mat.size(), n = mat[0].size();
        res.reserve(m * n);
        bool reverse = true;
        for (int j = 0; j < n; j++)
        {
            if (reverse)
            {
                int y = j, x = 0;
                if (j > m - 1)
                    y = m - 1, x = j - y;
                while (x >= 0 && x < n && y < m && y >= 0)
                {
                    res.push_back(mat[y][x]);
                    x += 1;
                    y -= 1;
                }
            }
            else
            {
                int y = 0, x = j;
                while (x >= 0 && x < n && y < m && y >= 0)
                {
                    res.push_back(mat[y][x]);
                    x -= 1;
                    y += 1;
                }
            }
            reverse = !reverse;
        }
        for (int i = 1; i < m; i++)
        {
            if (reverse)
            {
                int sum = i + n - 1;
                int y = std::min(sum, m - 1), x = sum - y;
                while (x >= 0 && x < n && y < m && y >= 0)
                {
                    res.push_back(mat[y][x]);
                    x += 1;
                    y -= 1;
                }
            }
            else
            {
                int y = i, x = n - 1;
                while (x >= 0 && x < n && y < m && y >= 0)
                {
                    res.push_back(mat[y][x]);
                    x -= 1;
                    y += 1;
                }
            }
            reverse = !reverse;
        }
        return res;
    }

    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        int offset = 0;
        int x_go[4] = {1, 0, -1, 0};
        int y_go[4] = {0, 1, 0, -1};
        vector<int> res;
        int m = matrix.size(), n = matrix[0].size();
        res.reserve(m * n);

        function<bool(int const, int const)> bounds[4] = {
            [&](int const x, int const y) -> bool
            {
                return x < n - offset;
            },
            [&](int const x, int const y) -> bool
            {
                return y < m - offset;
            },
            [&](int const x, int const y) -> bool
            {
                return x >= offset;
            },
            [&](int const x, int const y) -> bool
            {
                return y >= offset;
            },
        };
        int iter = 0;
        int x = 0, y = 0;
        while (res.size() < m * n)
        {

            res.push_back(matrix[y][x]);
            if (!bounds[iter](x + x_go[iter], y + y_go[iter]))
            {
                iter = (iter + 1) % 4;
                if (iter == 3)
                    offset += 1;
            }
            x += x_go[iter];
            y += y_go[iter];
        }
        return res;
    }

    int strStr(string haystack, string needle)
    {
        int n_i = 0;
        for (int i = 0; i < haystack.size(); i++)
        {
            if (haystack[i] == needle[n_i])
            {
                int h_i = i;
                while (haystack[++h_i] == needle[++n_i])
                    ;
                if (n_i == needle.size())
                    return i;
                else
                    n_i = 0;
            }
        }
        return -1;
    }

    int minSubArrayLen(int target, vector<int> &nums)
    {
        int res = nums.size() + 1;

        int s = 0;
        int sum = 0;
        for (int e = 0; e < nums.size(); e++)
        {
            sum += nums[e];
            while (sum >= target)
            {
                res = std::min(res, e - s + 1);
                sum -= nums[s++];
            }
        }
        return res == nums.size() + 1 ? 0 : res;
    }

    void rotate(vector<int> &nums, int k)
    {
        k = k % nums.size();
        if (k == 0)
            return;
        vector<int> tmp(k);
        int l_k = nums.size() - k;
        for (int i = 0; i < k; i++)
            tmp[i] = nums[l_k + i];
        for (int i = nums.size() - 1; i >= k; i--)
        {
            nums[i] = nums[i - k];
        }
        for (int i = 0; i < k; i++)
            nums[i] = tmp[i];
    }

    string reverseWords(string s)
    {
        int l = 0, p_l = -1;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] != ' ')
            {
                if (p_l == -1)
                    p_l = l;
                s[l++] = s[i];
            }
            else if (p_l != -1)
            {
                s[l] = ' ';
                std::reverse(s.begin() + p_l, s.begin() + l++);
                p_l = -1;
            }
        }
        if (p_l != -1)
            std::reverse(s.begin() + p_l, s.begin() + l);
        else
            l--;
        s = s.substr(0, l);
        std::reverse(s.begin(), s.end());
        return s;
    }
};

int main(int argc, char const *argv[])
{
    Solution s;

    // // test pivotIndex
    // vector<int> nums = {-1, -1, -1, -1, -1, 0};
    // std::reverse(nums.begin(), nums.end());
    // cout << s.pivotIndex(nums) << endl;

    // test findDiagonalOrder
    // vector<vector<int>> mat = {{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}};
    // vector<int> res = s.findDiagonalOrder(mat);
    // for (auto i : res)
    //     cout << i << " ";

    // test spiralOrder
    // vector<vector<int>> mat = {{1, 2, 3, 4},
    //                            {5, 6, 7, 8},
    //                            {9, 10, 11, 12},
    //                            {13, 14, 15, 16}};
    // vector<int> res = s.spiralOrder(mat);
    // for (auto i : res)
    //     cout << i << " ";

    // test strStr
    // cout << s.strStr("sadbutsad", "sad") << endl;

    // test minSubArrayLen
    // vector<int> nums = {2, 16, 14, 15};
    // cout << s.minSubArrayLen(20, nums) << endl;

    // test rotate
    // vector<int> nums = {1, 2, 3, 4, 5};
    // s.rotate(nums, 3);
    // for (auto i : nums)
    //     cout << i << " ";

    // test reverseWords
    cout << s.reverseWords("a good   example") << "//" << endl;
    return 0;
}
