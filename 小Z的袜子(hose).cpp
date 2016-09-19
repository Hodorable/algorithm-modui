/**************************************************************
    Coder: hodorable
    Language: C++
    Problem: www.lydsy.com/JudgeOnline/problem.php?id=2038
****************************************************************/

#include <map>
#include <set>
#include <list>
#include <queue>
#include <stack>
#include <cmath>
#include <ctime>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long  ll;
 
#define eps 1e-8
#define inf 0x7f3f3f3f
#define debug puts("BUG")
 
#define read freopen("in.txt","r",stdin)
#define write freopen("out.txt","w",stdout)
 
#define maxn 51000
int col[maxn],pos[maxn];
ll fz[maxn],fm[maxn];
int num[maxn];
struct str
{
    int l,r,id;
}nd[maxn];
bool cmp(str a, str b)
{
    if (pos[a.l] == pos[b.l])
        return a.r < b.r;
    return pos[a.l] < pos[b.l];
}
ll gcd(ll a, ll b)
{
    if (b) return gcd(b,a%b);
    return a;
}
void update(int x,int d,ll &ans)
{
    ans -= 1LL*num[col[x]]*num[col[x]];
    num[col[x]] += d;
    ans += 1LL*num[col[x]]*num[col[x]];
}
int main()
{
    //read;
    int n,m;
    while (~scanf("%d%d",&n,&m))
    {
        int bk = (int)ceil(sqrt(1.0*n));
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", col+i);
            pos[i] = i / bk;
        }
        int l,r;
        for (int i = 0; i < m; ++i)
        {
            scanf("%d%d",&l,&r);
            nd[i].l = l-1;
            nd[i].r = r-1;
            nd[i].id = i;
        }
        sort(nd,nd+m,cmp);
        l = 0, r = 0;
        memset(num,0,sizeof(num));
        num[col[0]] = 1;
        ll ans = 1;
        for (int i = 0; i < m; ++i)
        {
            int id = nd[i].id;
            if (nd[i].l == nd[i].r)
            {
                fz[id] = 0, fm[id] = 1;
                continue;
            }
            while (r < nd[i].r) update(++r,1,ans);
            while (r > nd[i].r) update(r--,-1,ans);
            while (l < nd[i].l) update(l++,-1,ans);
            while (l > nd[i].l) update(--l,1,ans);
            ll f1 = ans-nd[i].r+nd[i].l-1;
            ll f2 = 1LL*(nd[i].r-nd[i].l)*(nd[i].r-nd[i].l+1);
            //printf("%d %I64d %I64d %I64d\n",id,ans,f1,f2);
            ll g = gcd(f1,f2);
            fz[id] = f1/g, fm[id] = f2/g;
        }
        for (int i = 0; i < m; ++i)
            printf("%lld/%lld\n",fz[i],fm[i]);
    }
    return 0;
}