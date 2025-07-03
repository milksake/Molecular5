#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx2")
// #define _GLIBCXX_DEBUG 1
#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
// using namespace __gnu_pbds;

#define int long long
#define ll long long
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define printv(x) for (int iz = 0; iz < sz(x); iz++) cout << (x)[iz] << ((iz == sz(x)-1) ? '\n' : ' ')
#define printvv(x) for (int jz = 0; jz < sz(x); jz++) printv((x)[jz])

typedef pair<int, int> pii;
typedef vector<int> vi; 
typedef vector<vi> vvi;
typedef set<int> si;

const int inf = 1e18;

void printStructure(const string& r, int(*alpha)(char, char), const vvi& dp)
{
    cout << r << '\n';
    
    int n = sz(r);
    stack<pii> s;
    s.push({0, n-1});
    
    while (!s.empty())
    {
        auto [i, j] = s.top();
        s.pop();
        
        if (i+1 < n && j-1 >= 0 && i+1 != j && dp[i][j] == dp[i+1][j-1] + alpha(r[i], r[j]))
        {
            s.push({i+1, j-1});
            cout << i << ' ' << j << '\n';
            continue;
        }
        if (i+1 < n && dp[i][j] == dp[i+1][j])
        {
            s.push({i+1, j});
            continue;
        }
        if (j-1 >= 0 && dp[i][j] == dp[i][j-1])
        {
            s.push({i, j-1});
            continue;
        }
        rep(k, i+1, j)
            if (dp[i][j] == dp[i][k] + dp[k+1][j])
            {
                s.push({i, k});
                s.push({k+1, j});
                break;
            }
    }
}

void secStructureDpRNA(const string& r, int(*alpha)(char, char), vvi& dp)
{
    int n = sz(r);
    dp.assign(n, vi(n, inf));
    
    rep(i, 0, n)
    {
        if (i-1 >= 0)
            dp[i][i-1] = 0;
        dp[i][i] = 0;
    }
    
    rep(d, 1, n)
    {
        for (int i = 0; i + d < n; i++)
        {
            int j = i+d;
            if (i+1 < n && j-1 >= 0)
                dp[i][j] = dp[i+1][j-1] + alpha(r[i], r[j]);
            if (i+1 < n)
                dp[i][j] = min(dp[i][j], dp[i+1][j]);
            if (j-1 >= 0)
                dp[i][j] = min(dp[i][j], dp[i][j-1]);
                
            rep(k, i+1, j)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j]);
        }
    }
}

void solve()
{
    auto alpha1 = [](char ri, char rj) {
        if (ri > rj)
            swap(ri, rj);
        if (ri == 'C' && rj == 'G')
            return -5ll;
        if (ri == 'A' && rj == 'U')
            return -4ll;
        if (ri == 'G' && rj == 'U')
            return -1ll;
        return 0ll;
    };
    auto alpha2 = [](char ri, char rj) {
        if (ri > rj)
            swap(ri, rj);
        return -(int)((ri == 'C' && rj == 'G') || (ri == 'A' && rj == 'U'));
    };
    vvi dp;
    
    {
        string r = "GGAAAUCC";
        secStructureDpRNA(r, alpha1, dp);
        printStructure(r, alpha1, dp);
        cout << dp[0][sz(r)-1] << '\n';
        secStructureDpRNA(r, alpha2, dp);
        printStructure(r, alpha2, dp);
        cout << dp[0][sz(r)-1] << '\n';
    }
    {
        string r = "ACUCGAUUCCGAG";
        secStructureDpRNA(r, alpha1, dp);
        printStructure(r, alpha1, dp);
        cout << dp[0][sz(r)-1] << '\n';
        secStructureDpRNA(r, alpha2, dp);
        printStructure(r, alpha2, dp);
        cout << dp[0][sz(r)-1] << '\n';
    }
}

signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    // int t;
    // cin >> t;
    // while (t--)
        solve();
    
}
