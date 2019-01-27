#include <bits/stdc++.h>
#define mx 1000000
using namespace std;

int main () {
    srand(time(NULL));
    int n, i, cons;
    set <int> exist;
    vector <int> values;
    cin >> n;
    for ( i = 0 ; i < n ; ++i ) {
        cons = 1 + (rand()%mx) ;
        if(exist.find(cons) == exist.end()) {
            exist.insert(cons);
            values.push_back(cons);
            continue;
        }
        --i;
    }
    cout << n << " " << (rand()%mx) + 1 << "\n";
    for( i = 0 ; i < n ; ++i ) cout << values[i] << " "; 
    return 0;
}