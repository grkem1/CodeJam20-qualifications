#include <bits/stdc++.h>

using namespace std;

short XOR_bits(const short& a,const short& b){
    if(a!=b)return 1;
    if(a==b)return 0;
}

vector<short> XOR_vector(const vector<short>& a, const vector<short>& b){
    vector<short> result(a.size(), -1);
    for(int i = 0; i < a.size(); i++){
        if(a[i]==b[i])result[i] = 0;
        if(a[i]!=b[i])result[i] = 1;
    }
    return result;
}

void COMP(vector<short>& a){ // complements a vector in place
    for( int i = 0; i < a.size(); i++ ){
        a[i] == 0 ? a[i]++ : a[i] --;
    }
    return;
}

int findOp(const int& a,const int& b, const int& a_prime,const int& b_prime){
    if(b == -1 || b_prime == -1){   // only 2 operations to consider for 2-state inputs
        if(a == a_prime)return 0;   // NOP if state indicator did not change
        if(a != a_prime)return 3;   // COMP if state indicator toggles in the last state
    }

    if(a == a_prime && b == b_prime)return 0; // 0 stands for NOP
    if(a == a_prime && b != b_prime)return 1; // 1 stands for COMP+REV
    if(a != a_prime && b == b_prime)return 2; // 2 stands for REV
    if(a != a_prime && b != b_prime)return 3; // 3 stands for COMP

    return 5;                                 // should not come here!
}

void applyOp(vector<short>& batch, int op){
    if(op == 0)return;                        // apply NOP
    if(op == 1){                              
        COMP(batch);                          // apply COMP+REV
        reverse(batch.begin(),batch.end());
        return;
    }
    if(op == 2){
        reverse(batch.begin(),batch.end());   // apply REV
        return;
    }
    if(op == 3){
        COMP(batch);                          // apply COMP
        return;
    }
    cout << "Error!: Do not input op NOT in {0,1,2,3}" << endl;
}


