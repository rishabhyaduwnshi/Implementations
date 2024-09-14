#include <bits/stdc++.h>
using namespace std;

mutex mtx;
condition_variable cv;
bool print_hello_turn = true;

void print_hello()
{
    for(int i=0;i<5;i++)
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock,[]{return print_hello_turn;});
        cout<<"Hello"<<endl;
        print_hello_turn = false;
        cv.notify_all();
    }
}

void print_world()
{
    for(int i=0;i<5;i++)
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock,[]{return !print_hello_turn;});
        
        cout<<"World"<<endl;
        print_hello_turn = true;
        cv.notify_all();
    }
}


int main()
{
    thread t1(print_hello);
    thread t2(print_world);
    t1.join();
    t2.join();
}
