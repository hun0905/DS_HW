#include <iostream>
#include <string>
using namespace std;
class String
{
public:
    String(string str);
    ~String();
    void FailureFunction();
    void OutFailureFunction();
    void Delete(int start,int length);
    void CharDelete(char c);
    void OutString();
    int FastFind(String pat);
    int *f;

private:
    int Length();
    string s;
};
String::String(string str)
{
    s = str;
    f = new int[s.length()];
    FailureFunction();
}
String::~String()
{

}
void String::Delete(int start,int length)
{
    string tmp;
    for(int i = 0 ; i < Length() ; ++i)
    {
        if(i<start||i>=start+length)
            tmp+=s[i];
    }
    s = tmp;
}
void String::CharDelete(char c)
{
    string tmp;
    for(int i = 0 ; i < Length() ; ++i)
    {
        if(s[i]!=c)
            tmp+=s[i];
    }
    s = tmp;
}
void String::OutString()
{
    cout<<s<<endl;
}
int String::Length()
{
    return s.length();
}
void String ::FailureFunction()
{

    int lengthP = Length();
    f[0] = -1;
    for (int j = 1; j < lengthP; j++)
    {
        int i = f[j - 1];
        while ((s[j] != s[i + 1]) && (i >= 0))
            i = f[i];
        if (s[j] == s[i + 1])
            f[j] = i + 1;
        else
            f[j] = -1;
    }
}
void String ::OutFailureFunction()
{
    for (int i = 0; i < Length(); i++)
    {
        cout << f[i];
        if (i != Length() - 1)
            cout << ' ';
    }
    cout << endl;
}
int String::FastFind(String pat)
{
    int posP = 0, posS = 0;
    int lengthP = pat.Length(), lengthS = Length();
    while ((posP < lengthP) && (posS < lengthS))
    {
        if (pat.s[posP] == s[posS])
        {
            posP++;
            posS++;
        }
        else
        {
            if (posP == 0)
                posS++;
            else
                posP = pat.f[posP - 1] + 1;
        }
    }
    if (posP < lengthP)
        return -1;
    else
        return posS - lengthP;
}
int main()
{
    string str,sub_str;
    cout<<"輸入字串"<<endl;
    getline(cin,str);
    String s(str);
    char c;
    cout<<"輸入要刪除的字元"<<endl;
    cin>>c;
    s.CharDelete(c);
    s.OutString();
    /*String pat(sub_str);
    cout<<"輸入要找的子字串"<<endl;
    getline(cin,sub_str);
    if(s.FastFind(pat)!= -1)
        cout << s.FastFind(pat)<<endl;
    else
        cout<<"搜尋的子字串不存在"<<endl;*/

    return 0;
}