int main(){

    ofstream debugFile("debug");
    debugFile << endl;

    int T, B;
    cin >> T >> B;
    for(int TC = 0; TC < T; TC++){
        if(B <= 10){
            char response;
            vector<short> guess(B,-1);
            for(int i = 0; i < B; i++){
                cout << i+1 << endl;
                cin >> guess[i];
            }   
            copy ( guess.begin(), guess.end(), std::ostream_iterator<int>(std::cout, "") );
            cout << endl;
            cin >> response;
            if(response == 'N'){
                break;
            }else if(response == 'Y'){
                continue;
            }
        }else if(B == 20){
            char response;
            vector<short> guess(B,-1);
            vector<short> batch1(B/2,-1);
            vector<short> batch2(B/2,-1);
            vector<short> batch1_scratch(B/4,-1);
            vector<short> batch2_scratch(B/4,-1);
            // Take 5..14 in a single batch
            for(int i = B/4, j = 0; i < 3*B/4; i++,j++){
                cout << i+1 << endl;
                cin >> guess[i];
                batch1[j]=guess[i];
            }
            // Take 0..4 and 15..19 in the same batch
            for(int i = 0, j = 0; i < B/4; i++,j++){
                cout << i+1 << endl;
                cin >> guess[i];
                batch2[j]=guess[i];
            }
            for(int i = 3*B/4, j = B/4; i < B; i++,j++){
                cout << i+1 << endl;
                cin >> guess[i];
                batch2[j]=guess[i];
            }
            
            for(int i = 0; i < batch1_scratch.size(); i++){
                batch1_scratch[i] = XOR_bits(batch1[i], batch1[batch1.size() - i - 1]); // XOR bits with their counterparts
                batch2_scratch[i] = XOR_bits(batch2[i], batch2[batch2.size() - i - 1]); // XOR bits with their counterparts
            }

            // Find Indicator Bits for batch1

            int batch1_index_a = -1;
            int batch1_index_b = -1;
            int batch1_single_index = 0;

            for(int i = 0; i < batch1_scratch.size(); i++){
                if(batch1_index_a == -1 && batch1_scratch[i] == 1){
                    batch1_index_a = i;
                }
                if(batch1_index_b == -1 && batch1_scratch[i] == 0){
                    batch1_index_b = i;
                }
            }

            if(batch1_index_a == -1 || batch1_index_b == -1){ // If one of the indexes are missing we have a 2-state 
                batch1_index_a = -1;                          // batch. This means we can ignore both indexes and use 
                batch1_index_b = -1;                          // any element as state indicator. we use batch1_single
                                                              // index for this purpose.
            }

            // Find Indicator Bits for batch2

            int batch2_index_a = -1;
            int batch2_index_b = -1;
            int batch2_single_index = 0;

            for(int i = 0; i < batch2_scratch.size(); i++){
                if(batch2_index_a == -1 && batch2_scratch[i] == 1){
                    batch2_index_a = i;
                }
                if(batch2_index_b == -1 && batch2_scratch[i] == 0){
                    batch2_index_b = i;
                }
            }

            if(batch2_index_a == -1 || batch2_index_b == -1){ // If one of the indexes are missing we have a 2-state 
                batch2_index_a = -1;                          // batch. This means we can ignore both indexes and use 
                batch2_index_b = -1;                          // any element as state indicator. we use batch2_single
                                                              // index for this purpose.
            }

            // Find the last state using state indicator bits  |||| BATCH 111111 ||||

            int a,b;
            if(batch1_index_a != -1){        // if we need both a and b
                a = batch1[batch1_index_a];  // use a and b to indicate initial states
                // debugFile << "WHY: " << "batch1_index_a: " << batch1_index_a << "a: " << a;
                
                b = batch1[batch1_index_b];  // 
            }else{
                a = batch1[batch1_single_index]; // if single indicator is enough,
                b = -1;                          // get rid of b
            }

            int a_prime,b_prime;
            if(batch1_index_a != -1){                // if we need both a and b
                cout << batch1_index_a+6 << endl;      // query a_prime and b_prime
                cin  >> a_prime;                     // a_prime and b_prime stand for the state indicator bits in new state.
                cout << batch1_index_b+6 << endl;      // from now on, we have a new state and it is held by a_prime and b_prime
                cin  >> b_prime;
            }else{
                cout << batch1_single_index+6 << endl;      // if single indicator is enough,
                cin  >> a_prime;
                b_prime = -1;                        // get rid of b
            }


            // Find the operation to be applied
            int op = findOp(a,b,a_prime,b_prime);

            debugFile << "Batch1(Inner)--- :";
            copy ( batch1.begin(), batch1.end(), std::ostream_iterator<int>(debugFile, "") );
            debugFile << endl;
            debugFile << "Batch1(Inner)--- batch1_index_a: " << batch1_index_a << " batch1_index_b: " << batch1_index_b << endl;
            debugFile << "Batch1(Inner)--- a: " << a << " b: " << b << " a_prime: " << a_prime << " b_prime: " << b_prime << " op: " << op << endl;

            applyOp(batch1,op);

            // Find the last state using state indicator bits  |||| BATCH 222222 ||||

            if(batch2_index_a != -1){        // if we need both a and b
                a = batch2[batch2_index_a];  // use a and b to indicate initial states
                b = batch2[batch2_index_b];  // 
            }else{
                a = batch2[batch2_single_index]; // if single indicator is enough,
                b = -1;                          // get rid of b
            }

            if(batch2_index_a != -1){                // if we need both a and b
                cout << batch2_index_a + 1 << endl;      // query a_prime and b_prime
                cin  >> a_prime;                     // a_prime and b_prime stand for the state indicator bits in new state.
                cout << batch2_index_b + 1 << endl;      // from now on, we have a new state and it is held by a_prime and b_prime
                cin  >> b_prime;
            }else{
                cout << batch2_single_index + 1 << endl;      // if single indicator is enough,
                cin  >> a_prime;
                b_prime = -1;                        // get rid of b
            }

            // Find the operation to be applied
            op = findOp(a,b,a_prime,b_prime);

            debugFile << "Batch2(Outer)--- :";
            copy ( batch2.begin(), batch2.end(), std::ostream_iterator<int>(debugFile, "") );
            debugFile << endl;
            debugFile << "Batch2(Outer)--- batch2_index_a: " << batch2_index_a << " batch2_index_b: " << batch2_index_b << endl;
            debugFile << "Batch2(Outer)--- a: " << a << " b: " << b << " a_prime: " << a_prime << " b_prime: " << b_prime << " op: " << op << endl;

            applyOp(batch2,op);

            // Place the batches in their places in guess accordingly.

            for(int i = 0,j=0,k=0; i < guess.size(); i++){
                if(i < guess.size()/4 || i >= guess.size()*3/4){
                    guess[i] = batch2[j++];
                }else{
                    guess[i] = batch1[k++];
                }
            }

            // Print the result

            copy ( guess.begin(), guess.end(), std::ostream_iterator<int>(std::cout, "") );
            cout << endl;
            cin >> response;
            if(response == 'N'){
                break;
            }else if(response == 'Y'){
                continue;
            }
        }
    }
    return 0;

}