#include <bits/stdc++.h>
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE    
#include <gmock/gmock.h>
#endif
using namespace std;

class result_format
{
public:   
  result_format(char a, char b) : ch(a), balance(b) 
  {
  }
char  ch;
char balance;
};

class  Balance_Checker_608
{
public:
#define map_size  12
void result_output(std::ostream &os)
{
    for (const auto &res : res_out){
        os<< res.ch << " is the counterfeit coin and it is ";
        if(res.balance > 0)
            os<<"heavy.";
        else
            os<<"light.";

        os<<endl;           
   }
}
bool cases_input_then_check(std::istream &is)
{

    int case_num;
    is>>case_num;
    while(case_num--)
    {
    
        bool even_map[map_size]={false};
        int8_t up_down_map[map_size]={0};
        std::vector<int8_t> balance_result;
        int max_cnt=0;
        for(auto line_num=0;line_num<3;line_num++)  //one coin is counterfeit,will always be uniquely determined
        {  
            std::string l_str,r_str,result;
            is>>l_str;
            is>>r_str;
            is>>result;
            
            if(strncmp(result.c_str(),"even",strlen("even")) == 0){
                for (auto &ch : l_str)
                    even_map[ch-'A'] = true;
                for (auto &ch : r_str)
                    even_map[ch-'A'] = true;
            }
            else{
                max_cnt++;
                if(strncmp(result.c_str(),"up",strlen("up"))== 0){
                    balance_result.push_back(1);        
                    for (const auto &ch : l_str)
                        up_down_map[ch-'A']++;
                    for (const auto &ch : r_str)
                        up_down_map[ch-'A']--;
                }
                else{
                    balance_result.push_back(-1);   
                    for (auto &ch : l_str)
                        up_down_map[ch-'A']--;
                    for (auto &ch : r_str)
                        up_down_map[ch-'A']++;       
                }
                        
            }
        }
        uint8_t candidate0,candidate1;
        int check_cnt0=0,check_cnt1=0;
        for(auto i=0;i<map_size;i++)
        {
            if(even_map[i]==false)
            {
                if(up_down_map[i]!=0)
                {
                    candidate0 = i;
                    check_cnt0++;

                    if(up_down_map[i]==max_cnt || up_down_map[i]==-max_cnt){
                        candidate1 = i;
                        check_cnt1++;    
                    }

                }
            }
        }
    
        if(check_cnt0 == 1){
            res_out.push_back({(char)('A'+candidate0),up_down_map[candidate0]});
        }
        else if(check_cnt1 == 1)
        {
            res_out.push_back({(char)('A'+candidate1),up_down_map[candidate1]});
        }
        else
            return false; 
    }
    return true;
}
private:
     std::vector<result_format> res_out;
}; 

int solve_uva_problem(std::istream &is,std::ostream &os)
{
    
    while(1)
    {
        Balance_Checker_608  sally;
        if(!sally.cases_input_then_check(is))
            break;
        sally.result_output(os);
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

#endif