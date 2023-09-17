#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;


enum class LogLevel
{
    INFO,
    WARNING,
    ERROR
};

class Logger
{
    private:
        ofstream logfile;
        
    public:
        
        //constructor
        Logger(const string filename)
        {
            logfile.open(filename,ios::app);
            if(logfile.is_open() == false)
            {
                cerr<<"Could not open log file\n";
            }
        }
        
        void Log(LogLevel level, const string message)
        {
            if(logfile.is_open() == false)
            {
                cerr<<"Error opening log file\n";
                return;
            }
            
            time_t current_time = time(nullptr);
            string time_stamp = ctime(&current_time);
            time_stamp.pop_back();
            
            string log_level_string;
            
            switch(level)
            {
                case LogLevel::INFO:
                    log_level_string = "INFO";
                    break;
                
                case LogLevel::WARNING:
                    log_level_string = "WARNING";
                    break;
                    
                case LogLevel::ERROR:
                    log_level_string = "ERROR";
                    break;
            }
            
            logfile<<"["<<time_stamp<<"] ["<< log_level_string << "] ["<<message<<" ]"<<endl;
        }
        
        //destructor
        ~Logger()
        {
            if(logfile.is_open() == true)
            logfile.close();
        }
};

int main()
{
    Logger logfile("logfile.txt");
    logfile.Log(LogLevel::INFO,"This is INFO message");
    
}
