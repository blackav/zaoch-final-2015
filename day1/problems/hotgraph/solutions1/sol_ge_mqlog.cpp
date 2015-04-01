#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define fs first
#define sc second
#define left dsklf
#define right sdlkfj

const double pi = acos(-1.0);
const int vsize = 100 * 1000;
const int esize = 1000 * 1000;
const int inf = 1000 * 1000 * 1000;

int getnearest(int* ptr, int v) {
	if (v == -1 || ptr[v] == v)
		return v;

	ptr[v] = getnearest(ptr, ptr[v]);
	return ptr[v];
}

int n, m, q;
vector <pair <int, int> > vertex[vsize];
int* left[vsize];
int* right[vsize];
int* temps[vsize];
int* edgenum[vsize];
int numv[2 * esize];
int locps[2 * esize];
int dist[2 * esize];
int len[vsize];

int bfs(int start, int finish, int diff) {
	for (int i = 0; i < 2 * m; i++) {
		dist[i] = inf;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < len[i]; j++) {
			left[i][j] = j;
			right[i][j] = j;
		}

	queue <int> q;
   	for (int i = 0; i < len[start]; i++) {
//   		cerr << start << ' ' << i << ' ' << edgenum[start][i] << endl;
   		dist[edgenum[start][i] ^ 1] = 1;
   		q.push(edgenum[start][i] ^ 1);

 		left[start][i] = -1;
 		right[start][i] = -1;
   	}

   	while (!q.empty()) {
   		int edge = q.front();
   		int myv = numv[edge];
   		if (myv == finish)
   			return dist[edge];
   		int myps = locps[edge];
 //  		cerr << start << ' ' << edge << ' ' << myv << ' ' << myps << endl;
   		q.pop();
   		for (int i = 0; i < 2; i++) {
   			while (true) {
   				int nrs;
   				if (i == 0) 
   					nrs = getnearest(left[myv], myps);
   				else
   					nrs = getnearest(right[myv], myps);
   				if (nrs == -1 || abs(temps[myv][myps] - temps[myv][nrs]) > diff)
   					break;

   				dist[edgenum[myv][nrs] ^ 1] = dist[edge] + 1;
   				q.push(edgenum[myv][nrs] ^ 1);
   				left[myv][nrs] = nrs - 1;
   				right[myv][nrs] = nrs + 1;
   				if (nrs + 1 == len[myv])
   					right[myv][nrs] = -1;
   			}
   	   	}   	
   	}

   	return -1;
}

int main() {
    int v, u, temp;
    
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int d;
	scanf("%d%d%d", &n, &m, &d);
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &v, &u, &temp);
		v--, u--;

		numv[2 * i] = v;
		locps[2 * i] = vertex[v].size();
		numv[2 * i + 1] = u;
		locps[2 * i + 1] = vertex[u].size();

		vertex[v].pb(mp(2 * i, temp));
		vertex[u].pb(mp(2 * i + 1, temp));
	}

	for (int i = 0; i < n; i++) {
		len[i] = vertex[i].size();
		left[i] = new int[len[i]];
		right[i] = new int[len[i]];
        edgenum[i] = new int[len[i]];     
		temps[i] = new int[len[i]];
		
		for (int j = 0; j < len[i]; j++) {
			edgenum[i][j] = vertex[i][j].fs;
			temps[i][j] = vertex[i][j].sc;
		}
	}

	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		scanf("%d%d", &v, &u);
		v--, u--;

		if (v == u) {
			printf("0\n");
			continue;
		}

		printf("%d\n", bfs(v, u, d));
	} 

    return 0;
}
