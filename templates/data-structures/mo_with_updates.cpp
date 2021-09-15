// link: https://www.spoj.com/problems/XXXXXXXX/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()

// complexity: Q*(N/B)^2, choosing B as N^2/3, => Q*N^2/3. 
const int N = 5e4 + 10, Q = 1e5 + 10;
int A[N], last[N], rev[N + Q], cnt[N + Q];
bool use[N];
ll block_size;

struct Query {
    ll idx, l, r, t, lb, rb;
} q[Q];

struct Update {
    ll idx, prev_val, new_val;
} u[Q];

bool cmp(Query a, Query b) {
    return (a.lb < b.lb) || (a.lb == b.lb && a.rb < b.rb) || 
        (a.lb == b.lb && a.rb == b.rb && a.t < b.t);
}

/* bool cmp(Query a,Query b) { */
/*     return (a.lb < b.lb) || */ 
/*         (a.lb == b.lb && */ 
/*          (a.lb & 1 ? a.r < b.r : a.r > b.r)); */
/* } */

ll curr_ans = 0;
void add_element(int idx) {
    use[idx] = true;
    if(++cnt[A[idx]] == 1) {
        curr_ans += rev[A[idx]];
    }
}

void remove_element(int idx) {
    use[idx] = false;
    if(--cnt[A[idx]] == 0) {
        curr_ans -= rev[A[idx]];
    }
}

void reflect_update(int idx,int val) {
    if(!use[idx]) {
        A[idx] = val;
        return;
    }
    remove_element(idx);
    A[idx] = val;
    add_element(idx);
}

void do_update(int idx) {
    reflect_update(u[idx].idx, u[idx].new_val);
}

void undo_update(int idx) {
    reflect_update(u[idx].idx, u[idx].prev_val);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
    int n;
    cin >> n;
    block_size = pow(n, 2.0/3.0);
    map<ll,int> mp;
    for(int i = 0; i < n; i++) {
        cin >> A[i];
        last[i] = A[i];
        mp[A[i]];
    }
    int m, nq = 0, nu = 0;
    cin >> m;
    for(int i = 0; i < m; i++) {
        char ch;
        int x, y;
        cin >> ch >> x >> y;
        x--;
        if(ch == 'Q') {
            y--;
            q[nq] = {nq, x, y, nu - 1, x/block_size, y/block_size};
            nq++;
        } else {
            u[nu] = {x, last[x], y};
            last[x] = y;
            nu++;
            mp[last[x]];
        }
    }
    int compressed_val = 0; 
    for(auto &it : mp) {
        rev[compressed_val] = it.first;
        it.second = compressed_val++;
    }
    for(int i = 0; i < n; i++) A[i] = mp[A[i]];
    for(int i = 0; i < nu; i++) {
        u[i].new_val = mp[u[i].new_val];
        u[i].prev_val = mp[u[i].prev_val];
    }
    sort(q, q + nq, cmp);
    vector<long long> ans(nq);
    for(int i = 0, l = 0, r = -1, t = -1; i < nq; i++) {
        while(t < q[i].t) do_update(++t);
        while(t > q[i].t) undo_update(t--);
        while(r < q[i].r) add_element(++r);
        while(l > q[i].l) add_element(--l);
        while(r > q[i].r) remove_element(r--);
        while(l < q[i].l) remove_element(l++);
        ans[q[i].idx] = curr_ans;
    }
    for(auto a : ans) cout << a << endl;
    return 0;
}	

/* complexity with MO: */
/* O((N/B)*N + B*Q) */
