#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){

    int TC = 0;
    cin >> TC;
        //For each testcase
        for(int T = 0; T < TC; T++){
            int N;                      // input size
            vector<vector<int>> M;      // corresponding square matrix
            int columns, rows, trace;   //
            columns = rows = trace = 0; // outputs
            cin >> N;
            M.resize(N, vector<int>(N));

            ///////// Count rows with repetitive numbers, find trace
            for(int i = 0; i < N; i++){ // foreach row
                vector<bool> seen(N,false); // scratch
                bool traceFlag, seenFlag;
                traceFlag = seenFlag = false;
                for(int j = 0; j < N; j++){ //foreach column
                    cin >> M[i][j];
                    if(i == j){
                        trace += M[i][j];
                        traceFlag = true;
                    }
                    if(!seenFlag){
                        if(seen[M[i][j]-1] == true){
                            seenFlag = true;
                            rows++;
                        }else{
                            seen[M[i][j]-1] = true;
                        }                        
                    }
                }
            }

            /////// Count columns with repetitive numbers
            for(int j = 0; j < N; j++){        // foreach column
                vector<bool> seen(N,false);     // scratch  
                for(int i = 0; i < N; i++){   // foreach row
                    if(seen[M[i][j] - 1] == true){
                        columns++;
                        break;
                    }else{
                        seen[M[i][j] - 1] = true;
                    }
                }   
            }
            cout << "Case #" << T+1 << ": " << trace << " " << rows << " " << columns << "\n";
        }
}