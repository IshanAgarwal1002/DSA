#include<iostream>
#include<vector>
using namespace std;

void display(vector<vector<int>> &board)
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
            cout<<board[i][j]<<" ";
        cout<<"\n";
    }
}

bool isValidToPlaceNumber(vector<vector<int>> &board, int r,int c,int num)
{
    //for rows and columns
    for(int i=0;i<board.size();i++)
    {
        if(board[r][i]==num || board[i][c]==num)
            return false;
    }

    //for 3X3 matrix
    int x = (r/3) * 3;
    int y = (c/3) * 3;

    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[x+i][y+j]==num)
                return false;
        
    return true;
}

//prints all possible ans
// int sudoku_1(vector<vector<int>> &board,int idx)
// {
//     if(idx == 81)
//     {
//         display(board);
//         return 1;
//     }

//     int count=0;
//     int r = idx / 9;
//     int c = idx % 9;

//     if(board[r][c]==0)
//     {
//         for(int num=1;num<=9;num++)
//         {
//             if(isValidToPlaceNumber(board,r,c,num))
//             {
//                 board[r][c] = num;
//                 count += sudoku_1(board,idx+1);
//                 board[r][c] = 0;
//             }
//         }
//     } 
//     else
//     {
//         count += sudoku_1(board,idx+1);    
//     }
    
//     return count;
// }

//prints one ans
bool sudoku_1(vector<vector<int>> &board,int idx)
{
    if(idx == 81)
    {
        display(board);
        return true;
    }

    bool res = false;
    int r = idx / 9;
    int c = idx % 9;

    if(board[r][c]==0)
    {
        for(int num=1;num<=9;num++)
        {
            if(isValidToPlaceNumber(board,r,c,num))
            {
                board[r][c] = num;
                res = res || sudoku_1(board,idx+1);
                if(res)     return true;
                board[r][c] = 0;
            }
        }
    } 
    else
    {
        res = res || sudoku_1(board,idx+1);  
    }
    
    return res;
}

bool sudoku_2(vector<vector<int>> &board,vector<int> &calls,int idx)
{
    if(idx == calls.size())
    {
        display(board);
        return true;
    }

    bool res = false;
    int r = calls[idx] / 9;
    int c = calls[idx] % 9;

    for(int num=1;num<=9;num++)
    {
        if(isValidToPlaceNumber(board,r,c,num))
        {
            board[r][c] = num;
            res = res || sudoku_2(board,calls,idx+1);
            if(res)     return true;
            board[r][c] = 0;
        }
    }

    return res;
}

int rowMap[9] = {0,0,0,0,0,0,0,0,0};
int colMap[9] = {0,0,0,0,0,0,0,0,0};
int matrixMap[3][3] = {0,0,0,0,0,0,0,0,0};

bool sudoku_3(vector<vector<int>> &board,vector<int> &calls,int idx)
{
    if(idx == calls.size())
    {
        display(board);
        return true;
    }

    bool res = false;
    int r = calls[idx] / 9;
    int c = calls[idx] % 9;

    for(int num=1;num<=9;num++)
    {
        int mask = (1<<num);
        if(!(rowMap[r] & mask) && !(colMap[c] & mask) && !(matrixMap[r/3][c/3] & mask))
        {
            board[r][c] = num;
            rowMap[r] ^= mask;
            colMap[c] ^= mask;
            matrixMap[r/3][c/3] ^= mask;

            res = res || sudoku_3(board,calls,idx+1);
            if(res)     return true;

            board[r][c] = 0;
            rowMap[r] ^= mask;
            colMap[c] ^= mask;
            matrixMap[r/3][c/3] ^= mask;
        }
    }

    return res;
}

int main()
{
    vector<vector<int>> board = {{5,3,0,0,7,0,0,0,0},
                         {6,0,0,1,9,5,0,0,0},
                         {0,9,8,0,0,0,0,6,0},
                         {8,0,0,0,6,0,0,0,3},
                         {4,0,0,8,0,3,0,0,1},
                         {7,0,0,0,2,0,0,0,6},
                         {0,6,0,0,0,0,2,8,0},
                         {0,0,0,4,1,9,0,0,5},
                         {0,0,0,0,8,0,0,7,9}};

// vector<vector<int>> board = {{2,0,0,0,0,0,0,9,0},
//                          {5,0,0,0,8,0,0,3,6},
//                          {0,9,0,0,1,0,0,0,0},
//                          {1,3,0,2,0,0,0,6,0},
//                          {0,7,0,0,0,0,0,0,0},
//                          {4,6,9,3,0,0,0,0,2},
//                          {0,0,6,0,9,0,0,2,0},
//                          {0,4,2,0,0,0,0,8,0},
//                          {0,8,1,0,2,4,6,0,0}};

    vector<int> calls;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(board[i][j]==0)
                calls.push_back(i*9 + j);
            else
            {
                int mask = (1<<board[i][j]);
                rowMap[i] ^= mask;
                colMap[j] ^= mask;
                matrixMap[i/3][j/3] ^= mask;
            }
            
        }
    }
    cout<<sudoku_3(board,calls,0);
    return 0;
}