#include<iostream>
#include<vector>
using namespace std;

vector<vector<char>> board{{'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
                           {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
                           {'+', '-', '-', '-', '-', '-', '-', '-', '+', '+'},
                           {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
                           {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
                           {'+', '-', '-', '-', '-', '-', '-', '+', '+', '+'},
                           {'+', '-', '+', '+', '+', '-', '+', '+', '+', '+'},
                           {'+', '+', '+', '+', '+', '-', '+', '+', '+', '+'},
                           {'+', '+', '+', '+', '+', '-', '+', '+', '+', '+'},
                           {'+', '+', '+', '+', '+', '+', '+', '+', '+', '+'}};

vector<string> words = {"AGRA", "NORWAY", "ENGLAND", "GWALIOR"};

bool canPlaceWordH(int r, int c, string &word)
{
    if (c == 0 && word.length() < board[0].size())
    {
        if (board[r][c + word.length()] != '+')
            return false;
    }
    else if ((c + word.length()) == board[0].size() && word.length() != board[0].size())
    {
        if (board[r][c - 1] != '+')
            return false;
    }
    else
    {
        if (((c - 1) >= 0 && board[r][c - 1] != '+') || ((c + word.length()) < board[0].size() && board[r][c + word.length()] != '+'))
            return false;
    }

    for (int i = 0; i < word.length(); i++)
    {
        if ((c + i) < board[0].size() && board[r][c + i] != '-' && board[r][c + i] != word[i])
        {
            return false;
        }
    }
    return true;
}

vector<bool> placeWordH(int r, int c, string &word)
{
    vector<bool> mark(word.length(), false);
    for (int i = 0; i < word.length(); i++)
    {
        if (board[r][c + i] == '-')
        {
            mark[i] = true;
            board[r][c + i] = word[i];
        }
    }
    return mark;
}

void unPlaceWordH(int r, int c, string &word, vector<bool> &mark)
{
    for (int i = 0; i < word.length(); i++)
    {
        if (mark[i])
            board[r][c + i] = '-';
    }
}

bool canPlaceWordV(int r, int c, string &word)
{
    if (r == 0 && r + word.length() < board.size())
    {
        if (board[r + word.length()][c] != '+')
            return false;
    }
    else if ((r + word.length()) == board.size() && word.length() != board.size())
    {
        if (board[r - 1][c] != '+')
            return false;
    }
    else
    {
        if (((r - 1) >= 0 && board[r - 1][c] != '+') || ((r + word.length()) < board.size() && board[r + word.length()][c] != '+'))
            return false;
    }

    for (int i = 0; i < word.length(); i++)
    {
        if ((r + i) < board.size() && board[r + i][c] != '-' && board[r + i][c] != word[i])
        {
            return false;
        }
    }
    return true;
}

vector<bool> placeWordV(int r, int c, string &word)
{
    vector<bool> mark(word.length(), false);
    for (int i = 0; i < word.length(); i++)
    {
        if (board[r + i][c] == '-')
        {
            mark[i] = true;
            board[r + i][c] = word[i];
        }
    }
    return mark;
}

void unPlaceWordV(int r, int c, string &word, vector<bool> &mark)
{
    for (int i = 0; i < word.length(); i++)
    {
        if (mark[i])
            board[r + i][c] = '-';
    }
}

bool crossWord_(int idx)
{
    if (idx == words.size())
    {
        for (vector<char> &ar : board)
        {
            for (char ch : ar)
                cout << ch << " ";
            cout << endl;
        }
        return true;
    }

    string word = words[idx];
    bool res = false;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] == '-' || board[i][j] == word[0])
            {
                if (canPlaceWordH(i, j, word))
                {
                    vector<bool> mark = placeWordH(i, j, word);
                    res = res || crossWord_(idx + 1);
                    unPlaceWordH(i, j, word, mark);
                }

                if (canPlaceWordV(i, j, word))
                {
                    vector<bool> mark = placeWordV(i, j, word);
                    res = res || crossWord_(idx + 1);
                    unPlaceWordV(i, j, word, mark);
                }
            }
        }
    }

    return res;
}

void crossWord()
{
    cout << crossWord_(0) << endl;
}

int main()
{
    crossWord();
    return 0;
}