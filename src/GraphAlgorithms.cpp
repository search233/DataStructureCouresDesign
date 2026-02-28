#include "../include/GraphAlgorithms.h"
#include "../include/Utils.h"
#include <queue>
#include <set>
#include <cmath>
#include <climits>
#include <algorithm>
#include <unordered_set>
#include <map>

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

    // map city id -> index for DSU
    map<int,int> id2idx;
    for(size_t i=0;i<ids.size();++i) id2idx[ids[i]] = (int)i;

    DSU dsu((int)ids.size());
    for(auto& e : edges) {
        int iu = id2idx[e.u];
        int iv = id2idx[e.v];
        if(dsu.un(iu,iv))
            result.emplace_back(e.u,e.v);
    }

    return result;
}


// 最近邻贪心 + 简单 2-opt 局部搜索
std::vector<int>
GraphAlgorithms::tspNearestNeighbor(int start, bool returnToStart) const {
    std::vector<int> ids = graph.getAllCityIds();
    std::unordered_set<int> exist(ids.begin(), ids.end());
    if (!exist.count(start) || ids.empty()) return {};

    std::vector<int> route;
    route.reserve(ids.size() + (returnToStart?1:0));

    int cur = start;
    route.push_back(cur);
    std::unordered_set<int> visited;
    visited.insert(cur);

    while(visited.size() < ids.size()) {
        int next = -1;
        int bestd = INT_MAX;
        auto curCity = graph.getCity(cur).value();

        for(int id : ids) {
            if(visited.count(id)) continue;
            auto c = graph.getCity(id).value();
            int d = Utils::calDistance(curCity, c);
            if(d < bestd) { bestd = d; next = id; }
        }

        if(next == -1) break;
        route.push_back(next);
        visited.insert(next);
        cur = next;
    }

    if(returnToStart) route.push_back(start);

    auto tourLen = [&](const std::vector<int>& r)->int{
        if(r.size() <= 1) return 0;
        int sum = 0;
        for(size_t i=0;i+1<r.size();++i) {
            auto a = graph.getCity(r[i]).value();
            auto b = graph.getCity(r[i+1]).value();
            sum += Utils::calDistance(a,b);
        }
        return sum;
    };

    // 2-opt improvement
    bool improved = true;
    int maxIter = 1000;
    while(improved && maxIter--) {
        improved = false;
        size_t n = route.size();
        // if returnToStart, last == first; allow swapping on cycle
        for(size_t i=0;i+2<n && !improved; ++i) {
            for(size_t k=i+2;k+1<n && !improved; ++k) {
                // build new route with segment (i+1..k) reversed
                std::vector<int> nr = route;
                std::reverse(nr.begin() + (i+1), nr.begin() + (k+1));
                if(tourLen(nr) < tourLen(route)) {
                    route.swap(nr);
                    improved = true;
                }
            }
        }
    }

    return route;
}


// Steiner 近似：将问题视作在给定城市点上的完全图求最小生成树（不显式添加辅助点）
std::vector<Edge>
GraphAlgorithms::steinerApproxMST() const {
    std::vector<Edge> result;
    auto ids = graph.getAllCityIds();

    struct FullEdge { int u,v,w; };
    std::vector<FullEdge> edges;

    for(size_t i=0;i<ids.size();++i)
        for(size_t j=i+1;j<ids.size();++j) {
            auto c1 = graph.getCity(ids[i]).value();
            auto c2 = graph.getCity(ids[j]).value();
            int w = Utils::calDistance(c1, c2);
            edges.push_back({ids[i], ids[j], w});
        }

    sort(edges.begin(), edges.end(), [](auto &a, auto &b){ return a.w < b.w; });

    std::map<int,int> id2idx;
    for(size_t i=0;i<ids.size();++i) id2idx[ids[i]] = (int)i;

    DSU dsu((int)ids.size());
    for(auto &e : edges) {
        int iu = id2idx[e.u];
        int iv = id2idx[e.v];
        if(dsu.un(iu, iv))
            result.emplace_back(e.u, e.v);
    }

    return result;
}