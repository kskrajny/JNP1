#include <iostream>
#include <cstring>
#include <vector>
#include "parser.cpp"

using namespace std;

int main(){
    string line;
    for(int i=0;i<10;i++){
        getline(cin, line);

        pair<int, vector<string>> checked = checkLine(line);
    
        cout << checked.first;
        cout << "  ";

        if(checked.first == 1){
            if (checkTimeAndStops(checked.second)){
                cout << "ok kurs to "+checked.second[0];
            } else {
                cout << "nieok";
            }
        }
        if(checked.first == 3){
            for(int i = 2; i<checked.second.size(); i=i+2){
                cout << checked.second[i];
            }
        }
        cout << "\n";
    }
    return 0;
}
