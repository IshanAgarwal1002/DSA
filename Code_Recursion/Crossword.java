public class Crossword{

    public static void main(String[] args)
    {
        crossword();
    }

    static char[][] board ={{'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
                           {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
                           {'+', '-', '-', '-', '-', '-', '-', '-', '+', '+'},
                           {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
                           {'+', '-', '+', '+', '+', '+', '+', '+', '+', '+'},
                           {'+', '-', '-', '-', '-', '-', '-', '+', '+', '+'},
                           {'+', '-', '+', '+', '+', '-', '+', '+', '+', '+'},
                           {'+', '+', '+', '+', '+', '-', '+', '+', '+', '+'},
                           {'+', '+', '+', '+', '+', '-', '+', '+', '+', '+'},
                           {'+', '+', '+', '+', '+', '+', '+', '+', '+', '+'}};

    static String[] words = {"AGRA", "NORWAY", "ENGLAND", "GWALIOR"};

    public static void crossword()
    {
        System.out.println(crossword_(0));
    }

    public static boolean crossword_(int idx){

        if(idx == words.length)
        {
            for (char[] ar : board)
            {
                for (char ch : ar)
                    System.out.print(ch + " ");
                System.out.println();
            }
            return true;
        }

        String word = words[idx];
        boolean res = false;
        for(int i=0;i<board.length;i++)
        {
            for(int j=0;j<board[0].length;j++)
            {
                if(board[i][j]=='-' || board[i][j]== word.charAt(0)){

                    if(canPlaceWordH(i,j,word)){
                        boolean[] mark = placeWordH(i,j,word);
                        res = res || crossword_(idx+1);         //go place next word
                        unplaceWordH(i,j,word,mark);
                    }

                    if(canPlaceWordV(i,j,word)){
                        boolean[] mark = placeWordV(i,j,word);
                        res = res || crossword_(idx+1);         //go place next word
                        unplaceWordV(i,j,word,mark);
                    }
                }
            }
        }

        return res;
    }

    public static boolean canPlaceWordH(int r,int c,String word){

        if((c == 0) && ((c + word.length()) < board[0].length)){
            if(board[r][c+word.length()] != '+')
                return false;
        }
        else if((c+word.length() == board[0].length) && (word.length() != board[0].length)){
            if(board[r][c-1] != '+')
                return false;
        }
        else{
            if( ((c - 1 >= 0) && (board[r][c-1] != '+')) || (((c + word.length()) < board[0].length) && board[r][c + word.length()] != '+') )
                return false;
        }

        for(int i=0;i<word.length();i++){
            if(((c + i) < board[0].length) && (board[r][c+i] != '-') && (board[r][c+i] != word.charAt(i)))
                return false;
        }

        return true;
    }

    public static boolean[] placeWordH(int r,int c,String word){

        boolean[] mark = new boolean[word.length()];
        for(int i=0;i<word.length();i++)
        {
            if(board[r][c+i]=='-')
            {
                mark[i] = true;
                board[r][c+i] = word.charAt(i);
            }
        }
        return mark;
    }

    public static void unplaceWordH(int r,int c,String word,boolean[] mark){

        for(int i=0;i<word.length();i++)
        {
            if(mark[i]){
                board[r][c+i] = '-';
            }
        }
    }

    public static boolean canPlaceWordV(int r,int c,String word){

        if((r == 0) && ((r + word.length()) < board.length)){
            if(board[r+word.length()][c] != '+')
                return false;
        }
        else if((r+word.length() == board.length) && (word.length() != board.length)){
            if(board[r-1][c] != '+')
                return false;
        }
        else{
            if( ((r - 1 >= 0) && (board[r-1][c] != '+')) || (((r + word.length()) < board.length) && board[r + word.length()][c] != '+') )
                return false;
        }

        for(int i=0;i<word.length();i++){
            if(((r + i) < board.length) && (board[r+i][c] != '-') && (board[r+i][c] != word.charAt(i)))
                return false;
        }

        return true;
    }

    public static boolean[] placeWordV(int r,int c,String word){

        boolean[] mark = new boolean[word.length()];
        for(int i=0;i<word.length();i++)
        {
            if(board[r+i][c]=='-')
            {
                mark[i] = true;
                board[r+i][c] = word.charAt(i);
            }
        }
        return mark;
    }

    public static void unplaceWordV(int r,int c,String word,boolean[] mark){

        for(int i=0;i<word.length();i++)
        {
            if(mark[i]){
                board[r+i][c] = '-';
            }
        }
    }
}