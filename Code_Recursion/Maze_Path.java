import java.util.ArrayList;
import java.util.Scanner;

public class Maze_Path
{
    public static Scanner input = new Scanner(System.in);

    public static void main(String[] args)
    {
        int sr=0, sc=0, er=2, ec=2;
        // ArrayList <String> ans = mazePath_multi_HVD_1(sr,sc,er,ec);
        // for(String s:ans)
        //     System.out.println(s);
        // System.out.print(mazePath_multi_HVD_2(sr,sc,er,ec,""));

        int[][] board = new int[3][3];
        // System.out.print(mazePath_multi_8D_1(sr, sc, er, ec,Math.max(er,ec), board, ""));
        // ArrayList <String> ans = mazePath_multi_8D_2(sr, sc, er, ec, Math.max(er,ec), board);
        // for(String s:ans)
        //     System.out.println(s); 
        System.out.print(mazePath_Height(sr, sc, er, ec, board));
    }

    public static ArrayList <String> mazePath_HV_1(int sr,int sc,int er,int ec)
    {
        if(sr==er && sc==ec)
        {
            ArrayList <String> base = new ArrayList<>();
            base.add("");
            return base;
        }

        ArrayList <String> ans = new ArrayList<>();

        if(sr+1 <= er)
        {
            ArrayList <String> Ver = mazePath_HV_1(sr+1, sc, er, ec);
            for(String s:Ver)
                ans.add("V" + s);
        }

        if(sc+1 <= ec)
        {
            ArrayList <String> Hor = mazePath_HV_1(sr, sc+1, er, ec);
            for(String s:Hor)
                ans.add("H" + s);
        }

        return ans;
    }

    public static int mazePath_HV_2(int sr,int sc,int er,int ec, String ans)
    {
        if(sr==er && sc==ec)
        {
            System.out.println(ans);
            return 1;
        }

        int count=0;

        if(sr+1 <= er)
            count += mazePath_HV_2(sr+1, sc, er, ec,ans+"V");

        if(sc+1 <= ec)
            count += mazePath_HV_2(sr, sc+1, er, ec,ans+"H");

        return count;
    }

    public static ArrayList <String> mazePath_HVD_1(int sr,int sc,int er,int ec)
    {
        if(sr==er && sc==ec)
        {
            ArrayList <String> base = new ArrayList<>();
            base.add("");
            return base;
        }

        ArrayList <String> ans = new ArrayList<>();

        if(sr+1 <= er)
        {
            ArrayList <String> Ver = mazePath_HVD_1(sr+1, sc, er, ec);
            for(String s:Ver)
                ans.add("V" + s);
        }

        if(sr+1 <= er && sc+1 <= ec)
        {
            ArrayList <String> Dia = mazePath_HVD_1(sr+1, sc+1, er, ec);
            for(String s:Dia)
                ans.add("D" + s);
        }

        if(sc+1 <= ec)
        {
            ArrayList <String> Hor = mazePath_HVD_1(sr, sc+1, er, ec);
            for(String s:Hor)
                ans.add("H" + s);
        }

        return ans;
    }

    public static int mazePath_HVD_2(int sr,int sc,int er,int ec, String ans)
    {
        if(sr==er && sc==ec)
        {
            System.out.println(ans);
            return 1;
        }

        int count=0;

        if(sr+1 <= er)
            count += mazePath_HVD_2(sr+1, sc, er, ec,ans+"V");

        if(sc+1 <= ec && sr+1 <= er)
            count += mazePath_HVD_2(sr+1, sc+1, er, ec,ans+"D");
        
        if(sc+1 <= ec)
            count += mazePath_HVD_2(sr, sc+1, er, ec,ans+"H");

        return count;
    }

    public static ArrayList <String> mazePath_multi_HVD_1(int sr,int sc,int er,int ec)
    {
        if(sr==er && sc==ec)
        {
            ArrayList <String> base = new ArrayList<>();
            base.add("");
            return base;
        }

        ArrayList <String> ans = new ArrayList<>();

        for(int jump=1;sr+jump <= er;jump++)
        {
            ArrayList <String> Ver = mazePath_multi_HVD_1(sr+jump, sc, er, ec);
            for(String s:Ver)
                ans.add("V"+ jump + s);
        }

        for(int jump=1;sr+jump <= er && sc+jump <= ec;jump++)
        {
            ArrayList <String> Dia = mazePath_multi_HVD_1(sr+jump, sc+jump, er, ec);
            for(String s:Dia)
                ans.add("D"+ jump + s);
        }

        for(int jump=1;sc+jump <= ec;jump++)
        {
            ArrayList <String> Hor = mazePath_multi_HVD_1(sr, sc+jump, er, ec);
            for(String s:Hor)
                ans.add("H"+ jump + s);
        }

        return ans;
    }

