#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    
    string str = "abcde";
    string s = str;
    rotate(s.begin(), s.begin() + 1, s.end());
    cout << str << endl;
    cout << s << endl;
    return 0;
}