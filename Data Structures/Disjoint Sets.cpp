#include <bits/stdc++.h>
using namespace std;

class disjoint_sets
{
    private:
        vector<int> rank;
        vector<int> size;
        vector<int> parent;
    public:
        disjoint_sets(int n)
        {
            rank.resize(n+1,0);
            parent.resize(n);
            size.resize(n+1);
            for(int i=0;i<n;i++)
            {    
                parent[i] = i;
                size[i] = 1;
            }
        }
        
        int find_final_parent(int node)
        {
            if(node == parent[node])
                return node;
            //recursively finds the final parent and do path compression
            return parent[node] = find_final_parent(parent[node]);
        }
        
        void union_by_rank(int u, int v)
        {
            //find final parents of u and v
            int final_parent_u = find_final_parent(u);
            int final_parent_v = find_final_parent(v);
            
            //if they both have same parent, don't need to do anything
            if(final_parent_u == final_parent_v)
                return;
            
            if(rank[final_parent_u] < rank[final_parent_v])
            {
                parent[final_parent_u] = final_parent_v;
            }
            else if(rank[final_parent_u] > rank[final_parent_v])
            {
                parent[final_parent_v] = final_parent_u;
            }
            //when both have same rank, one will get attached to another and rank will increase
            else
            {
                parent[final_parent_v] = final_parent_u;
                rank[final_parent_u]++;
            }
        }
        
        void union_by_size(int u, int v)
        {
            //find final parents of u and v
            int final_parent_u = find_final_parent(u);
            int final_parent_v = find_final_parent(v);
            
            //if they both have same parent, don't need to do anything
            if(final_parent_u == final_parent_v)
                return;
            
            if(size[final_parent_u] < size[final_parent_v])
            {
                parent[final_parent_u] = final_parent_v;
                size[final_parent_v] += final_parent_u;
            }
            else
            {
                parent[final_parent_v] = final_parent_u;
                size[final_parent_u] += final_parent_v;
            }
        }
};


int main()
{
    disjoint_sets d1(5);
}