    public static int mazePath_multi_HVD_2(int sr,int sc,int er,int ec, String ans)
    {
        if(sr == er && sc == ec)
        {
            System.out.println(ans);
            return 1;
        }

        int count=0;

        for(int jump=1;sr + jump <= er;jump++)
            count += mazePath_multi_HVD_2(sr + jump, sc, er, ec,ans+"V"+jump);

        for(int jump=1;sr + jump <= er && sc + jump <= ec;jump++)
            count += mazePath_multi_HVD_2(sr + jump, sc+jump, er, ec,ans+"D"+jump);
        
        for(int jump=1;sc + jump <= ec;jump++)
            count += mazePath_multi_HVD_2(sr, sc + jump, er, ec,ans+"H"+jump);

        return count;
    }

    static int[][] dir4 = {{0,1}, {-1,0}, {0,-1}, {1,0}};
    static String[] dirN4 = {"R", "U", "L", "D"};

    public static boolean isValid(int r,int c, int[][] board)
    {
        if(r<0 || c<0 || r>=board.length || c>=board[0].length || board[r][c]==1)
            return false;
        
        return true;
    }

    public static int mazePath_4D_1(int sr,int sc,int er,int ec,int[][] board, String ans)
    {
        if(sr==er && sc==ec)
        {
            System.out.println(ans);
            return 1;
        }

        int count=0;
        board[sr][sc] = 1;

        for(int d=0;d<dir4.length;d++)
        {
            int r = sr + dir4[d][0];
            int c = sc + dir4[d][1];
            if(isValid(r,c,board))
            {
                count += mazePath_4D_1(r, c, er, ec, board, ans+dirN4[d]);
            }
        }

        board[sr][sc] = 0; 
        return count;
    }

    public static ArrayList <String> mazePath_4D_2(int sr,int sc,int er,int ec,int[][] board)
    {
        if(sr==er && sc==ec)
        {
            ArrayList<String> base = new ArrayList<>();
            base.add("");
            return base;
        }

        ArrayList <String> ans = new ArrayList<>();
        board[sr][sc] = 1;

        for(int d=0;d<dir4.length;d++)
        {
            int r = sr + dir4[d][0];
            int c = sc + dir4[d][1];
            if(isValid(r,c,board))
            {
                ArrayList <String> recAns = mazePath_4D_2(r, c, er, ec, board);
                for(String s:recAns)
                    ans.add(dirN4[d] + s);
            }
        }

        board[sr][sc] = 0; 
        return ans;
    }

    static int[][] dir8 = {{0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}};      //coordinates (y,x)
    static String[] dirN8 = {"R", "E", "U", "N", "L", "W", "D", "S"};

    public static int mazePath_8D_1(int sr,int sc,int er,int ec,int[][] board,String ans)
    {
        if(sr==er && sc==ec)
        {
            System.out.println(ans);
            return 1;
        }

        int count = 0;
        board[sr][sc]=1;

        for(int d=0;d<dir8.length;d++)
        {
            int r = sr + dir8[d][0];
            int c = sc + dir8[d][1];
            if(isValid(r, c, board))
            {
                count += mazePath_8D_1(r, c, er, ec, board, ans+dirN8[d]);
            }
        }

        board[sr][sc]=0;
        return count;
    }

    public static ArrayList <String> mazePath_8D_2(int sr,int sc,int er,int ec,int[][] board)
    {
        if(sr==er && sc==ec)
        {
            ArrayList<String> base = new ArrayList<>();
            base.add("");
            return base;
        }

        ArrayList <String> ans = new ArrayList<>();
        board[sr][sc] = 1;

        for(int d=0;d<dir8.length;d++)
        {
            int r = sr + dir8[d][0];
            int c = sc + dir8[d][1];
            if(isValid(r,c,board))
            {
                ArrayList <String> recAns = mazePath_8D_2(r, c, er, ec, board);
                for(String s:recAns)
                    ans.add(dirN8[d] + s);
            }
        }

        board[sr][sc] = 0; 
        return ans;
    }

