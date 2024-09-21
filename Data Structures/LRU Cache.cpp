#include <bits/stdc++.h>
using namespace std;

class Node
{
    public:
        Node* next;
        Node* prev;
        int value;
        int key;
        Node(int k, int v) : value(v), key(k), next(nullptr), prev(nullptr){}
};

class LRUCache
{
    private:
        int capacity;
        unordered_map<int,Node*> cache_map;
        Node* head;
        Node* tail;
        
        //removing the current node from list
        void remove_node(Node* current_node)
        {
            Node* prev_node = current_node->prev;
            Node* next_node = current_node->next;
            prev_node->next = next_node;
            next_node->prev = prev_node;
        }
        
        //adding the current_node to front
        void add_node_to_front(Node* current_node)
        {
            current_node->next = head->next;
            current_node->prev = head;
            head->next->prev = current_node;
            head->next = current_node;
        }
    
        
    public:
        LRUCache(int cap) : capacity(cap)
        {
            head = new Node(0,0);
            tail = new Node(0,0);
            head->next = tail;
            tail->prev = head;
        }
        
        int get(int key)
        {
            if(cache_map.find(key) == cache_map.end())
                return -1;
            
            Node* current_node = cache_map[key];
            remove_node(current_node);
            add_node_to_front(current_node);
            return current_node->value;
        }
        
        void put(int key, int value)
        {
            if(cache_map.find(key) != cache_map.end())
            {
                Node* current_node = cache_map[key];
                current_node->value = value;
                remove_node(current_node);
                add_node_to_front(current_node);
            }
            else
            {
                if(cache_map.size() == capacity)
                {
                    Node* lru = tail->prev;
                    remove_node(lru);
                    cache_map.erase(lru->key);
                    delete lru;
                }
                
                Node* new_node = new Node(key,value);
                add_node_to_front(new_node);
                cache_map[key] = new_node;
            }
        }
        
        ~LRUCache()
        {
            Node* current_node = head;
            while(current_node != nullptr)
            {
                Node* next_node = current_node->next;
                delete(current_node);
                current_node = next_node;
            }
        }
};

int main()
{
    LRUCache l1(5);
}
