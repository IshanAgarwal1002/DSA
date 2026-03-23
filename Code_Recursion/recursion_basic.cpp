#include<iostream>
#include<vector>
using namespace std;

void printInc(int a,int b)
{
    if(a>b)
        return;
    
    cout<<a<<" ";
    printInc(a+1,b);
}

void printDec(int a,int b)
{
    if(a>b)
        return;
    
    printDec(a+1,b);
    cout<<a<<" ";
}

void printIncDec(int a,int b)
{
    if(a>b)
        return;
    
    if(!(a&1))  //even
        cout<<a<<" ";
    printIncDec(a+1,b);
    if(a&1)     //odd
        cout<<a<<" ";
}

int fact(int n)
{
    return (n<=1)?1:n*fact(n-1);
}

int fibo(int n)
{
    if(n<=1)
        return n;
    return fibo(n-1) + fibo(n-2);
}

void fibo2(int a,int b,int n)
{
    if(n==0)
        return;
    cout<<a<<" ";
    fibo2(b,a+b,n-1);
}

int power(int a,int b)
{
    return (b==0)? 1 : a*power(a,b-1);
}

int power2(int a,int b)
{
    if(a==0)    return 0;
    if(b<=0)    return 1;
    int n = power2(a,b/2);
    n*=n;
    return (b&1)?n*a:n;
}

void set1()
{
    int a,b;
    cin>>a>>b;
    // printInc(a,b);
    // printDec(a,b);
    // printIncDec(a,b);
    cout<<power2(a,b);
}

//set2=====================================================

void display(vector <int> &arr,int idx)
{
    if(idx==arr.size())   return;
    cout<<arr[idx]<<" ";
    display(arr,idx+1);
}

bool find(vector <int> &arr,int idx,int data)
{
    if(idx==arr.size())   return false;
    if(arr[idx]==data)
        return true;
    return find(arr,idx+1,data);
}

int maximum(vector <int> &arr,int idx)
{
    if(idx==arr.size()-1) return arr[idx];
    int ans = maximum(arr,idx+1);
    return max(arr[idx],ans);
}

int minimum(vector <int> &arr,int idx)
{
    if(idx==arr.size()-1) return arr[idx];
    int ans = minimum(arr,idx+1);
    return min(arr[idx],ans);
}

//set3==============================================================

vector <string> subsequence1(string str)
{
    if(str.size()==0)
    {
        vector <string> base;
        base.push_back(str);
        return base;
    }

    char ch = str[0];
    vector <string> ans = subsequence1(str.substr(1));
    int n = ans.size();

    for(int i=0;i<n;i++)
    {
        ans.push_back(ch+ans[i]);
    }

    return ans;
}

int subsequence2(string str,string ans)
{
    if(str.size()==0)
    {
        cout<<ans<<"\n";
        return 1;
    }

    int count=0;
    char ch = str[0];

    count += subsequence2(str.substr(1),ans+ch);
    count += subsequence2(str.substr(1),ans);

    return count;
}

vector <string> permutation1(string str)
{
    if(str.size()==1)
    {
        vector <string> base = {str};
        return base;
    }

    char ch = str[0];
    vector <string> ans = permutation1(str.substr(1));
    vector <string> newAns;

    for(string s:ans)
    {
        for(int i=0;i<=s.size();i++)
        {
            newAns.push_back(s.substr(0,i)+ch+s.substr(i));
        }
    }

    return newAns;
}

int permutation2(string str,string ans)
{
    if(str.size()==0)
    {
        cout<<ans<<"\n";
        return 1;
    }

    int count=0;

    for(int i=0;i<str.size();i++)
    {
        char ch = str[i];
        string nstr = str.substr(0,i) + str.substr(i+1);
        count += permutation2(nstr,ans+ch);
    }
    
    return count;
}

