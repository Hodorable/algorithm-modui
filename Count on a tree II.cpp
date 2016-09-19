/**************************************************************
    Coder: hodorable
    Language: C++
    Problem: http://www.spoj.com/problems/COT2/
****************************************************************/
#include <bits/stdc++.h>

using namespace std;
typedef long long  ll;

#define eps 1e-8
#define inf 0x7f3f3f3f
#define debug puts("BUG")

#define read freopen("in","r",stdin)
#define N 40010
#define M 100010
vector<int>vc[N];
struct node
{
    int l, r, dx;
}nd[M];
int a[N],b[N];
int dep[N],fa[N][17];
int bl[N],st[N],dfn[N];
int bin[17];
int cnt, top, ind;
bool operator<(node a, node b)
{
    if (bl[a.l] == bl[b.l])
        return dfn[a.r] < dfn[b.r];
    return bl[a.l] < bl[b.l];
}
void dfs(int u, int f, int b)
{
    int bot = top;
    dfn[u] = ++ind;
    dep[u] = dep[f] + 1;
    fa[u][0] = f;
    for (int i = 1; i <= 16; ++i)
        if (dep[u] >= bin[i]) fa[u][i] = fa[fa[u][i-1]][i-1];
        else break;
    for (size_t i = 0; i < vc[u].size(); ++i)
    {
        int v = vc[u][i];
        if (v == f) continue;
        dfs(v,u,b);
        if (top - bot >= b)
        {
            cnt++;
            while (top != bot)
                bl[st[top--]] = cnt;
        }
    }
    st[++top] = u;
}
bool in[N];
int ans[M], sum[N], res;
void add(int u)
{
    if (sum[a[u]]++ == 0) ++res;
}
void del(int u)
{
    if (--sum[a[u]] == 0) --res;
}
void reverse(int u)
{
    if (in[u]) del(u);
    else add(u);
    in[u] ^= 1;
}
void move(int u, int v)
{
    while (u != v)
    {
        if (dep[u] > dep[v])
        {
            reverse(u);
            u = fa[u][0];
        }
        else
        {
            reverse(v);
            v = fa[v][0];
        }
    }
}
int lca(int u, int v)
{
    if (dep[u] < dep[v]) swap(u, v);
    int t = dep[u]-dep[v];
    for (int i = 0; bin[i] <= t; ++i)
        if (t & bin[i]) u = fa[u][i];
    for (int i = 16; i >= 0; --i)
        if (fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }
    return u == v ? u : fa[u][0];
}
int main()
{
    //read;
    int n, m;
    bin[0] = 1;
    for (int i = 1; i < 17; ++i)
        bin[i] = (bin[i-1]<<1);
    while (~scanf("%d%d",&n,&m))
    {
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", a+i);
            b[i] = a[i];
        }
        sort(b+1,b+1+n);
        for (int i = 1; i <= n; ++i)
            a[i] = lower_bound(b+1,b+1+n,a[i]) - b;

        for (int i = 1; i <= n; ++i)
            vc[i].clear();
        int u, v;
        for (int i = 1; i < n; ++i)
        {
            scanf("%d%d",&u, &v);
            vc[u].push_back(v);
            vc[v].push_back(u);
        }
        int bk = (int)sqrt(n);
        top = cnt  = ind = 0;
        dep[0] = -1;
        dfs(1, 0, bk);
        while (top)
            bl[st[top--]] = cnt;
        for (int i = 0; i < m; ++i)
        {
            scanf("%d%d",&u,&v);
            //if (dfn[u] > dfn[v]) swap(u, v);
            nd[i].l = u;
            nd[i].r = v;
            nd[i].dx = i;
        }
        sort(nd, nd+m);
        memset(sum, 0, sizeof(sum));
        res = 0;
        int l = 1, r = 1;
        for (int i = 0; i < m; ++i)
        {
            move(nd[i].l, l);
            move(nd[i].r, r);
            int t = lca(nd[i].l, nd[i].r);
            reverse(t);
            ans[nd[i].dx] = res;
            reverse(t);
            l = nd[i].l, r = nd[i].r;
        }
        for (int i = 0; i < m; ++i)
            printf("%d\n",ans[i]);
    }
    return 0;
}