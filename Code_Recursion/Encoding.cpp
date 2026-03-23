#include<iostream>
#include<vector>
using namespace std;

//CryptArithmetic geeksforgeeks

string str1 = "send";
string str2 = "more";
string str3 = "money";

int letters=0;      //bitArray to represent unique characters
vector<int> LetterNumMap(26,0);     //Mapped the code against the character

void uniqueLetters(string str)
{
    for(int i=0;str[i]!='\0';i++)
    {
        int mask = (1 << (str[i] - 'a'));
        letters |= mask;
    }
}

//creates a string of all the unique letters
string createString()
{
    string str = "";
    for(int i=0;i<26;i++)
    {
        int mask = (1 << i);
        if((letters & mask) != 0)
            str += (char)(i + 'a');
    }
    return str;
}

int StringToNum(string &str)
{
    int n=0;
    for(int i=0;i<str[i]!='\0';i++)
    {
        n = n*10 + LetterNumMap[str[i] - 'a'];
    }
    return n;
}

int numUsed = 0;        //bitArray to store the number which is used in encoding

int crypto(string str, int idx)
{
    if(idx == str.length())
    {
        int num1 = StringToNum(str1);
        int num2 = StringToNum(str2);
        int num3 = StringToNum(str3);
        if((num1 + num2 == num3) && (LetterNumMap[str1[0] - 'a'] != 0) && (LetterNumMap[str2[0] - 'a'] != 0) && (LetterNumMap[str3[0] - 'a'] != 0))
        {
            cout<<num1<<"\n+"<<num2<<"\n------\n"<<num3;
            return 1;
        }
        return 0;
    }

    int count = 0;

    for(int num=0;num<=9;num++)
    {
        int mask = (1 << num);
        if((numUsed & mask)==0)
        {
            numUsed ^= mask;
            LetterNumMap[str[idx] - 'a'] = num;
            count += crypto(str,idx+1);
            numUsed ^= mask;
            LetterNumMap[str[idx] - 'a'] = 0;
        }
    }

    return count;
}

int main()
{

    uniqueLetters(str1+str2+str3);

    string str = createString();
    if(str.length()>10)
        cout<<"Encoding not possible.";
    else
        cout<<"\n"<<crypto(str,0);

    return 0;
}