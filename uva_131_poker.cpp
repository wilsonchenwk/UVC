#include <bits/stdc++.h>
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE    
#include <gmock/gmock.h>
#endif
using namespace std;

const std::vector<std::string> hand_name_table={
"highest-card",
"one-pair",
"two-pairs",
"three-of-a-kind",
"straight",
"flush",
"full-house",
"four-of-a-kind",
"straight-flush"
};

enum HAND_NAME_ENUM { 
hi_card = 0, 
one_pair, 
two_pairs,  
three_a_kind,
straight,
_flush,
full_house, 
four_a_kind, 
straight_flush
};

std::unordered_map<std::string, int> poker_num_map = {{"A", 1},{"2", 2},{"3", 3},{"4", 4},{"5", 5},{"6", 6},{"7", 7},\
                                            {"8", 8},{"9", 9},{"T", 10},{"J", 11},{"Q", 12},{"K", 13}};
std::unordered_map<std::string, int> poker_suit_map = {{"C", 0},{"D", 1},{"H", 2},{"S", 3}};

#define P_NUM_INT(str)   poker_num_map[str.substr(0,1)]
#define P_NUM_STR(str)   str.substr(0,1)
#define P_SUIT_INT(str)  poker_suit_map[str.substr(1,1)]
#define P_SUIT_STR(str)  str.substr(1,1)
class Poker_131
{
public:
    Poker_131() //constructor
    {
        round_cards.resize(10);
        init_done = false;
    }
    bool round_init(std::istream &is,std::ostream &os) // true:ok  false:fail
    {
        int i = 0;
        best_hand_num = hi_card;
        check_done = false;
        while(std::getline(is, round_cards[i],' '))
        {
            if(++i == 9){
            std::getline(is, round_cards[i++]);    
                break;
            }
        }
        if(i==10){
            os<<"Hand: ";    
            for(i=0;i<5;i++)
            {
                os<<round_cards[i]<<" ";  
            }
            os<<"Deck: ";
            for(i=5;i<10;i++)
            {
                os<<round_cards[i]<<" ";  
            }

            init_done = true;
            check_done = false;
            return true;
        }
        else{
            init_done = false;   
            return false;
        }
    }
    bool round_check(void) // true:ok  false:fail
    {
        if(!init_done)
            return false;
        for(int i=5;i<=10 && best_hand_num!=straight_flush;i++)
        {
            std::sort(round_cards.begin(), round_cards.begin()+i, [](const string &a, const string &b){
                    return P_NUM_INT(a) < P_NUM_INT(b); // 升序排列
            });
            HAND_NAME_ENUM hand =  find_best_hand(i);
            if(best_hand_num < hand)
                best_hand_num = hand;
        }
        check_done = true;
        return true;
    }
    bool result_output(std::ostream &os) // true:ok  false:fail
    {
        if(!check_done)
            return false;
        os<<"Best hand: "<<hand_name_table[best_hand_num]<<endl;    
        return true;
    }
private:
    std::vector<std::string> round_cards;
    HAND_NAME_ENUM best_hand_num;
    bool init_done;
    bool check_done;
    HAND_NAME_ENUM find_best_hand(int num) 
    {
        int conti_cnt = 1 , same_cnt = 1,sf_test=1;
        int p=0,k3=0,k4=0,f=0;
        int pre_diff_num = P_NUM_INT(round_cards[0]);
        int  suit_cnt[4]={1};
        bool  suit_on_flush_bit=0;
        bool  suit_on_straight_bit=0;
        for(int i =1;i<num;i++)
        {

            if(P_NUM_INT(round_cards[i]) == P_NUM_INT(round_cards[i-1]))
                same_cnt++;
            else
            {
                if(P_NUM_INT(round_cards[i]) == 1 + pre_diff_num)
                    conti_cnt++;
                else
                {
                    if(conti_cnt == 4 && (P_NUM_STR(round_cards[0]) =="A" &&  P_NUM_STR(round_cards[i])=="K")){
                        conti_cnt ++;        
                    }
                    else
                        conti_cnt = 1;           
                }
                pre_diff_num = P_NUM_INT(round_cards[i]);
                if(conti_cnt == 5)
                {
                    suit_on_straight_bit|= (1<<P_SUIT_INT(round_cards[i]));
                    conti_cnt = 1;
                }
                
                if(same_cnt==4){
                    k4++;
                }
                else if(same_cnt==3){
                    k3++;
                }
                else if(same_cnt==2){
                    p++;
                }
                same_cnt = 1;
            }
            if(P_SUIT_STR(round_cards[i]) ==  P_SUIT_STR(round_cards[i-1]))
            {    
                suit_cnt[P_SUIT_INT(round_cards[i])] ++;
                

            }
               
            if(suit_cnt[P_SUIT_INT(round_cards[i])] ==5)
                suit_on_straight_bit|= (1<<P_SUIT_INT(round_cards[i]));
            
        }
        if(conti_cnt == 4 && (P_NUM_STR(round_cards[0]) =="A" &&  P_NUM_STR(round_cards[9])=="K"))
        {    
            suit_on_straight_bit|= (1<<P_SUIT_INT(round_cards[0]));  
        }
                    
        if((suit_on_flush_bit & suit_on_straight_bit) && is_straight_flush(num,suit_on_flush_bit & suit_on_straight_bit))
            return straight_flush;
        if(k4)
            return four_a_kind;
        if(k3 && p)
            return full_house;
        if(suit_on_flush_bit)
            return _flush;
        if(suit_on_straight_bit)
            return straight;
        if(k3)
            return three_a_kind;
        if(p>=2)
            return two_pairs;
        else if(p)
            return one_pair;
        else
            return hi_card;              
    }   
    bool is_straight_flush(int num,int bit) 
    {
        int cnt = 1;

 
        if(cnt == 5)
            return true;
        else
            return false;       
    }

};
int solve_uva_problem(std::istream &is,std::ostream &os)
{
    Poker_131 player;
    while(1)
    {
        if(!player.round_init(is,os))
            break;
        player.round_check();
        player.result_output(os);
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
