#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class String
{
    private:
        char *str;
        size_t length;
        
    public:
        
    //constructors
    String()
    {
        str = nullptr;
        length = 0;
    }
    
    //parameterised constructor
    String(const char *copy_string)
    {
        length = strlen(copy_string);
        str = new char[length+1];
        strcpy(str,copy_string);
    }
    
    //copy constructor
    String(const String& copy_string)
    {
        length = copy_string.length;
        str = new char[length+1];
        strcpy(str,copy_string.str);
    }
    
    //assignment operator
    String& operator= (const String& copy_string)
    {
        if(this != &copy_string)
        {
            delete []str;
            length = copy_string.length;
            str = new char[length+1];
            strcpy(str,copy_string.str);
        }
        return *this;
    }
    
    //concatenation
    String operator+ (const String& copy_string)
    {
        String new_string;
        new_string.length = length+copy_string.length;
        new_string.str = new char[new_string.length+1];
        strcpy(new_string.str,str);
        strcat(new_string.str,copy_string.str);
        
        return new_string;
    }
    
    size_t get_length()
    {
        return length;
    }
    
    void print_string()
    {
        cout<<str<<"\n";
    }
    
     //destructor
    ~String()
    {
        delete []str;
    }
};

int main()
{
    String str1("Hello ");
    String str2("World !!");
    String str3 = str1+str2;
    str3.print_string();
}
