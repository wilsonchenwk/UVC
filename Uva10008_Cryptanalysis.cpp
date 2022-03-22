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
        vector<pair<char, int>> result(26);
        
        //initial vector of pairs from A to Z
        for(uint8_t i=0;i < 26;i++)
            result[i] = make_pair(i+'A',0);   

        while(line_num)
        {
            std::string str_line;
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


#ifndef ONLINE_JUDGE
TEST(uva_test, uva_test1)
{
    std::istringstream iss(
        "3\n"\
        "This is a test.\n"\
        "Count me 1 2 3 4 5.\n"\
        "Wow!!!! Is this question easy?\n"\
        );
    std::ostringstream oss;

    solve_uva_problem(iss, oss);
    EXPECT_EQ(
                "S 7\n"\
                "T 6\n"\
                "I 5\n"\
                "E 4\n"\
                "O 3\n"\
                "A 2\n"\
                "H 2\n"\
                "N 2\n"\
                "U 2\n"\
                "W 2\n"\
                "C 1\n"\
                "M 1\n"\
                "Q 1\n"\
                "Y 1\n"\
                ,oss.str());
}
#endif