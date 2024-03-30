#include <string>
#include <vector>
#include <iostream>
using namespace std;
string longestCommonPrefix(vector<string> &strs)
{
    string res = strs[0];
    for (int i = 1; i < strs.size(); i++)
    {
        int len = res.size();
        if (len > strs[i].size())
            len = strs[i].size();
        int j = 0;
        for (j = 0; j < len; j++)
        {
            if (res[j] != strs[i][j])
                break;
        }
        res = res.substr(0, j);
    }
    return res;
}

int main()
{
    vector<string> strs = {"flower", "flow", "flight"};
    string res = longestCommonPrefix(strs);
    std::cout << res << std::endl;
    return 0;
}