import java.util.ArrayList;

public class Sudoku {
    public static void main(final String[] args) {
       
        int[][] board = {{5,3,0,0,7,0,0,0,0},
                         {6,0,0,1,9,5,0,0,0},
                         {0,9,8,0,0,0,0,6,0},
                         {8,0,0,0,6,0,0,0,3},
                         {4,0,0,8,0,3,0,0,1},
                         {7,0,0,0,2,0,0,0,6},
                         {0,6,0,0,0,0,2,8,0},
                         {0,0,0,4,1,9,0,0,5},
                         {0,0,0,0,8,0,0,7,9}};
        // System.out.print(sudoku_01(board, 0));
        ArrayList <Integer> calls = new ArrayList<>();
        rowMap = new int[9];
        colMap = new int[9];
        matrixMap = new int[3][3];
        for(int i=0;i<board.length;i++)
        {
            for(int j=0;j<board.length;j++)
            {
                if(board[i][j]==0)
                    calls.add(i*9+j);
                else
                {
                    int mask = (1<<board[i][j]);
                    rowMap[i] ^= mask;
                    colMap[j] ^= mask;
                    matrixMap[i/3][j/3] ^= mask;
                }
            }
        }
    
        // System.out.print(sudoku_2(board,calls, 0));
        System.out.print(sudoku_3(board,calls, 0));
    }

    public static boolean isValidToPlaceNumber(int[][] board,int r,int c,int num)
    {
        //for row and column
        for(int i=0;i<board.length;i++)
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

    //print all possible answers
    // public static int sudoku_01(int[][] board,int idx)   
    // {
    //     if(idx==81)
    //     {
    //         display(board);
    //         return 1;
    //     }

    //     int r = idx/9;
    //     int c = idx%9;
    //     int count=0;

    //     if(board[r][c] == 0)
    //     {
    //         for(int num=1;num<=9;num++)
    //         {
    //             if(isValidToPlaceNumber(board, r, c, num))
    //             {
    //                 board[r][c]=num;
    //                 count += sudoku_01(board, idx+1);
    //                 board[r][c]=0;
    //             }
    //         }
    //     }
    //     else{
    //         count += sudoku_01(board, idx+1);
    //     }

    //     return count;
    // }

    //prints single ans
    public static boolean sudoku_1(int[][] board,int idx)
    {
        if(idx==81)
        {
            display(board);
            return true;
        }

        int r = idx/9;
        int c = idx%9;
        
        boolean res = false;

        if(board[r][c] == 0)
        {
            for(int num=1;num<=9;num++)
            {
                if(isValidToPlaceNumber(board, r, c, num))
                {
                    board[r][c]=num;
                    res = res || sudoku_1(board, idx+1);
                    if(res) return true;
                    board[r][c]=0;
                }
            }
        }
        else{
            res = res || sudoku_1(board, idx+1);
        }

        return res;
    }

    public static boolean sudoku_2(int[][] board,ArrayList<Integer> calls,int idx)
    {
        if(idx == calls.size())
        {
            display(board);
            return true;
        }

        int r = calls.get(idx)/9;
        int c = calls.get(idx)%9;
        
        boolean res = false;

        for(int num=1;num<=9;num++)
        {
            if(isValidToPlaceNumber(board, r, c, num))
            {
                board[r][c]=num;
                res = res || sudoku_2(board,calls,idx+1);
                if(res) return true;
                board[r][c]=0;
            }
        }

        return res;
    }

    static int[] rowMap;
    static int[] colMap;
    static int[][] matrixMap;

    public static boolean sudoku_3(int[][] board,ArrayList<Integer> calls,int idx)
    {
        if(idx == calls.size())
        {
            display(board);
            return true;
        }

        int r = calls.get(idx)/9;
        int c = calls.get(idx)%9;
        
        boolean res = false;

        for(int num=1;num<=9;num++)
        {
            int mask = (1<<num);
            if((rowMap[r] & mask) == 0 && (colMap[c] & mask) == 0 && (matrixMap[r/3][c/3] & mask) == 0 )
            {
                board[r][c]=num;
                rowMap[r] ^= mask;
                colMap[c] ^= mask;
                matrixMap[r/3][c/3] ^= mask;

                res = res || sudoku_3(board,calls,idx+1);
                if(res) return true;
                
                board[r][c]=0;
                rowMap[r] ^= mask;
                colMap[c] ^= mask;
                matrixMap[r/3][c/3] ^= mask;
            }
        }

        return res;
    }

    public static void display(int[][] board)
    {
        for(int[] i:board)
        {
            for(int j:i)
                System.out.print(j + " ");
            System.out.println();
        }
    }
}