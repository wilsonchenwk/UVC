#include <bits/stdc++.h>
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE    
#include <gmock/gmock.h>
#endif

using namespace std;

bool comp_cnt_desc_alphabet(const pair<char, int> &a, const pair<char, int> &b)
{
	return (a.second > b.second) || 
        ((a.second == b.second) && (a.first < b.first));
}

int solve_uva_problem(istream &is,ostream &os)
{
    std::string str_val;
    while (getline(is,str_val)) {
        uint32_t line_num = stoi(str_val);
        std::string str_line;
        vector<pair<char, int>> result(26);
        
        //initial vector of pairs from A to Z
        for(uint8_t i=0;i < 26;i++)
            result[i] = make_pair(i+'A',0);   

        while(line_num)
        {
            getline(is,str_line);
            for(uint32_t i=0;i<str_line.length();i++)
            {
                const char l = str_line[i];
                if (l>='a' && l<='z')
                {
                    result[l-'a'].second=result[l-'a'].second+1;
                }
                else if (l>='A' && l<='Z')
                {
                     result[l-'A'].second=result[l-'A'].second+1;
                }
            }
            line_num--;
        }


        sort(result.begin(), result.end(), comp_cnt_desc_alphabet);

        for(auto i=0;i<26 && result[i].second;i++)
            os<<result[i].first << " " << result[i].second << endl;
       
    }
    return 0;
}

int main(int argc, char** argv)
{
#ifdef ONLINE_JUDGE
    return solve_uva_problem(std::cin, std::cout);
#else    
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
#endif    
}

