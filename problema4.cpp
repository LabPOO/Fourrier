#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
ifstream fin("date.in");
int main()
{

    char a[100],s[100];
    int n=0;
    while(fin.getline(a,100))
    {
        n++;
        cout<<n<<" "<<a<<endl;
    }

    return 0;
}
