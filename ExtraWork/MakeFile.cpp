#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main()
{
    string str;
    fstream iofile("file.txt",ios::out);
    cout<<"enter some strings";
    while(1)
    {
        cin>>str;
        if(str=="end")
        {
        break;
        }
        iofile<<str<<endl;
    }
    iofile.close();
    ifstream iofile2("file.txt",ios::in);
    iofile2>>str;
    while(!iofile2.eof())
    {
        cout<<str<<endl;
        iofile2>>str;
    }
    return 0;
}