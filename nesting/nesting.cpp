#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
    
    ios_base::sync_with_stdio(false);
    int TC;
    cin >> TC;
    // cin.clear();
    cin.ignore();
    for(int T = 0; T < TC; T++){

        string input;
        getline(cin, input);
        string s;
        int prev = 0;
        for(int i = 0; i < input.size(); i++){
            bool pre = false;
            for(int j = 0; j < (input[i]-'0') - prev; j++){
                s.push_back('(');
                pre = true;
            }
            if(pre)s.push_back(input[i]);
            for(int j = 0; j < prev - (input[i]-'0'); j++){
                s.push_back(')');
            }
            if(!pre)s.push_back(input[i]);
            prev = input[i]-'0';
        }
        for(int i = 0; i < prev; i++){
            s.push_back(')');
        }

        cout << "Case #" << T+1 << ": ";
        for(int i = 0; i < s.size(); i++){
            cout << s[i];
        }
        cout << "\n";

    }

    return 0;
}