#include <bits/stdc++.h>
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE    
#include <gmock/gmock.h>
#endif
using namespace std;

#define TOTAL_CARD_NUM  52


struct piles_deck
{
    std::vector<int> deck;
    std::vector<int> piles[7];

    bool operator < (const piles_deck &other) const
    {
        if(deck.size() < other.deck.size())
            return true;
        else if(deck.size() > other.deck.size())
            return false;

        
        for(int i=0;i<7;i++){
        if(piles[i].size() < other.piles[i].size())
                return true;
        else if(piles[i].size() > other.piles[i].size())
            return false;          
        }
        if(deck<other.deck)
            return true;
        else  if(deck>other.deck)
            return false;  

        for(int i=0;i<7;i++){
        if(piles[i] < other.piles[i])
                return true;
        else  if(piles[i] > other.piles[i])
            return false;       
        }

        return false;
    }
};


class  Poker_Game_10_20_30
{
public:
    explicit Poker_Game_10_20_30()
    {

    }
    bool init(std::istream &is)
    {
        uint8_t i = 0;
        uint16_t card_value;
  
        is>>card_value;
        if(card_value == 0)
            return false;
        //init & clear
        get_draw = 0;
        record.clear();
        poker_composite.deck.clear();
        for (auto &pile : poker_composite.piles)
            pile.clear();
        
        active_piles = 7;
        dealt_cnt = 7;

        poker_composite.piles[i++].emplace_back(card_value);

        while(i<7) //initial deal
        {
            is>>card_value;
            poker_composite.piles[i++].emplace_back(card_value);
        }
        
        while(i<TOTAL_CARD_NUM) 
        {
            is>>card_value;
            poker_composite.deck.emplace_back(card_value);
            i++;
        }
        return true;
    }

    bool deal_n_play(void)
    {
        for (auto &pile : poker_composite.piles){
            if(pile.size())
            {
                if(poker_composite.deck.size() ==0)
                    break;
                dealt_cnt++;
                pile.emplace_back(poker_composite.deck[0]);
                poker_composite.deck.erase(poker_composite.deck.begin());
                play(pile);

                if(record.find(poker_composite) != record.end()){
                    get_draw = 1;
                    break;
                }
                else
                    record.emplace(poker_composite);
            }

        }
        return true;
    }

    bool result_check(std::ostream &os)
    {
        bool ret = true;

        if(active_piles == 0) //win
            os<<"Win : "<< dealt_cnt <<endl;
        else if(poker_composite.deck.size() ==0)  //loss
            os<<"Loss: "<< dealt_cnt <<endl;
        else{
            if(get_draw)
                os<<"Draw: "<< dealt_cnt <<endl;
            else
                ret = false;
        }
        return ret;
    }
    
    
private:
     struct piles_deck poker_composite;
     std::set<piles_deck> record;
     uint16_t active_piles;
     uint16_t dealt_cnt;
     uint16_t get_draw;
    //  std::set<std::vector<std::array<int, 3> >> round_snapshot;
    bool valid_sum(int sum)
    {
        if(sum==20 || sum == 10 || sum==30)
            return true;
        else
            return false;
    }
    void play(std::vector<int> &pile) 
    {   
            size_t n = pile.size();
            while(n >= 3)
            {
                int picked = 0;
                if(valid_sum(pile[0] + pile[1] + pile[n-1]))    
                {
                    poker_composite.deck.emplace_back(pile[0]);
                    poker_composite.deck.emplace_back(pile[1]);
                    poker_composite.deck.emplace_back(pile[n-1]);
                    pile.erase(pile.begin());
                    pile.erase(pile.begin());
                    pile.erase(pile.end()-1);
                    picked =1;    
                }    
                else if(n > 3)
                {
                    //2. the first one and the last two  
                    if(valid_sum(pile[0] + pile[n-2] + pile[n-1]))    
                    {
                        poker_composite.deck.emplace_back (pile[0]);
                        poker_composite.deck.emplace_back (pile[n-2]);
                        poker_composite.deck.emplace_back (pile[n-1]);
                        pile.erase(pile.begin());
                        pile.erase(pile.end()-2);
                        pile.erase(pile.end()-1);
                        picked = 1;  
                    }
                    //3. the last three cards.
                    else if(valid_sum(pile[n-3] + pile[n-2] + pile[n-1]))
                    {
                        poker_composite.deck.emplace_back (pile[n-3]);
                        poker_composite.deck.emplace_back (pile[n-2]);
                        poker_composite.deck.emplace_back (pile[n-1]);
                        pile.erase(pile.end()-3);
                        pile.erase(pile.end()-2);
                        pile.erase(pile.end()-1);
                        picked = 1;      
                    }
                }
                if(!picked)
                    break;
            
                n = pile.size();

                if(n==0)
                {
                    record.clear();
                    active_piles--;
                }    
                
            }
        
    }
}; 

int solve_uva_problem(std::istream &is,std::ostream &os)
{
    
    while(1)
    {
        Poker_Game_10_20_30  game;

        if(!game.init(is))
            break;
        while(1)
        {
            game.deal_n_play();
            if(game.result_check(os))
                break;
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

#endif