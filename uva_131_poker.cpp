#include <bits/stdc++.h>
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE    
#include <gmock/gmock.h>
#endif
using namespace std;

const std::string hand_name_table[9]{
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

std::map<std::string, int> poker_num_map = {{"A", 1},{"2", 2},{"3", 3},{"4", 4},{"5", 5},{"6", 6},{"7", 7},\
                                            {"8", 8},{"9", 9},{"T", 10},{"J", 11},{"Q", 12},{"K", 13}};
std::map<std::string, int> poker_suit_map = {{"C", 1},{"D", 2},{"H", 3},{"S", 4}};

#define P_NUM_INT(str)   poker_num_map[str.substr(0,1)]
#define P_NUM_STR(str)   str.substr(0,1)
#define P_SUIT_INT(str)  poker_suit_map[str.substr(1,1)]
#define P_SUIT_STR(str)  str.substr(1,1)
class  Poker_Composite
{
public:
Poker_Composite()
{
    num_map.resize(13+1+1);
    suit_map.resize(4+1);
}
vector<uint8_t> num_map;
vector<uint8_t> suit_map;

}; 

class Poker_131
{
public:
    Poker_131() //constructor
    {
        round_cards.resize(10);
    }
    bool round_init(std::istream &is,std::ostream &os) // true:ok  false:fail
    {
        int i = 0;
        best_hand_num = hi_card;
        std::fill(hand_comp.num_map.begin(), hand_comp.num_map.end(), 0);
        std::fill(hand_comp.suit_map.begin(), hand_comp.suit_map.end(), 0);
        std::fill(deck_comp.num_map.begin(), deck_comp.num_map.end(), 0);
        std::fill(deck_comp.suit_map.begin(), deck_comp.suit_map.end(), 0);
        std::string line;
        std::getline(is, line);
        // if (line == "")
        //     return false;
        std::stringstream ss;
        ss << line;
        while(ss>> round_cards[i])
        {
            if(++i == 10)
                break;
        }
        if(i!=10)
        return false;
            os<<"Hand: ";    
            for(i=0;i<5;i++)
            {
                os<<round_cards[i]<<" ";
                hand_comp.num_map[P_NUM_INT(round_cards[i])]++;
                hand_comp.num_map[14] += (P_NUM_STR(round_cards[i]) =="A") * 1;
                hand_comp.suit_map[P_SUIT_INT(round_cards[i])]++;
            }
            os<<"Deck: ";
            for(i=5;i<10;i++)
            {
                os<<round_cards[i]<<" ";
                deck_comp.num_map[P_NUM_INT(round_cards[i])]++;
                deck_comp.num_map[14] += (P_NUM_STR(round_cards[i]) =="A") * 1;
                deck_comp.suit_map[P_SUIT_INT(round_cards[i])]++;  
            }
  
            return true;
        

    }
    bool round_check(void) // true:ok  false:fail
    {

        HAND_NAME_ENUM tmp= find_best_hand(deck_comp);
        best_hand_num = find_best_hand(hand_comp);
        if(best_hand_num<tmp)
            best_hand_num = tmp;    
        std::vector<std::string> deck_cards;
        for(int i=5;i<9 && best_hand_num!=straight_flush;i++)
        {
            hand_comp.num_map[P_NUM_INT(round_cards[i])]++;
            hand_comp.num_map[14] += (P_NUM_STR(round_cards[i]) =="A") * 1;
            hand_comp.suit_map[P_SUIT_INT(round_cards[i])]++;
            deck_cards.push_back(round_cards[i]);
            HAND_NAME_ENUM hand =  find_best_hand(hand_comp,&deck_cards,best_hand_num);
            if(best_hand_num < hand)
                best_hand_num = hand;
        }
        return true;
    }
    bool result_output(std::ostream &os) // true:ok  false:fail
    {

        os<<"Best hand: "<<hand_name_table[best_hand_num]<<endl;    
        return true;
    }
private:
    Poker_Composite hand_comp,deck_comp;
    std::vector<std::string> round_cards;
    HAND_NAME_ENUM best_hand_num;
    bool init_done;
    bool check_done;

    HAND_NAME_ENUM find_best_hand(Poker_Composite &total, std::vector<std::string>  *must =nullptr,HAND_NAME_ENUM current = (HAND_NAME_ENUM)hi_card) 
    {
        uint16_t i,j;
        int flush_idx=0,straight_begin=0,num_k4=0,k3_idx=0;
        vector<uint8_t> v_pair,v_k3;
        for(i=1;i<=14;i++)
        {
            if(total.num_map[i]==0)
                continue;
            else{
                if(i<14)    
                {    if(total.num_map[i]==2 )
                        v_pair.push_back(i);
                    else if(total.num_map[i]==3)
                        k3_idx = i;
                    else if(total.num_map[i]==4)
                        num_k4 = i;
                }
                if(straight_begin==0 && i<=10 && total.num_map[i] && total.num_map[i+1] && total.num_map[i+2]
                     && total.num_map[i+3] && total.num_map[i+4]){
                     straight_begin =i;            
                }
            }

        }
        int straight_end = straight_begin +4;
        while(straight_end < 14 && total.num_map[straight_end + 1])
        {
            straight_end++;
        }
        for(i=1;i<=4;i++)
        {
            if(total.suit_map[i]>=5)       
                flush_idx = i;
        }
        switch(current+1)
        {
            case(one_pair): //not completed
                if(v_pair.size()==1)
                {
                    if(must!=nullptr)
                    {
                        for(j=0;j<v_pair.size();j++)
                        {
                            if(P_NUM_INT(must->at(must->size()-1)) == v_pair[j])
                                current = one_pair; 
                        }
                        
                    }
                    else
                        current = one_pair;           
                }
            case(two_pairs): //not completed
                if(v_pair.size()==2)
                {
                    if(must!=nullptr)
                    {
                        int k=0;
                        int num=must->size() -1;
                        for(i=0;i<must->size();i++)
                        {
                                
                                for(j=0;j<v_pair.size();j++)
                                {
                                    if(P_NUM_INT(must->at(i)) == v_pair[j]){
                                        k++;
                                        break;
                                    }     
                                }
                        }
                        if(k>=num)
                             current = two_pairs;
                    }
                    else
                        current = two_pairs;
                }
            case(three_a_kind): //not completed
                if(k3_idx)
                {   
                    if(must!=nullptr)
                    {
                        int num=must->size() -2;
                        if(P_NUM_INT(must->at(must->size() -1)) == k3_idx)
                        {    
                            int k=0;
                            for(i=0;i<must->size();i++)
                            {
                                
                                if(P_NUM_INT(must->at(i)) == k3_idx)
                                    k++;
                            }
                            if(k>=num)
                                current = three_a_kind; 
                        }
                    }
                    else
                        current = three_a_kind;   
                }
            case(straight):
                if(straight_begin)
                {   
                    if(must!=nullptr)
                    {
                        for(i=0;i<must->size();i++)
                        {
                            if(P_NUM_INT(must->at(i)) > straight_end)       
                                break;
                            if(P_NUM_INT(must->at(i)) < straight_begin && !(straight_end==14 && P_NUM_INT(must->at(i))==1))       
                                break;
    
                            if(i==must->size()-1)
                                current = straight;   
                        }
                    }
                    else
                        current = straight;   
                }
            case(_flush):
                if(flush_idx)
                {   
                    if(must!=nullptr)
                    {
                        for(i=0;i<must->size();i++)
                        {
                            if(P_SUIT_INT(must->at(i)) != flush_idx)
                                break;
                            if(i==must->size()-1){
                                current = _flush;
                            }   
                        }        
                    }
                    else
                        current = _flush;   
                }
            case(full_house):
                if(k3_idx && v_pair.size())
                {   

                    if(must!=nullptr)
                    {
                        for(i=0;i<must->size();i++)
                        {
                            if(P_NUM_INT(must->at(i)) != k3_idx)       
                            {
                                int k=0;
                                for(j=0;j<v_pair.size();j++)
                                {
                                    if(P_NUM_INT(must->at(i)) == v_pair[i])
                                        k=1;
                                }
                                if(!k)
                                    break;
                            }
                            if(i==must->size()-1)
                                current = full_house;   
                        }
                    }
                    else
                        current = full_house ;           
                    
            
                }
            case(four_a_kind):
                if(num_k4)
                {   
                    if(must!=nullptr)
                    {
                        int num=must->size() -1;
                        if(P_NUM_INT(must->at(must->size() -1)) == num_k4)
                        {    
                            int k=0;
                            for(i=0;i<must->size();i++)
                            {
                                
                                if(P_NUM_INT(must->at(i)) == num_k4)
                                    k++;
                            }
                            if(k>=num)
                                current = four_a_kind; 
                        }
                    }
                    else
                        current = four_a_kind;   
                }
            case(straight_flush):
                if(straight_begin && flush_idx)
                {   
                    if(must!=nullptr)
                    {
                        for(i=0;i<must->size();i++)
                        {
                            // cout<< P_NUM_INT(must->at(i)) <<"/"<<P_SUIT_INT(must->at(i)) <<endl;
                            if(P_NUM_INT(must->at(i))  > straight_end)       
                                break;
                            if(P_NUM_INT(must->at(i)) < straight_begin && !(straight_end==14 && P_NUM_INT(must->at(i))==1))        
                                break;
                            if(P_SUIT_INT(must->at(i)) != flush_idx)
                                break;
                            if(i==must->size()-1)
                                current = straight_flush;   
                        }
                    }
                    else
                        current = straight_flush;   
                }
            default:
                return current;
        }
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
        "TH JH QC QD QS QH KH AH 2S 6S\n"\
         "2H 2S 3H 3S 3C 2D 3D 6C 9C TH\n"\
        );
    std::ostringstream oss;

    solve_uva_problem(iss, oss);
    EXPECT_EQ("Hand: TH JH QC QD QS Deck: QH KH AH 2S 6S Best hand: straight-flush\n"\
    "Hand: 2H 2S 3H 3S 3C Deck: 2D 3D 6C 9C TH Best hand: four-of-a-kind\n"\
    ,oss.str());
}
#endif