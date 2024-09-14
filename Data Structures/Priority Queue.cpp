#include <bits/stdc++.h>
using namespace std;

class Priority_Queue
{
    private:
        int array[100];
        int size = 0;
    
    public:
        Priority_Queue()
        {
            array[0] = -1;
            size = 0;
        }
        void push(int value)
        {
            size++;
            int index = size;
            array[index] = value;
            
            while(index > 1)
            {
                int parent_index = floor(index/2);
                if(array[parent_index] < array[index])
                {
                    swap(array[parent_index],array[index]);
                    index = parent_index;
                }
                else
                    return;
            }
        }
        
        void pop()
        {
            if(size == 0)
                return;
            
            //copy the last node data to first node and decrement the size
            array[1] = array[size];
            size--;
            
            //now make sure every element follows the max heap property
            int parent_index = 1;
            while(parent_index < size)
            {
                int left_child_index = 2*parent_index;
                int right_child_index = 2*parent_index+1;
                
                if(left_child_index < size && array[parent_index] < array[left_child_index])
                {
                    swap(array[parent_index],array[left_child_index]);
                    parent_index = left_child_index;
                }
                else if(right_child_index < size && array[parent_index] < array[right_child_index])
                {
                    swap(array[parent_index],array[right_child_index]);
                    parent_index = right_child_index;
                }
                else
                    return;
            }
            
            
        }
        
        void print_pq()
        {
            for(int i=1;i<=size;i++)
                cout<<array[i]<<" ";
        }
};



int main()
{
    Priority_Queue pq;
    pq.push(50);
    pq.push(55);
    pq.push(53);
    pq.push(52);
    pq.push(54);
    pq.pop();
    pq.pop();
    pq.print_pq();
}
