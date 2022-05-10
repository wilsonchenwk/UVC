#include <bits/stdc++.h>
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE    
#include <gmock/gmock.h>
#endif

class Tains_514
{
public:
    Tains_514(int N) //constructor
    {
        for(auto i=1;i<=N;i++)
            trains_A.push(i);   
    }
    bool output_specified_train(int train_no)
    {
        //find in A
        if(!trains_A.empty() && trains_A.front()<=train_no){
            while(trains_A.front()< train_no)
            {
                trains_Station.push_back(trains_A.front());
                trains_A.pop();
            }
            trains_A.pop();   
            return true;
        }

        //find in station
          if(!trains_Station.empty() && trains_Station.back()==train_no){
            trains_Station.pop_back();
            return true;
        }

        return false;
    }
    bool empty(void)
    {
        return trains_A.empty() && trains_Station.empty();
    }
private:
    std::vector<int> trains_Station;
    std::queue<int>  trains_A;
    // std::queue<int>  trains_B;
};
int solve_uva_problem(std::istream &is,std::ostream &os)
{
    std::string str_val;
    while (std::getline(is,str_val)) {
        auto num = stoi(str_val);
        if(num == 0)
            return 0;
        
        while(1)
        {
            std::string str_line;
            std::getline(is,str_line);
            if(std::stoi(str_line) == 0)
                break;
            
            Tains_514 train(num);
            std::string::size_type idx = 0,sz;
            for(auto i=0;i<num;i++)
            {
                // os<< std::stoi(&str_line[idx],&sz) << std::endl;
                if(!train.output_specified_train(std::stoi(&str_line[idx],&sz)))
                    break;
                idx+=sz;
            }
        
            if(train.empty())
                os<<"Yes"<<std::endl;
            else
                os<<"No"<<std::endl;
            
        }
        os<<std::endl;
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
