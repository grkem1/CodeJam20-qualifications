#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h> 

using namespace std;

class Task{
public:
    int start,end,index;
    Task(int s = 0, int e = 0, int i = 0){
        start = s;
        end = e;
        index = i;
    }
};

int main(){

    ios_base::sync_with_stdio(false);
    int TC;
    cin >> TC;
    for(int T = 0; T < TC; T++){

        int taskCount;
        cin >> taskCount;
        vector<Task> myTasks;
        for(int i = 0; i < taskCount; i++){
            int a,b;
            cin >> a >> b;
            myTasks.push_back(Task(a,b,i));
        }

        bool impossibleFlag = false; 
        vector<int> indexC;
        vector<Task> taskJ;
        sort(myTasks.begin(),myTasks.end(),[](const Task& lhs, const Task& rhs){return lhs.start < rhs.start;});

        int Clast = 0;
        for(int i = 0; i < myTasks.size(); i++){
            if(myTasks[i].start >= Clast){
                indexC.push_back(myTasks[i].index);
                Clast = myTasks[i].end;
            }else{
                taskJ.push_back(myTasks[i]);
            }
        }

        int Jlast = 0;
        for(int i = 0; i < taskJ.size(); i++){
            if(taskJ[i].start < Jlast){
                impossibleFlag = true;
                break;
            }
            Jlast = taskJ[i].end;
        }

        cout << "Case #" << T+1 << ": " ;
        if(impossibleFlag){
            cout << "IMPOSSIBLE" << endl;
            continue;
        }

        sort(indexC.begin(),indexC.end());
        int indexCindex = 0;

        {
        int i = 0;
        while(indexCindex < indexC.size()){
            for(;i<indexC[indexCindex];i++){
                cout << "J";
            }
            if(i == indexC[indexCindex]){
                cout << "C";
                i++;
            }
            if(i > indexC[indexCindex]){
                indexCindex++;
            }
        }
        for(;i < myTasks.size();i++){
            cout << "J";
        }
        }

        cout << endl;

    }

    return 0;

}