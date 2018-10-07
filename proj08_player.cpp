/*  Tia Fowlkes
 Project 8
 26 March 2018
 Section 009  */
//
#include "proj08_market.h"
#include "proj08_player.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
using std::ifstream;
#include <sstream>
using std::istringstream;
#include <algorithm>
using std::count; using std::find;
#include<map>
using std::map;
#include<vector>
using std::vector;
#include<string>
using std::string;
#include <iterator>
//using std::string::const_iterator iterator; // 
#include<utility>
using std::pair;
#include <iomanip>
using std::setprecision; using std::fixed;


/*
attempt to buy a stock by the player from the 
Market on the specified date. returns true if the player: has enough cash to make the purchase, the stock symbol is one of the valid 30 symbols, the date is valid (within the range of dates stored in Market)
if true, purchase is made and the player info is updated
cash reduced, stocks updated. if false: return no action taken
*/
bool Player::buy(Market &m, string stock, long date, long quantity){
    
    //enough cash
double spend = quantity * m.get_price(stock,date);
if(m.get_price(stock, date) != -1){
    
    if(cash >= spend){
        auto itr = find(m.symbol_list.begin(),m.symbol_list.end(),stock);
        //if symbol is found
        if(itr!=m.symbol_list.end()){
            //if date exists
            if(m.stocks.count(date) != 0){
                //if stocks exist within  market
                if(stocks.count(stock) != 0){
                    
                    //upgrade quantity
                    stocks[stock] += quantity;
                }
                else{
                    //upgrade quantity 
                    stocks[stock] = quantity;
                }
                //upgrade cash
                cash -= spend;
                return true;
            }
        }
    }
}
    return false;
}

/*
returns true if the player: has the stock
to sell, has at least the quantity indicated (can't sell more than you have)
if true, player info is updated, cash is increased, stocks updated
*/

bool Player::sell(Market &m, string stock, long date, long quantity){
    bool bol = false;
    //create price of stock
    double spend = quantity * m.get_price(stock,date);
    //stock index in stocks list
    auto found = stocks[stock];
    //if stock is available and has enough to sell
    if((m.get_price(stock,date)) != -1.0 && found >= quantity){
        //upgrade stock
        stocks[stock] -= quantity;
        //upgrade cash
        cash += spend;
        bol = true;
    }
    
    return bol;
}

/*
format is :cash,symbol:quantity,symbol:quantity
numeric output is fixed, setprecision(2)
always prints the cash value (even if 0.00), but only prints 
stocks (symbol:quant) if there are  indeed any key:value pairs in stocks
*/

string Player::to_str()
{
    string typ = "";
    string ans = "";
    
    //ostringstream. set values in stream
    std::ostringstream cash1;
    
    //set values in stream
    cash1<<fixed<<setprecision(2)<<cash;
   //iterate through stock list
    for(auto itr = stocks.begin(); itr != stocks.end(); itr++)
    {
        //create new ostringstream
        std::ostringstream sec;
        //put in price
        sec << itr->second;
        
        //format string
        typ += (itr->first) + ":" + sec.str() + ',';
        sec.str("");
        
    }
    //return entire string
    ans = cash1.str() + ',' + typ.substr(0,typ.size()-1);
    return ans;
}


Player Player::combine(Player &b){

/* Player combine(Player &b)
returns a new Player that has, as a combination, all the 
cash and stocks of the two players: the 
caller and the argument.
the caller and the argument Players have their 
cash set to 0 and their stocks cleared */ 

//create new player
Player new_p;
//combine cash
new_p.cash += b.cash + cash;
//set stocks to new player
new_p.stocks = stocks;

// iterate through stocks list
for(auto itr = b.stocks.begin(); itr != b.stocks.end(); itr++){
    //if stock does not exist 
    if(new_p.stocks.count(itr->first) == 0){
            //insert stock into player
            new_p.stocks.insert(*itr);
    }
    //if there is more than one stock
    else{
        //update stocks
        new_p.stocks[itr->first] += itr->second;
        
    }
    
}
 //reset to 0
 cash = 0;
 b.cash = 0;
 
 //clear values
 stocks.clear();
 b.stocks.clear();
    
return new_p;

}




