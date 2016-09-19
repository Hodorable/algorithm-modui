/**************************************************************
    Coder: hodorable
    Language: C++
    Problem: www.lydsy.com/JudgeOnline/problem.php?id=3289
****************************************************************/
 
#include <bits/stdc++.h>
using namespace std;
 
#define N 50050
#define read freopen("in","r",stdin)
struct node
{
    int b,l,r,dx;
    bool operator <(const node &n) const
    {
        if (b == n.b)
            return r < n.r;
        return b < n.b;
    }
}nd[N];
int a[N],b[N];
int c[N];
int ans[N];
int lowbit(int k)
{
    return (k&-k);
}
void update(int pos, int num, int n)
{
    while (pos <= n)
    {
        c[pos] += num;
        pos += lowbit(pos);
    }
}
int sum(int pos)
{
    int s = 0;
    while (pos > 0)
    {
        s += c[pos];
        pos -= lowbit(pos);
    }
    return s;
}
int main()
{
    //read;
    int n, q;
    while (~scanf("%d",&n))
    {
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d",a+i);
            b[i] = a[i];
        }
        sort(b+1,b+n+1);
        int t = 0;
        for (int i = 1; i <= n; ++i)
        {
            a[i] = lower_bound(b+1,b+1+n,a[i])-b;
            t = max(a[i], t);
        }
        scanf("%d",&q);
        int bk = (int)sqrt(n);
        for (int i = 0; i < q; ++i)
        {
            scanf("%d%d",&nd[i].l, &nd[i].r);
            nd[i].b = (nd[i].l-1) / bk + 1;
            nd[i].dx = i;
        }
        sort(nd,nd+q);
        memset(c, 0, sizeof(c));
        int x = 0, l = 1, r = 0;
        for (int i = 0; i < q; ++i)
        {
            int dx = nd[i].dx;
            if (nd[i].l == nd[i].r)
            {
                ans[dx] = 0;
                continue;
            }
            while (r < nd[i].r)
            {
                r++;
                int p = a[r];
                x += sum(t)-sum(p);
                update(p,1,t);
            }
            while (r > nd[i].r)
            {
                int p = a[r];
                x -= sum(t)-sum(p);
                update(p,-1,t);
                r--;
            }
            while (l > nd[i].l)
            {
                l--;
                int p = a[l];
                x += sum(p-1);
                update(p,1,t);
            }
            while (l < nd[i].l)
            {
                int p = a[l];
                x -= sum(p-1);
                update(p,-1,t);
                l++;
            }
            ans[nd[i].dx] = x;
        }
        for (int i = 0; i < q; ++i)
            printf("%d\n",ans[i]);
    }
    return 0;
}