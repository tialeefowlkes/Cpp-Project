/*  Tia Fowlkes
 Project 8
 26 MArch 2018
 Section 009  */

#include "proj08_market.h"
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
#include<utility>
using std::pair;



/*
provides three data members:
string file_name, the name of the file containing the data
vector<string> symbol_list, A list of the short names of each of the 30 stocks in the Dow map<long, vector<double> > stocks
The prices of the 30 stocks on the date (the key). The 
prices are in order of the elements in symbol_list (that is, alphabetically by short name)
*/

Market::Market(string s){
    string line;
    
    //open file
    ifstream myfile(s);
    
    //if file is open
    if (myfile.is_open()){
        //going through each line
        while (getline (myfile,line)){
            long date = 0;
        
            istringstream iss (line);
            //add date
            iss >> date;
            
            vector<double> prices;
            
            for(int i=0; i<30; i++){
                double price = 0;
                iss >> price;
                //add prices to vector
                prices.push_back(price);
            }
            //creating map of stocks
            stocks.insert(pair<long,vector<double>>(date, prices));
        }
    }
}


/*
returns the price of the stock on the 
date if: the date is a valid date, the stock symbol is a valid stock symbol
returns a -1.0 otherwise
*/

double Market::get_price (string stock, long date) const {
    // returns the price of the stock on the date if: the date is a valid date
    // & the stock symbol is a valid stock symbol
    

    //if date exists
    if(stocks.count(date) != 0){
        auto itr = find(symbol_list.begin(), symbol_list.end(),stock);
            //if symbol is found
            if(itr!=symbol_list.end()){
                //create index from place to end of list
                int indx = distance(symbol_list.begin(),itr);
                //return the price of the stock at th date
                return stocks.at(date)[indx];
            }
            else{
                return -1.0;
            }
    }
    
    else{
        return -1.0;
    }
}

/*
Returns as a pair
the high and low values (in that order) for that stock for the provided year.
if the ye ar or the symbol does not exist, returns the pair {-1.0, -1.0};
*/ 
pair<double, double> Market::high_low_year(long year, string symbol){
    bool yr_found = false;
    vector<double> prices;
    //iterate through stock list
    for(auto itr=stocks.begin(); itr != stocks.end(); ++itr){
        //iterate through dates
        long yr = itr->first / 10000;
        //if year exists
        if(yr == year){
            yr_found = true;
            //create index of the stock from the symbol_list
            auto indx_stock = find(symbol_list.begin(), symbol_list.end(),symbol);
            //if stock is not in the symbol_list
            if(indx_stock!= symbol_list.end()){
                prices.push_back(itr->second[distance(symbol_list.begin(),indx_stock)]);
        }
            else{
                return pair<double,double>(-1.0,-1.0);
            }
            
        }
    }
    
    //finding the high low values
         
         //if year does not exist                        
        if(yr_found == false){
            return pair<double,double>(-1.0,-1.0);
        }                             
         //prices vector index
        double high =prices[0];
        double low = prices[0];
        
        //iterate through prices
        for(auto x: prices){
            //if high
            if(x>high){
                high = x;
            }
            //if low
            if(x<low){
                low = x;
            }
        }
                //return pair 
                return pair<double,double>(high,low);

}
        
        
        
        
        


