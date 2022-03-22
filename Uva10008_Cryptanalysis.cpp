#include <bits/stdc++.h>
// #define ONLINE_JUDGE
#ifndef ONLINE_JUDGE    
#include <gmock/gmock.h>
#endif

using namespace std;

bool comp_cnt_desc_alphabet(const pair<char, int> &a, const pair<char, int> &b)
{
	return (a.second > b.second) || 
        ((a.second == b.second) && (a.first < b.first));
}

int solve_uva_problem(std::istream &is,ostream &os)
{
    std::string str_val;
    while (std::getline(is,str_val)) {
        auto line_num = stoi(str_val);
        std::vector<pair<char, int>> result(26);
        
        //initial vector of pairs from A to Z
        for(auto i=0;i < 26;i++)
            result[i] = std::make_pair(i+'A',0);   

        while(line_num)
        {
            std::string str_line;
            std::getline(is,str_line);
            
            for (const auto &l : str_line) 
            {
                if (l >='a' && l <='z')
                {
                    result[l-'a'].second ++;
                }
                else if (l>='A' && l<='Z')
                {
                     result[l-'A'].second++ ;
                }    
            }
            line_num--;
        }
        std::sort(result.begin(), result.end(), comp_cnt_desc_alphabet);

         for (const auto &res : result) 
         {
            if(!res.second)
                break;
            os<<res.first << " " << res.second << endl;
         }
       
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