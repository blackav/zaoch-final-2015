#include <cstdio>
#include <map>
#include "testlib.h"
#include "mostdist.h"
using namespace std;

#define eprintf(...) fprintf(stderr, __VA_ARGS__)

map<string, string> get_args(char argc, char* argv[])
{
    map<string, string> res;
    res["m"] = "1000000"; // 1e6
    res["factor"] = "0.01";
    res["q"] = "10";
    res["v"] = "1000000000"; // 1e9
    res["ld"] = "0";
    res["rd"] = "50000";
    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            char* pt = argv[i];
            while (*pt == '-')
                ++pt;
            if (i + 1 == argc || argv[i + 1][0] == '-')
                res[pt];
            else
                res[pt] = argv[i + 1];
        }
    }
    for (map<string, string>::iterator it = res.begin(); it != res.end(); it++)
        eprintf("%s -> %s\n", it->first.c_str(), it->second.c_str());
    if (res.find("help") != res.end())
        exit(0);
    return res;
}

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);
    map<string, string> args = get_args(argc, argv);

    int m = atoi(args["m"].c_str());
    double factor = atof(args["factor"].c_str());
    int q = atoi(args["q"].c_str());
    int v = atoi(args["v"].c_str());
    int ld = atoi(args["ld"].c_str());
    int rd = atoi(args["rd"].c_str()); 
    vector<edge> edges;
    int n = 1;
    for (int i = 0; i < m; i++)
    {
        int a = 0;
        int b = 0;
        int t = rnd.next(-v, v);
        if (rnd.next(0, 1000 * 1000 * 1000 - 1) < factor * 1e9)
        {
            b = rnd.next(1, n);
            n = max(n, b + 1);
        }
        edges.push_back(edge(a, b, t));
    }
    vector<int> ord(n);
    for (int i = 0; i < n; i++)
        ord[i] = i + 1;
    shuffle(ord.begin(), ord.end());
    for (int i = 0; i < m; i++)
    {
        if (rnd.next(0, 1))
            swap(edges[i].a, edges[i].b);
        edges[i].a = ord[edges[i].a];
        edges[i].b = ord[edges[i].b];
    }
    sort(edges.begin(), edges.end());
    printf("%d %d\n", n, m);
    for (int i = 0; i < m; i++)
        printf("%d %d %d\n", edges[i].a, edges[i].b, edges[i].t);
    printf("%d\n", q);
    for (int i = 0; i < q; i++)
    {
        int a = ord[rnd.next(0, n - 1)];
        int d = rnd.next(ld, rd);
        int b = mostdist(n, m, ord[a], edges, d);
        printf("%d %d %d\n", a, b, d); 
    }
}
