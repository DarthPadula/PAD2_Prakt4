/* 
 * File:   read_file_main.cpp
 * Author: max
 *
 * Created on 22. November 2017, 17:08
 */

#include <cstdlib>
#include <map>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iterator>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

void error(string s){
    throw runtime_error{s};
}


int main() {
    try {
        ifstream readin {"beispiel.txt"};
        int counter {0};
        if(!readin){
            error("Failed opening file!");
        }
        string readword{};
        map<string,int> words{};
        while((readin >> readword)&& !readin.eof()){
            ++words[readword];
            counter++;
        }    
        vector<pair<int,string>> sortmap{};
        pair<int,string> pushpair{};
        using citer = map<string,int>::const_iterator;
        for(citer p {words.cbegin()};p != words.cend();++p){
            pushpair.first = p->second;
            pushpair.second = p->first;
            sortmap.push_back(pushpair);
                                                           }
        sort(sortmap.begin(),sortmap.end());
        for(int i = 0; i < sortmap.size();i++){
            cout << sortmap[i].second << " : " << sortmap[i].first << endl;
        }
        cout << "Anzahl Wörter: " << counter << endl;
        return 0;
    } catch (exception &e) {
        cerr << e.what();
        return -2;
    } catch (...) {
        cerr << "\nUnknown Exception!\n" << endl;
        return -1;
    }
}

