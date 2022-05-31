#include <bits/stdc++.h>
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE    
#include <gmock/gmock.h>
#endif

const std::vector<std::string> best_hands{"straight-flush", "four-of-a-kind", \
"full-house", "flush", "straight", "three-of-a-kind", "two-pairs", "one-pair", "highest-card"};

class Poker_131
{
public:
    Poker_131() //constructor
    {
        poker_cards.resize(10);
    }
    bool round_init(std::istream &is)
    {
        int i = 0;
        while(std::getline(is, poker_cards[i++],' ')  && i<10);

        if(i==10)
            return true;
        else    
            return false;
    }
private:
    std::vector<std::string> poker_cards;
};
int solve_uva_problem(std::istream &is,std::ostream &os)
{
    Poker_131 player;
    while(1)
    {
        if(!player.round_init(is))
            break;
    }
        os<<std::endl;
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

    char value;
    char suit;
};

class Poker_131
{
public:
    Poker_131() //constructor
    {
        poker_cards.resize(10);
    }
    bool round_init(std::istream &is)
    {
        int i = 0;
        while(std::getline(is, poker_cards[i++],' ')  && i<10);

        if(i==10)
            return true;
        else    
            return false;
    }
private:
    std::vector<std::string> poker_cards;
};
int solve_uva_problem(std::istream &is,std::ostream &os)
{
    Poker_131 player;
    while(1)
    {
        if(!player.round_init(is))
            break;
    }
        os<<std::endl;
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
