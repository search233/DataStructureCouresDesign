#include "../include/GraphAlgorithms.h"
#include "../include/Utils.h"
#include <queue>
#include <set>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;

GraphAlgorithms::GraphAlgorithms(const Graph& g): graph(g) {}

bool GraphAlgorithms::isConnected() const {

    auto ids = graph.getAllCityIds();
    if (ids.empty()) return true;

    set<int> visited;
    queue<int> q;

    q.push(ids[0]);
    visited.insert(ids[0]);

    while(!q.empty()) {
        int u = q.front(); q.pop();

        for(auto [v,w] : graph.getNeighbors(u)) {
            if(!visited.count(v)) {
                visited.insert(v);
                q.push(v);
            }
        }
    }

    return visited.size() == ids.size();
}

// Dijkstra
unordered_map<int,int>
GraphAlgorithms::dijkstra(int start) const {

    unordered_map<int,int> dist;
    auto ids = graph.getAllCityIds();

    for(int id : ids)
        dist[id] = INT_MAX;

    dist[start] = 0;

    using P = pair<int,int>; // (dist,node)
    priority_queue<P, vector<P>, greater<P>> pq;

    pq.push({0,start});

    while(!pq.empty()) {
        auto [d,u] = pq.top();
        pq.pop();

        if(d > dist[u]) continue;

        for(auto [v,w] : graph.getNeighbors(u)) {
            if(dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

struct DSU{
	int n;
	vector<int>fa, sz;

	DSU(int n){
		init(n);
	}

	void init(int n){
		this -> n = n;
		fa.assign(n + 5, 0);
		sz.assign(n + 5, 1);
		for(int i = 0; i <= n; i++)fa[i] = i;
	}

	int find(int k){
		return k == fa[k] ? k : fa[k] = find(fa[k]);
	}

	bool same(int u, int v){
		return find(u) == find(v);
	}

	bool un(int u, int v){
		u = find(u); v = find(v);
		if(u == v)return false;
		sz[u] += sz[v];
		fa[v] = u;
		return true;
	}


	int size(int x){
		return sz[find(x)];
	}

};

vector<Edge>
GraphAlgorithms::kruskal() const {

    vector<Edge> result;
    auto ids = graph.getAllCityIds();

    struct FullEdge {
        int u,v,w;
    };

    vector<FullEdge> edges;

    // 构造完全图
    for(size_t i=0;i<ids.size();++i)
        for(size_t j=i+1;j<ids.size();++j) {

            auto c1 = graph.getCity(ids[i]).value();
            auto c2 = graph.getCity(ids[j]).value();

            int w = Utils::calDistance(c1, c2);
            edges.push_back({ids[i],ids[j],w});
        }

    sort(edges.begin(),edges.end(),
         [](auto&a,auto&b) -> bool {
            return a.w<b.w;});

    DSU dsu(ids.size());
    for(auto& e : edges)
        if(dsu.un(e.u,e.v))
            result.emplace_back(e.u,e.v);

    return result;
}