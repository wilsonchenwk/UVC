#include <bits/stdc++.h>
// #define ONLINE_JUDGE
#ifndef ONLINE_JUDGE    
#include <gmock/gmock.h>
#endif


int solve_uva_problem(std::istream &is,std::ostream &os)
{
    int n;
    int day_cnt = 1;
    std::string str_val;
    while (std::getline(is,str_val)) {
        auto line_num = stoi(str_val);
        if(line_num == 0)
            return 0;

        std::vector<uint32_t> schedule;

        while(line_num--)
        {
            std::string str_line;
            std::getline(is,str_line);
            uint32_t from_time,to_time;

            from_time = std::stoi (str_line.substr(0,2)) * 60; //hour to mins
            from_time += std::stoi (str_line.substr(3,2));   
            to_time = std::stoi (str_line.substr(6,2))*60; //hour to mins
            to_time += std::stoi (str_line.substr(9,2));
            schedule.push_back((from_time << 16) | to_time);
        }
        std::sort(schedule.begin(),schedule.end());

        uint32_t longest_begin = (10*60);
        uint32_t longest_nap = (schedule[0] >> 16) - (longest_begin);

        for(auto i =1;i<schedule.size();i++)
        {
            uint32_t begin = (schedule[i-1] & 0xFFFF);
            uint32_t nap = (schedule[i] >> 16) - begin;
            if(nap > longest_nap)
            {
                longest_nap = nap;
                longest_begin = begin;
            }
        }
        uint32_t final_begin = schedule.back() & 0xFFFF;
        uint32_t final_nap  = (18*60) -  final_begin;
        if(longest_nap < final_nap){
            longest_nap = final_nap;
            longest_begin = final_begin;
        }
        // Day #2: the longest nap starts at 15:00 and will last for 1 hours and 45 minutes.
        // Day #3: the longest nap starts at 17:15 and will last for 45 minutes.

        os << "Day #"<<day_cnt++<<": the longest nap starts at ";
        os << (longest_begin/60) <<":";
        os << std::setw(2) << std::setfill('0') << (longest_begin%60);
        os << " and will last for ";
        if(longest_nap / 60)
            os << (longest_nap / 60)<<" hours and ";
        os << (longest_nap % 60)<<" minutes."<<std::endl;
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

// 17
// 7 6 60 70 78 44 86 21 7 11 33 44 93 87 68 72 92 
#ifndef ONLINE_JUDGE
TEST(uva_test, uva_test1)
{
    std::istringstream iss(
        "4\n"\
        "10:00 12:00 Lectures\n"\
        "13:00 15:00 Boring lectures...\n"\
        "15:30 17:45 Reading\n"\
        "12:00 13:00 Lunch, like always.\n"\
        "0\n");
    std::ostringstream oss;

    solve_uva_problem(iss, oss);
    EXPECT_EQ("Day #1: the longest nap starts at 15:00 and will last for 30 minutes.\n",oss.str());
}

TEST(uva_test, uva_test2)
{
    std::istringstream iss(
        "1\n"\
        "15:30 17:45 Reading\n"\
        "0\n");
    std::ostringstream oss;

    solve_uva_problem(iss, oss);
    EXPECT_EQ("Day #1: the longest nap starts at 10:00 and will last for 5 hours and 30 minutes.\n",oss.str());
}

TEST(uva_test, uva_test3)
{
    std::istringstream iss(
        "1\n"\
        "12:00 13:00 Lunch, like always.\n"\
        "0\n");
    std::ostringstream oss;

    solve_uva_problem(iss, oss);
    EXPECT_EQ("Day #1: the longest nap starts at 13:00 and will last for 5 hours and 0 minutes.\n",oss.str());
}
#endif