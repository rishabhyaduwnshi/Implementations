#include <bits/stdc++.h>
using namespace std;


class MessageQueue
{
    private:
        mutex mtx;
        condition_variable cv;
        queue<string> q;
    public:
        MessageQueue() {}
        ~MessageQueue() {}
    
        void enqueue(const string &data)
        {
            //acquire the lock
            unique_lock<mutex> lock(mtx);
            q.push(data);
            //notify the waiting thread
            cv.notify_one();
        }
        
        string dequeue()
        {
            //acquire the lock
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this](){
                return q.empty() == false;
            });
            string current_data = q.front();
            q.pop();
            cv.notify_one();
            return current_data;
        }
        
        bool is_empty()
        {
            unique_lock<mutex> lock(mtx);
            return q.empty() == true;
        }
};

void producer(MessageQueue &mq)
{
    for(int i=0;i<5;i++)
    {
        string message = "Message " + to_string(i);
        cout<<"Producer pushing data : "<<message<<endl;
        mq.enqueue(message);
        this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void consumer(MessageQueue &mq)
{
    for(int i=0;i<5;i++)
    {
        string message = mq.dequeue();
        cout<<"Data read from queue : "<<message<<endl;
        this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}


int main()
{
    MessageQueue mq;
    thread t1(producer,ref(mq));
    thread t2(consumer,ref(mq));
    t1.join();
    t2.join();
}
