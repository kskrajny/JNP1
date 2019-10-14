#include <iostream>
#include <regex>
#include <cstring>

using namespace std;


pair<int, vector<string>> checkLine(string line){
    regex first("(0*[1-9][0-9]*|0)([[:space:]](([6-9]|1[0-9]|20):[0-5][0-9]|5:5[5-9]|21:([01][0-9]|2[01]))[[:space:]]([[:lower:]]|[[:upper:]]|_|\\^)+)*");
    regex second("([[:lower:]]|[[:upper:]]|[[:space:]])+[[:space:]]\\d+.\\d\\d[[:space:]][1-9][0-9]*");
    regex third("\\?[[:space:]](([[:lower:]]|[[:upper:]]|_|\\^)+[[:space:]](0*[1-9][0-9]*|0)[[:space:]])*([[:lower:]]|[[:upper:]]|_|\\^)+");

    vector<string> v; // this is what I am going to return
    pair<int, vector<string>> outcome;

    if(regex_match(line, first)) {
        outcome.first = 1;
    } else {
        if(regex_match(line, second)){
            outcome.first = 2;
        } else {
            if(regex_match(line, third)){
                outcome.first = 3;
            } else {
                outcome.first = -1;
                outcome.second = v;
                return outcome;
            }
        }
    }

    line = line+" "; // for easier loop
    string word = ""; // this is where i write next signs
    int stage = 0;

    switch (outcome.first) {

        case 1:
            for(auto x: line){
                if(x!=' '){
                    if(!stage==0 || x!='0'){
                        word = word+x;
                        stage = 1;
                    }
                } else {
                    if(stage==0 && word==""){
                        word = "0";
                    }
                    v.push_back(word);
                    word = "";
                }
            }
            break;
        case 2:
            for(auto x: line){
                switch(stage){
                    case 0:
                        if(int(x)<48 || int(x)>57){
                            word = word+x;
                        } else {
                            word.pop_back();
                            v.push_back(word);
                            word = "";
                            word = word+x;
                            stage=1;
                        }
                        break;
                    case 1:
                        if(x != ' '){
                            word = word+x;
                        } else {
                            v.push_back(word);
                            word = "";
                        }
                        break;
                }
            }
            break;
        case 3:
            for(auto x: line){
                if(x!=' '){
                    if(!stage==0 || x!='0'){
                        word = word+x;
                        stage = 1;
                    }
                } else {
                    if(stage==0 && word==""){
                        word = "0";
                    }
                    v.push_back(word);
                    word = "";
                    stage = 0;
                }
            }
            break;
            
    }

    outcome.second = v;
    return outcome;
}
