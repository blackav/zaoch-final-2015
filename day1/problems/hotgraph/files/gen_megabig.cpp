#include <cstdio>
#include <map>
#include "testlib.h"
#include "mostdist.h"
using namespace std;

#define eprintf(...) fprintf(stderr, __VA_ARGS__)

map<string, string> get_args(char argc, char* argv[])
{
    map<string, string> res;
    res["n"] = "100000"; // 1e5
    res["m"] = "1000000"; // 1e6
    res["q"] = "10";
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

    int n = atoi(args["n"].c_str());
    int m = atoi(args["m"].c_str());
    int q = atoi(args["q"].c_str());
    vector<edge> edges;
    int sep = 2 * q;
    
    for (int i = 0; i < sep; i++)
    {
        int a = 0;
        int b = 1 + i;
        int t = (i < q) ? 0 : (m - 2 * q + 1);
        edges.push_back(edge(a, b, t));
    }

    for (int i = 0; i < m - sep; i++)
    {
        int a = 0;
        int b = 1 + sep + i % (n - sep - 1);
        int t = i + 1;
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
        int a = i + 1;
        int b = i + q + 1;
        int d = 1;
        printf("%d %d %d\n", ord[a], ord[b], d); 
    }
}