int permutation3(string str,string ans)
{
    if(str.size()==0)
    {
        cout<<ans<<"\n";
        return 1;
    }

    int count=0;
    bool alpha[26];

    for(int i=0;i<str.size();i++)
    {
        char ch = str[i];
        if(!alpha[ch - 'a'])
        {
            alpha[ch - 'a'] = true;
            string nstr = str.substr(0,i) + str.substr(i+1);
            count += permutation3(nstr,ans+ch);
        }
    }

    return count;
}

vector<string> words = {":;/", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz", "&*%", "#@$", "+-="};

vector <string> nokiaKeypad1(string str)
{
    if(str.size()==0)
    {
        vector <string> base = {str};
        return base;
    }

    int n = str[0] - '0';
    string word = words[n];
    vector <string> ans = nokiaKeypad1(str.substr(1));
    vector <string> newAns;

    for(string s:ans)
    {
        for(int i=0;i<word.size();i++)
        {
            newAns.push_back(word[i] + s);
        }
    }

    if(str.length() > 1)
    {
        n = n*10 + (str[1] - '0');
        if(n==10 || n == 11)
        {
            word = words[n];
            ans = nokiaKeypad1(str.substr(2));
            for(int i=0;i<word.length();i++)
            {
                for(string s: ans)
                {
                    newAns.push_back(word[i] + s);
                }
            }
        }
    }

    return newAns;
}

int nokiaKeypad2(string str,string ans)
{
    if(str.size()==0)
    {
        cout<<ans<<"\n";
        return 1;
    }

    int count=0;
    int n = str[0] - '0';
    string word = words[n];

    for(int i=0;i<word.size();i++)
    {
        count += nokiaKeypad2(str.substr(1), ans + word[i]);
    }

    if(str.size()>1)
    {
        int num = n*10 + (str[1] - '0');
        if(num==10 || num==11)
        {
            word = words[num];
            for(int i=0;i<word.size();i++)
            {
                count += nokiaKeypad2(str.substr(2), ans + word[i]);
            }
        }
    }

    return count;
}

char alpha[27] = {'-','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

int generateCode1(string str,string ans)
{
    if(str.size()==0)
    {
        cout<<ans<<"\n";
        return 1;
    }

    int count=0;
    int n = str[0] - '0';
    char ch = alpha[n];

    if(ch != '-')
        count += generateCode1(str.substr(1),ans+ch);

    if(str.size()>1)
    {
        int num = n*10 + (str[1] - '0');
        if(num>=10 && num<=26)
        {
            ch = alpha[num];
            count += generateCode1(str.substr(2),ans+ch);
        }
    }

    return count;
}

vector <string> generateCode2(string str)
{
    if(str.size()==0)
    {
        vector <string> base = {str};
        return base;
    }

    int n = str[0] - '0';
    char ch = alpha[n];
    vector <string> ans;
    if(ch != '-')
        ans = generateCode2(str.substr(1));
    vector <string> newAns;

    for(string s:ans)
    {
        newAns.push_back(ch+s);
    }

    if(str.size()>1)
    {
        int num = n*10 + (str[1] - '0');
        if(num>=10 && num<=26)
        {
            ch = alpha[num];
            ans = generateCode2(str.substr(2));
            for(string s:ans)
            {
                newAns.push_back(ch+s);             
            }
        }
    }

    return newAns;
}

void set3()
{
    string str;
    cin>>str;
    // vector <string> ans = subsequence1(str);
    // cout<<subsequence2(str,"");
    // vector <string> ans = permutation1(str);
    // cout<<permutation3(str,"");
    // vector <string> ans = nokiaKeypad1(str);
    // for(string s:ans)
    // {
    //     cout<<s<<"\n";
    // }
    // cout<<nokiaKeypad2(str,"");
    // cout<<generateCode1(str,"");
    vector <string> ans = generateCode2(str);
    for(string s:ans)
    {
        cout<<s<<"\n";
    }
}

void set2()
{
    vector <int> arr = {-1,234,34,7,2,999,23,4,5,6,3,2,5,7,32};
    // display(arr,0);
    // int n;
    // cin>>n;
    cout<<minimum(arr,0);
}

void solve()
{
    // set1();
    // set2();
    set3();
}

int main()
{
    solve();
    return 0;
}