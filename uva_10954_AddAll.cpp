#include <bits/stdc++.h>
// #define ONLINE_JUDGE
#ifndef ONLINE_JUDGE    
#include <gmock/gmock.h>
#endif


int solve_uva_problem(std::istream &is,std::ostream &os)
{
    int n;
    
    while (is>>n) {
        std::vector<uint32_t> vec_numbers;
        if(n == 0)
            return 0;
        
        for(auto i=0;i< n;i++)
        {
            uint32_t val;
            is >> val;
            vec_numbers.push_back(val);
        }

        std::sort(vec_numbers.begin(), vec_numbers.end(),std::greater<uint32_t>());
        uint64_t total_sum = 0;
        auto i = vec_numbers.size() - 1;
        while(i)
        {
            const auto val = vec_numbers[i];   
            if(val > vec_numbers[i - 1]) // re-sort
            {
                          
                vec_numbers.pop_back();
                uint32_t l=0,r = i,mid=(l+r)/2;
                //find insert index
                if(val >=vec_numbers[0])
                {
                    vec_numbers.insert(vec_numbers.begin(),val);   
                }
                else
                { 
                    while(mid >l)
                    {
                        if(vec_numbers[mid] < val)
                        {   
                            r= mid;
                            mid=(l+r)/2;
                        }
                        else
                        {   
                            l=mid;
                            mid=(l+r)/2  ;
                        }
                    }     
                    vec_numbers.insert(vec_numbers.begin()+mid + 1,val);  
                } 
            } 
            vec_numbers[i - 1] += vec_numbers[i];
            total_sum +=  vec_numbers[i - 1] ; 
            i--;
            vec_numbers.pop_back();
              
        }           
        os << total_sum << std::endl;
    }
    return 0;
}

int solve_uva_problem2(std::istream &is,std::ostream &os){
	
	int n;
	while (is >> n)
	{
		if (!n)
		{
			break;
		}
		std::priority_queue<uint32_t, std::vector<uint32_t>, std::greater<uint32_t>> q;
		for (int i = 0; i < n; i++)
		{
			uint32_t val;
            is >> val;
			q.push(val);
		}
		uint64_t total_sum = 0;
		while (1)
		{
			int sum;
            sum = q.top();
			q.pop();
			if (q.empty())
			{
				break;
			}
			sum += q.top();
			q.pop();
			total_sum += sum;
			q.push(sum);
		}
		os << total_sum << std::endl;
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
        "17\n"\
        "7 6 60 70 78 44 86 21 7 11 33 44 93 87 68 72 92\n"\
        "0\n");
    std::ostringstream oss;

    solve_uva_problem(iss, oss);
    EXPECT_EQ("3349\n",oss.str());
}

TEST(uva_test, uva_test2)
{
    std::istringstream iss(
        "2\n"\
        "56 91\n"\
        "0\n");
    std::ostringstream oss;

    solve_uva_problem(iss, oss);
    EXPECT_EQ("147\n",oss.str());
}
#endif