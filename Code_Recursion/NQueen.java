public class NQueen{

    public static void main(String[] args){

        // set1();
        set2();

    }

    public static int combinationQueen1D(boolean[] boxes, int qpsf, int tnq, int idx, String ans)
    // qpsf = queen placed so far
    {
        if(qpsf == tnq){
            System.out.println(ans);
            return 1;
        }

        int count = 0;

        for(int i = idx;i<boxes.length;i++){
            count += combinationQueen1D(boxes, qpsf+1, tnq, i+1, ans + i + " ");
        }

        return count;
    }

    public static int permutationQueen1D(boolean[] boxes, int qpsf, int tnq, String ans)
    // qpsf = queen placed so far
    {
        if(qpsf == tnq){
            System.out.println(ans);
            return 1;
        }

        int count = 0;
    
        for(int i = 0;i<boxes.length;i++){
            if(!boxes[i]){
                boxes[i]=true;
                count += permutationQueen1D(boxes, qpsf+1, tnq, ans + i + " ");
                boxes[i]=false;
            }
        }

        return count;
    }

    public static int permutationQueen1D_sub(boolean[] boxes, int qpsf, int tnq,int i, String ans)
    // qpsf = queen placed so far
    {
        if(i == boxes.length)
            return 0;
        if(qpsf == tnq){
            System.out.println(ans);
            return 1;
        }

        int count = 0;
    
        if(!boxes[i]){
            boxes[i]=true;
            count += permutationQueen1D_sub(boxes, qpsf+1, tnq, 0, ans + i + " ");
            boxes[i]=false;
        }
        count += permutationQueen1D_sub(boxes, qpsf, tnq, i+1, ans);

        return count;
    }

    public static int combinationQueen1D_sub(boolean[] boxes, int qpsf, int tnq,int i, String ans)
    // qpsf = queen placed so far
    {
        if(qpsf == tnq){
            System.out.println(ans);
            return 1;
        }

        int count = 0;

        if(i != boxes.length)
        {
            count += combinationQueen1D_sub(boxes, qpsf+1, tnq, i+1, ans + i + " ");
            count += combinationQueen1D_sub(boxes, qpsf, tnq, i+1, ans);
        }
        return count;
    }

    public static int combinationQueen2D(boolean[][] boxes, int qpsf, int tnq, int idx, String ans){

        if(qpsf == tnq){
            System.out.println(ans);
            return 1;
        }
        
        int count = 0;

        for(int i = idx;i<boxes.length * boxes[0].length;i++){
            int r = i / boxes.length;
            int c = i % boxes[0].length;
            count += combinationQueen2D(boxes, qpsf+1, tnq, i+1, ans + "(" + r + "," + c + ") ");
        }

        return count;
    }

    public static int permutationQueen2D(boolean[][] boxes, int qpsf, int tnq, String ans)
    // qpsf = queen placed so far
    {
        if(qpsf == tnq){
            System.out.println(ans);
            return 1;
        }

        int count = 0;
    
        for(int i = 0;i<boxes.length * boxes[0].length;i++){
            int r = i / boxes.length;
            int c = i % boxes[0].length;
            if(!boxes[r][c]){
                boxes[r][c]=true;
                count += permutationQueen2D(boxes, qpsf+1, tnq,ans + "(" + r + "," + c + ") ");
                boxes[r][c]=false;
            }
        }

        return count;
    }

    public static void set1(){
        int n=3;
        // boolean[] boxes = new boolean[n];
        boolean[][] boxes = new boolean[n][n];

        // System.out.println(combinationQueen1D(boxes,0,3,0,""));
        // System.out.println(permutationQueen1D(boxes,0,3,""));
        // System.out.println(permutationQueen1D_sub(boxes,0,3,0,""));
        // System.out.println(combinationQueen1D_sub(boxes,0,3,0,""));
        System.out.println(permutationQueen2D(boxes,0,3,""));
    }

    //NQueen==========================================================================

    public static boolean isSafeToPlaceQueen(boolean[][] boxes, int row, int col){
        int[][] dir = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
        
        for(int i=0;i<dir.length;i++)
        {
            for(int jump=1;jump <= boxes.length;jump++)
            {
                int r = row + jump*dir[i][0];
                int c = col + jump*dir[i][1];

                if(r >= 0 && c >= 0 && r < boxes.length && c < boxes.length)
                {
                    if(boxes[r][c]==true)
                        return false;
                }
                else break;
            }
        }

        return true;
    }

    public static int Nqueen_01(boolean[][] boxes, int tnq, int idx, String ans){
        if(tnq==0)
        {
            System.out.println(ans);
            return 1;
        }

        int count = 0;

        for(int i=idx;i<boxes.length * boxes[0].length;i++){
            int r = i / boxes.length;
            int c = i % boxes[0].length;

            if(isSafeToPlaceQueen(boxes, r, c))
            {
                boxes[r][c] = true;
                count += Nqueen_01(boxes, tnq-1, i+1, ans + "(" + r + "," + c + ") ");
                boxes[r][c] = false;
            }
        }

        return count;
    }

    static boolean[] rowA;
    static boolean[] colA;
    static boolean[] diag;  // n+m-1 = 7
    static boolean[] adiag; // n+m-1 = 7

    public static int Nqueen_02(int n,int m, int tnq, int idx, String ans){         //n = no. of rows, m = no. of columns
        if(tnq==0)
        {
            System.out.println(ans);
            return 1;
        }

        int count = 0;

        for(int i=idx;i<n*m;i++){
            int r = i / n;
            int c = i % m;

            if(!rowA[r] && !colA[c] && !diag[r-c+m-1] && !adiag[r+c])
            {
                rowA[r] = true;
                colA[c] = true;
                diag[r - c + m - 1] = true;
                adiag[r + c] = true;

                count += Nqueen_02(n,m, tnq-1, i+1, ans + "(" + r + "," + c + ") ");
                
                rowA[r] = false;
                colA[c] = false;
                diag[r - c + m - 1] = false;
                adiag[r + c] = false;
            }
        }

        return count;
    }

    static int rowA_ = 0;
    static int colA_ = 0;
    static int diag_ = 0;
    static int adiag_ = 0;

    public static int Nqueen_03(int n,int m, int tnq, int idx, String ans){         //n = no. of rows, m = no. of columns
        if(tnq==0)
        {
            System.out.println(ans);
            return 1;
        }

        int count = 0;

        for(int i=idx;i<n*m;i++){
            int r = i / n;
            int c = i % m;

            if( (rowA_ & (1<<r))==0 && (colA_ & (1<<c))==0 && (diag_ & (1<<(r-c+m-1)))==0 && (adiag_ & (1<<(r+c)))==0 )
            {
                rowA_ ^= (1 << r);
                colA_ ^= (1 << c);
                diag_ ^= (1 << (r - c + m - 1));
                adiag_ ^= (1 << (r + c));

                count += Nqueen_03(n,m, tnq-1, i+1, ans + "(" + r + "," + c + ") ");
                
                rowA_ ^= (1 << r);
                colA_ ^= (1 << c);
                diag_ ^= (1 << (r - c + m - 1));
                adiag_ ^= (1 << (r + c));
            }
        }

        return count;
    }

    public static int Nqueen_03_sub(int n,int m, int tnq, int i, String ans){         //n = no. of rows, m = no. of columns, i=index
        if (i == n * m || tnq == 0)
        {
            if (tnq == 0)
            {
                System.out.println(ans);
                return 1;
            }
            return 0;
        }

        int count = 0;
        int r = i / n;
        int c = i % m;

        if( (rowA_ & (1<<r))==0 && (colA_ & (1<<c))==0 && (diag_ & (1<<(r-c+m-1)))==0 && (adiag_ & (1<<(r+c)))==0 )
        {
            rowA_ ^= (1 << r);
            colA_ ^= (1 << c);
            diag_ ^= (1 << (r - c + m - 1));
            adiag_ ^= (1 << (r + c));

            count += Nqueen_03_sub(n,m, tnq-1, i+1, ans + "(" + r + "," + c + ") ");
                
            rowA_ ^= (1 << r);
            colA_ ^= (1 << c);
            diag_ ^= (1 << (r - c + m - 1));
            adiag_ ^= (1 << (r + c));
        }
        count += Nqueen_03_sub(n,m, tnq, i+1, ans);

        return count;
    }

    public static int Nqueen_04(int n,int m, int tnq, int r, String ans){         //n = houses, m = rooms, r = row
        if (r == n || tnq == 0)
        {
            if (tnq == 0)
            {
                System.out.println(ans);
                return 1;
            }
            return 0;
        }

        int count = 0;

        for(int i = 0; i < m; i++){
            int x = r;
            int y = i;

            if((rowA_ & (1 << x))==0 && (colA_ & (1 << y))==0 && (diag_ & (1 << (x - y + m - 1)))==0 && (adiag_ & (1 << (x + y)))==0)
            {
                rowA_ ^= (1 << x);
                colA_ ^= (1 << y);
                diag_ ^= (1 << (x - y + m - 1));
                adiag_ ^= (1 << (x + y));

                count += Nqueen_04(n,m, tnq-1, r+1, ans + "(" + x + "," + y + ") ");
                
                rowA_ ^= (1 << x);
                colA_ ^= (1 << y);
                diag_ ^= (1 << (x - y + m - 1));
                adiag_ ^= (1 << (x + y));
            }
        }

        return count;
    }

    public static int Nqueen_04_sub(int n,int m, int tnq, int r, String ans){         //n = houses, m = rooms, r = row
        if (r == n || tnq == 0)
        {
            if (tnq == 0)
            {
                System.out.println(ans);
                return 1;
            }
            return 0;
        }

        int count = 0;

        for(int i = 0; i < m; i++){
            int x = r;
            int y = i;

            if((rowA_ & (1 << x))==0 && (colA_ & (1 << y))==0 && (diag_ & (1 << (x - y + m - 1)))==0 && (adiag_ & (1 << (x + y)))==0)
            {
                rowA_ ^= (1 << x);
                colA_ ^= (1 << y);
                diag_ ^= (1 << (x - y + m - 1));
                adiag_ ^= (1 << (x + y));

                count += Nqueen_04_sub(n,m, tnq-1, r+1, ans + "(" + x + "," + y + ") ");
                
                rowA_ ^= (1 << x);
                colA_ ^= (1 << y);
                diag_ ^= (1 << (x - y + m - 1));
                adiag_ ^= (1 << (x + y));
            }
        }
        count += Nqueen_04_sub(n, m, tnq, r + 1, ans);
        return count;
    }

    public static void set2(){
        int n = 4;
        int m = 4;
        // boolean[][] boxes = new boolean[n][n];
        // System.out.println(Nqueen_01(boxes,4,0,""));

        rowA = new boolean[n];
        colA = new boolean[m];
        diag = new boolean[n+m-1];  // n+m-1 = 7
        adiag = new boolean[n+m-1];
        System.out.println(Nqueen_02(4,4,4,0,""));
    }
}