    public static int mazePath_multi_8D_1(int sr,int sc,int er,int ec,int rad,int[][] board,String ans)
    {
        if(sr==er && sc==ec)
        {
            System.out.println(ans);
            return 1;
        }

        int count = 0;
        board[sr][sc]=1;

        for(int d=0;d<dir8.length;d++)
        {
            for(int jump=0;jump<=rad;jump++)
            {
                int r = sr + jump*dir8[d][0];
                int c = sc + jump*dir8[d][1];
                if(isValid(r, c, board))
                {
                    count += mazePath_multi_8D_1(r, c, er, ec, rad, board, ans+dirN8[d]+jump);
                }
            }
        }

        board[sr][sc]=0;
        return count;
    }

    public static ArrayList <String> mazePath_multi_8D_2(int sr,int sc,int er,int ec,int rad,int[][] board)
    {
        if(sr==er && sc==ec)
        {
            ArrayList<String> base = new ArrayList<>();
            base.add("");
            return base;
        }

        ArrayList <String> ans = new ArrayList<>();
        board[sr][sc] = 1;

        for(int d=0;d<dir8.length;d++)
        {
            for(int jump=0;jump<=rad;jump++)
            {
                int r = sr + jump*dir8[d][0];
                int c = sc + jump*dir8[d][1];
                if(isValid(r,c,board))
                {
                    ArrayList <String> recAns = mazePath_multi_8D_2(r, c, er, ec, rad, board);
                    for(String s:recAns)
                        ans.add(dirN8[d] + jump + s);
                }
            }
        }

        board[sr][sc] = 0; 
        return ans;
    }

    public static int mazePath_Height(int sr,int sc,int er,int ec,int[][] board){
        if(sr==er && sc==ec){
            return 0;
        }

        board[sr][sc]=2;
        int maxH=0;
        for(int d=0;d<dir8.length;d++){
            int r=sr+dir8[d][0];
            int c=sc+dir8[d][1];
            if(r>=0 && c>=0 && r<board.length && c<board[0].length && board[r][c]==0){
                int recH=mazePath_Height(r,c,er,ec,board);
                maxH=Math.max(recH,maxH);
            }
        }
        
        board[sr][sc]=0;
        return maxH+1;
    }

    static class pair{
        int len=0;
        String str="";

        pair(int len,String str){
            this.len=len;
            this.str=str;
        }
    }

    public static pair floodfill_LongestPath(int sr,int sc,int er,int ec,int[][] board){
        if(sr==er && sc==ec){
            return new pair(0,"");
        }

        board[sr][sc]=2;
        
        pair mypair=new pair(0,"");

        for(int d=0;d<dir8.length;d++){
            int r=sr + dir8[d][0];
            int c=sc + dir8[d][1];
            if(r>=0 && c>=0 && r<board.length && c<board[0].length && board[r][c]==0){
                pair recP=floodfill_LongestPath(r,c,er,ec,board);
                 
                if(recP.len+1> mypair.len){
                    mypair.len = recP.len + 1;
                    mypair.str = dirN8[d] + recP.str;
                }
            }
        }
        
        board[sr][sc]=0;
        return mypair;
    }

    public static pair floodfill_ShortestPath(int sr,int sc,int er,int ec,int[][] board){
        if(sr==er && sc==ec){
            return new pair(0,"");  //c++ -> INT_MAX;
        }

        board[sr][sc]=2;
        
        pair mypair=new pair((int)1e7,"");

        for(int d=0;d<dir8.length;d++){
            int r=sr + dir8[d][0];
            int c=sc + dir8[d][1];
            if(r>=0 && c>=0 && r<board.length && c<board[0].length && board[r][c]==0){
                pair recP=floodfill_ShortestPath(r,c,er,ec,board);
                 
                if(recP.len+1 < mypair.len){
                    mypair.len=recP.len+1;
                    mypair.str=dirN8[d]+recP.str;
                }
            }
        }
        
        board[sr][sc]=0;
        return mypair;
    }
} 