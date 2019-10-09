#include <iostream>
#include <cstring>
#include <regex>

using namespace std;

int to_minutes(string x){ // change xx:xx to minutes
    x=x+":"; // for easier loop
    int sum = 0;
    int i = 0;
    int stage = 0;
    for(auto x: x){
        if(x!=':'){
            i=i*10+int(x)-48;
        } else {
            if(stage == 0){
                sum=sum+i*60;
                i=0;
                stage = 1;
            } else {
                sum = sum+i;
            }
        }
    }
    return sum;
}

bool check_first(vector<string> v){ // check if time increase, and stops doesnt repeat


    regex time("[0-9]{1,2}:[0-9]{2}"); // dont worry about this
    vector<string> stops;
    int last = 0; //
    int curr;
    for(auto x: v){
        if(regex_match(x, time)){
            curr = to_minutes(x);
            if(last >= curr){
                return false;
            }
            last = curr;
        } else {
            for(string y: stops){
                if(x == y) {
                    return false;
                }
            }
            stops.push_back(x);
        }
    }
    return true;
}

pair<int, vector<string>> check_line(string line){ // checl if the line can meet expectations
    regex first("0*[1-9]+([[:space:]](([6-9]|1[0-9]|20):[0-5][0-9]|5:5[5-9]|21:([01][0-9]|2[01]))[[:space:]]([[:lower:]]|[[:upper:]]|_|\\^)+)*");
    regex second("([[:lower:]]|[[:upper:]]|[[:space:]])+[[:space:]]\\d+.\\d\\d[[:space:]][1-9][0-9]*");
    regex third("\\?[[:space:]](([[:lower:]]|[[:upper:]]|_|\\^)+[[:space:]]0*[1-9]+[[:space:]])*([[:lower:]]|[[:upper:]]|_|\\^)+");

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
        int stage = 0; // for linetype 1 and 2
        switch (outcome.first%2) {

        case 1:
            for(auto x: line){
                if(x!=' '){
                    if(!stage==0 || x!='0'){
                        word = word+x;
                    }
                } else {
                    v.push_back(word);
                    word = "";
                    stage = 1;
                }
            }
            break;
        case 0:
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
        }
    outcome.second = v;
    return outcome;
}


int main() // write something, if it means expectations vector will be written by program,
            //it will also parse hours(xx:xx) to minutes after 0:00 if they exists
{
    string line;
    getline(cin, line);
    for(string x: check_line(line).second){
        cout << "\n"+x;
    }
    cout << "\n";
    if(check_first(check_line(line).second)){
        cout << "ok";
    } else {
        cout << "nieok";
    }
    return 0;
}
