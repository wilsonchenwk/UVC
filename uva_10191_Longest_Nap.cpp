#include <bits/stdc++.h>
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE    
#include <gmock/gmock.h>
#endif

#define  HourtoMinutes   60

class Schedule
{
public:
    void add(const std::string &in)
    {
        uint32_t from_time,to_time;

        from_time = std::stoi (in.substr(0,2)) * HourtoMinutes; //hour to mins
        from_time += std::stoi (in.substr(3,2));   
        to_time = std::stoi (in.substr(6,2))*HourtoMinutes; //hour to mins
        to_time += std::stoi (in.substr(9,2));
        vec_schedule.push_back((from_time << 16) | to_time);
        dirty = 1;
    }

    std::pair<uint32_t, uint32_t> get_longest_minutes_pair()
    {
        if(dirty)
        {
            std::sort(vec_schedule.begin(),vec_schedule.end());
            longest_begin = day_start_minutes;
            longest_nap = (vec_schedule[0] >> 16) - longest_begin;

            for(uint32_t i =1;i<vec_schedule.size();i++)
            {
                uint32_t s_begin = (vec_schedule[i-1] & 0xFFFF);
                uint32_t nap = (vec_schedule[i] >> 16) - s_begin;
                if(nap > longest_nap)
                {
                    longest_nap = nap;
                    longest_begin = s_begin;
                }
            }
            uint32_t s_end = vec_schedule.back() & 0xFFFF;
            uint32_t final_nap  = day_end_minutes -  s_end;
            if(longest_nap < final_nap){
                longest_nap = final_nap;
                longest_begin = s_end;
            }
            dirty = 0;
        }
        return std::make_pair(longest_begin,longest_nap);
    }

private:
    std::vector<uint32_t> vec_schedule;
    uint32_t longest_nap;
    uint32_t longest_begin;
    const uint32_t day_start_minutes = (10*HourtoMinutes);
    const uint32_t day_end_minutes = (18*HourtoMinutes);
    int dirty;
};
int solve_uva_problem(std::istream &is,std::ostream &os)
{
    int day_cnt = 1;
    std::string str_val;
    while (std::getline(is,str_val)) {
        auto line_num = stoi(str_val);
        if(line_num == 0)
            return 0;

        Schedule p_schedule;

        while(line_num--)
        {
            std::string str_line;
            std::getline(is,str_line);
            p_schedule.add(str_line);
        }
        std::pair<uint32_t, uint32_t> longest = p_schedule.get_longest_minutes_pair();
        // Day #2: the longest nap starts at 15:00 and will last for 1 hours and 45 minutes.
        // Day #3: the longest nap starts at 17:15 and will last for 45 minutes.

        os << "Day #"<<day_cnt++<<": the longest nap starts at ";
        os << (longest.first/HourtoMinutes) <<":";
        os << std::setw(2) << std::setfill('0') << (longest.first%HourtoMinutes);
        os << " and will last for ";
        if(longest.second / HourtoMinutes)
            os << (longest.second / HourtoMinutes)<<" hours and ";
        os << (longest.second  % HourtoMinutes)<<" minutes."<<std::endl;
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