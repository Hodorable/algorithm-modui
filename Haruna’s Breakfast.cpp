/**************************************************************
    Coder: hodorable
    Language: C++
    Problem: www.lydsy.com/JudgeOnline/problem.php?id=4129
****************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define eps 1e-8
#define inf 0x7f3f3f3f
#define debug puts("BUG")

#define read freopen("in","r",stdin)
#define N 50010
int a[N];
vector<int>vc[N];
struct query
{
    int u, v, tm, id;
}q[N];
struct change
{
    int u, v;
}c[N];
int bin[17];
int bl[N], st[N];
int dep[N],fa[N][17];
int top, cnt;
bool operator<(query a, query b)
{
    if (bl[a.u] == bl[b.u])
    {
        if (bl[a.v] == bl[b.v])
            return a.tm < b.tm;
        return bl[a.v] < bl[b.v];
    }
    return bl[a.u] < bl[b.u];
}
void dfs(int u, int f, int b)
{
    int bot = top;
    dep[u] = dep[f] + 1;
    fa[u][0] = f;
    for (int i = 1; i < 17; ++i)
        if (dep[u] >= bin[i]) fa[u][i] = fa[fa[u][i-1]][i-1];
        else break;
    for (size_t i = 0; i < vc[u].size(); ++i)
    {
        int v = vc[u][i];
        if (v == f) continue;
        dfs(v, u, b);
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
int ans[N], sum[N], sum2[N], id[N];
void add(int u, int n)
{
    if (a[u] <= n && sum[a[u]]++ == 0)
        ++sum2[id[a[u]]];
}
void del(int u, int n)
{
    if (a[u] <= n && --sum[a[u]] == 0)
        --sum2[id[a[u]]];
}
void reverse(int u,int n)
{
    if (in[u]) del(u, n);
    else add(u, n);
    in[u] ^= 1;
}
void move(int u, int v, int n)
{
    while (u != v)
    {
        if (dep[u] > dep[v])
        {
            reverse(u, n);
            u = fa[u][0];
        }
        else
        {
            reverse(v, n);
            v = fa[v][0];
        }
    }
}
void rock(int x,int n)
{
    int u = c[x].u, v = c[x].v;
    if (in[u])
    {
        if (a[u] <= n && --sum[a[u]] == 0)
            sum2[id[a[u]]]--;
        if (v <= n && sum[v]++ == 0)
            sum2[id[v]]++;
    }
    swap(c[x].v, a[u]);
}
void roll(int u, int v, int n)
{
    while (u < v) rock(++u, n);
    while (u > v) rock(u--, n);
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
int gao(int sz)
{
    for (int i = 0, j = 0; ;++i, j += sz)
    {
        if (sum2[i] == sz) continue;
        while (sum[j]) j++;
        return j;
    }
    return 0;

}
int main()
{
    //read;
    bin[0] = 1;
    for (int i = 1; i < 17; ++i)
        bin[i] = bin[i-1]<<1;
    int n, m;
    while (~scanf("%d%d",&n,&m))
    {
        for (int i = 1; i <= n; ++i)
            scanf("%d", a+i);
        for (int i = 1; i <= n; ++i)
            vc[i].clear();
        int u, v, t;
        for (int i = 1; i < n; ++i)
        {
            scanf("%d%d", &u, &v);
            vc[u].push_back(v);
            vc[v].push_back(u);
        }
        dep[0] = -1;
        top = cnt = 0;
        int bk = (int)pow(n, 0.67);
        dfs(1, 0, bk);
        while (top) bl[st[top--]] = cnt;
        int nq = 0, nc = 0;
        for (int i = 0; i < m; ++i)
        {
            scanf("%d%d%d",&t,&u,&v);
            if (t == 0) c[nc++] = (change){u, v};
            else q[nq] = (query){u, v, nc-1, nq}, nq++;
        }
//        for (int i = 0; i < nq; ++i)
//            if (bl[q[i].u] > bl[q[i].v]) swap(q[i].u, q[i].v);
        sort(q, q+nq);
        int sz = (int)sqrt(n);
        for (int i = 0; i <= n; ++i)
            id[i] = i / sz;
        memset(sum, 0 ,sizeof(sum));
        memset(sum2, 0, sizeof(sum2));
        memset(in, 0, sizeof(in));
        u = 1, v = 1, t = -1;
        for (int i = 0; i < nq; ++i)
        {
            move(u, q[i].u, n);
            move(v, q[i].v, n);
            roll(t, q[i].tm, n);
            int l = lca(q[i].u, q[i].v);
            reverse(l, n);
            ans[q[i].id] = gao(sz);
            reverse(l, n);
            u = q[i].u, v = q[i].v, t = q[i].tm;
        }
        for (int i = 0; i < nq; ++i)
            printf("%d\n",ans[i]);
    }
    return 0;
}
