#include <bits/stdc++.h>
#define mx 10000
using namespace std;

int main () {
    srand(time(NULL));
    int n, m;
    cin >> n >> m;
    set<int> present;
    vector<int> total;
    vector<int> small;
    vector<int> large;
    cout << n << " " << m << "\n";
    int count = 0;
    while(count<(n+m)) {
        int cons = 1 + (rand() % mx);
        if(present.find(cons)==present.end()) {
            total.push_back(cons);
            present.insert(cons);
            ++count;
        }
    }
    sort(total.begin(), total.end());
    count=0;
    while(count<n) {
        small.push_back(total[count]);
        ++count;
    }
    while(count<(n+m)) {
        large.push_back(total[count]);
        ++count;
    }
    random_shuffle(small.begin(), small.end());
    random_shuffle(large.begin(), large.end());
    int i;
    for(i=0;i<n;++i) cout<<small[i]<<" ";
    cout << "\n";
    for(i=0;i<m;++i) cout<<large[i]<<" "; 
    return 0;
}