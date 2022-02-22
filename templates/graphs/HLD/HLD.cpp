
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ll long long int
#define ld long double
#define ordered_set tree < ll ,  null_type ,  less<ll> ,  rb_tree_tag ,  tree_order_statistics_node_update >
//added two more functions to set
//(1)*(set.find_by_order(k))[kth element in the sorted set] 
//(2)set.order_of_key(k)[count of elements strictly less than k]

// Uncomment when using kactl templates and change typedef of pair
// #define rep(i, a, b) for(int i = a; i < (b); ++i)
// #define sz(x) (int)(x).size()
// typedef pair<int, int> pii;

typedef vector< int > vi;
typedef vector<long long> lvi;
typedef vector< vector<int> > vvi;
typedef vector< vector<long long> > lvvi;
typedef pair< int,int > ii;
typedef pair< long long,long long > lii;
typedef vector<pair<int,int>> vii;
typedef vector<pair<long long,long long>> lvii;
typedef vector<vector<pair<int,int>>> vvii;
typedef vector<vector<pair<long long,long long>>> lvvii;
typedef vector<bool> vb;

mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
// usage: x = rng() % k; shuffle(all(v), rng);

#define all(c) (c).begin(),(c).end()
#define tc(t) int (t); cin>>(t);while((t)--)
#define ff first
#define pb push_back
#define ss second
#ifdef ONLINE_JUDGE
    #define error(args...) 0
#else
    #define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
#endif
void err(istream_iterator<string> it) {cerr << endl;}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr <<"[ "<< *it << " = " << a << " ]";
    err(++it, args...);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
const long long mod = 1e9 + 7;
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

long long mos() { return 0LL; }
template<typename T, typename... Args>
T mos(T a, Args... args) { return ((a + mos(args...))%mod + mod)%mod; }

long long mop() { return 1LL; }
template<typename T, typename... Args>
T mop(T a, Args... args) { return (a*mop(args...))%mod; }
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T = long long>
class SegmentTrees {
    vector<T> st, lazy;
public:
    void init(int n) {
        st.clear();
        lazy.clear();
        st.assign(4*n, 0);
        lazy.assign(4*n, 0);
    }
    void push(int x) {
        if(lazy[x]) {
            st[x*2] += lazy[x];
            st[x*2 + 1] += lazy[x];
            lazy[x*2] += lazy[x];
            lazy[x*2 + 1] += lazy[x];
            lazy[x] = 0;
        }
    }
    void update(int l,int r,T val,int left,int right,int pos=1) {
        if(l > r) return;
        if(l == left and r == right) {
            st[pos] += val;
            lazy[pos] += val;
        }
        else {
            push(pos);
            int mid = (left + right)/2;
            update(l, min(r, mid), val, left, mid, pos*2);
            update(max(l, mid + 1), r, val, mid + 1, right, pos*2 + 1);
            st[pos] = min(st[pos*2], st[pos*2+1]);
        }
    }
    T query(int l,int r,int left,int right,int pos=1) {
        if(l>r) return 0;
        if(l==left && r==right) return st[pos];
        else {
            push(pos);
            int mid = (left + right)/2;
            return min(query(l, min(r,mid), left, mid, (pos<<1LL)), query(max(l,mid+1), r, mid+1, right, (pos<<1LL)+1));
        }
    }
};


// requires a segment tree with init function
template<class T = int>
class HLD {
    SegmentTrees<T> sgt;
    vector<vector<int>> adj;
    vector<int> sz, par, head, sc, st, ed;
    int t, n;
public:
    HLD(vector<vector<int>> &adj1,int n1): 
    sz(n1+1), par(n1+1), head(n1+1), sc(n1+1),
    st(n1+1), ed(n1+1) {
        n = n1;
        adj = adj1;
        t = 0;
    }
    void dfs_sz(int x,int p = 0) {
        sz[x] = 1; par[x] = p; head[x] = x;
        for(auto nx : adj[x]) {
            if(nx == p) continue;
            dfs_sz(nx, x);
            sz[x] += sz[nx];
            if(sz[nx] > sz[sc[x]]) sc[x] = nx;
        }
    }
    void dfs_hld(int x,int p = 0) {
        st[x] = t++;
        if(sc[x]) {
            head[sc[x]] = head[x];
            dfs_hld(sc[x], x);
        }
        for(auto nx : adj[x]) {
            if(nx == p or nx == sc[x]) continue;
            dfs_hld(nx, x);
        }
        ed[x] = t - 1;
    }
    void build(int base = 1) {
        dfs_sz(base);
        dfs_hld(base);
        sgt.init(t);
    }   
    bool anc(int x,int y) {
        if(x == 0) return true;
        if(y == 0) return false;
        return (st[x] <= st[y] and ed[x] >= ed[y]);
    }
    int lca(int x,int y) {
        if(anc(x, y)) return x;
        if(anc(y, x)) return y;
        while(!anc(par[head[x]], y)) x = par[head[x]];
        while(!anc(par[head[y]], x)) y = par[head[y]];
        x = par[head[x]];
        y = par[head[y]];
        // one will overshoot the lca and the other will reach lca.
        return anc(x, y) ? y : x;
    }
    void update_up(int x,int p,ll add) {
        while(head[x] != head[p]) {
            sgt.update(st[head[x]], st[x], add, 0, t-1);
            x = par[head[x]];
        }
        sgt.update(st[p], st[x], add, 0, t - 1);
    }
    // add to [1<->x]
    void range_update(int u,int v,T add) {
        int l =  lca(u, v);
        update_up(u, l, add);
        update_up(v, l, add);
        update_up(l, l, -add);
    }
    T query_up(int x,int p) {
        T ans = 0;
        while(head[x] != head[p]) {
            ans = min(ans, sgt.query(st[head[x]], st[x], 0, t-1));
            x = par[head[x]];
        }
        ans = min(ans, sgt.query(st[p], st[x], 0, t - 1));
        return ans;
    }
    T range_min(int u,int v) {
        int l = lca(u, v);
        return min(query_up(u, l), query_up(v, l));
    }
    bool check() {
        return sgt.query(0, t-1, 0, t-1) >= 0;
    }
};

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);    
    int n;
    cin >> n;
    vvi adj(n + 2);
    for(int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        adj[p].pb(i);
        adj[i].pb(p);
    }
    HLD<ll> H(adj, n);
    H.build();
    vi A(n + 1), C(n + 1);
    // 1 -> A -> add
    for(int i = 1; i <= n; i++) {
        int add;
        cin >> add;
        A[i] = add;
        H.range_update(1, i, add);
    }
    for(int i = 1; i <= n; i++) {
        int sub;
        cin >> sub;
        C[i] = sub;
        H.range_update(1, i, -sub);
    }
    if(!H.check()) cout << "No" << "\n";
    else cout << "Yes" << "\n";
    tc(Q) {
        int t;
        cin >> t;
        if(t == 1) {
            int v, val;
            cin >> v >> val;
            H.range_update(1, v, val - A[v]);
            A[v] = val;
        } else {
            int v, val;
            cin >> v >> val;
            H.range_update(1, v, C[v] - val);
            C[v] = val;
        }
        if(H.check()) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}    


// WA
// 1. overflow
// 2. re-initialize global variables for every test case.
// 3. edge cases like n=1

// Run time error
// 1. division by zero.
// 2. array bounds.

// TLE
// 1. uncomment that #define endl '\n' line