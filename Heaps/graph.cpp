#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int> > adj[1000000];
int main(){
    srand(time(NULL));
    int n,e,a1,a2,r1,r2,wt;
    cin>>n>>e;
    set<pair<int,int> > present;
    int count=0;
    while(count<e){
        a1=rand()%n+1;
        a2=rand()%n+1;
        r1=min(a1,a2);
        r2=max(a1,a2);
        wt=rand()%100+100;
        if(r1==r2) continue;
        if(present.find(make_pair(r1,r2))!=present.end())continue;
        present.insert(make_pair(r1,r2));
        adj[r1].push_back(make_pair(r2,wt));
        adj[r2].push_back(make_pair(r1,wt));
        ++count;
    }
    cout<<n<<" "<<e<<"\n";
    for(a1=1;a1<=n;++a1){
        for(a2=0;a2<adj[a1].size();++a2){
            if(adj[a1][a2].first>a1)
                cout<<a1<<" "<<adj[a1][a2].first<<" "<<adj[a1][a2].second<<"\n";
        }
    }
    cout<<1;
    return 0;
}