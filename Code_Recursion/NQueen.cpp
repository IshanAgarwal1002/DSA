#include<iostream>
#include<vector>
using namespace std;

int combinationQueen1D(vector<bool> &boxes, int qpsf, int total_q, int idx, string ans)
// qpsf = queen placed so far
{
    if(qpsf == total_q)
    {
        cout<<ans<<"\n";
        return 1;
    }

    int count = 0;
    
    for(int i=idx;i<boxes.size();i++)
    {
        count += combinationQueen1D(boxes, qpsf+1, total_q, i+1, ans+ "B"+ to_string(i) + " Q" + to_string(qpsf) + " ");
    }

    return count;
}

int permutationQueen1D(vector<bool> &boxes, int qpsf, int tnq, string ans)
{ //qpsf : queen place so far, tnq: total no of queen
    if (qpsf == tnq)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int i = 0; i < boxes.size(); i++)
    {
        if (!boxes[i])
        {
            boxes[i] = true;
            count += permutationQueen1D(boxes, qpsf + 1, tnq, ans + "B" + to_string(i) + "Q" + to_string(qpsf) + " ");
            boxes[i] = false;
        }
    }
    return count;
}

int permutationQueen1D_sub(vector<bool> &boxes, int idx, int qpsf, int tnq, string ans)
{ //qpsf : queen place so far, tnq: total no of queen
    if (qpsf == tnq || idx == boxes.size())
    {
        if(idx == boxes.size())
            return 0;
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    if (!boxes[idx])
    {
        boxes[idx] = true;
        count += permutationQueen1D_sub(boxes, 0, qpsf + 1, tnq, ans + "B" + to_string(idx) + "Q" + to_string(qpsf) + " ");
        boxes[idx] = false;
    }
    count += permutationQueen1D_sub(boxes, idx + 1, qpsf, tnq, ans);

    return count;
}

int combinationQueen1D_sub(vector<bool> &boxes, int qpsf, int total_q, int idx, string ans)
// qpsf = queen placed so far
{
    if(qpsf == total_q)
    {
        cout<<ans<<"\n";
        return 1;
    }

    int count = 0;

    if(idx != boxes.size())
    {
        count += combinationQueen1D_sub(boxes, qpsf+1, total_q, idx+1, ans+ "B"+ to_string(idx) + " Q" + to_string(qpsf) + " ");
        count += combinationQueen1D_sub(boxes, qpsf, total_q, idx+1, ans);
    }

    return count;
}

int combinationQueen2D(vector<vector<bool>> &boxes, int qpsf, int tnq, int idx, string ans)
{ //qpsf : queen place so far, tnq: total no of queen
    if (qpsf == tnq)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int i = idx; i < boxes.size() * boxes[0].size(); i++)
    {
        int x = i / boxes.size();
        int y = i % boxes[0].size();
        count += combinationQueen2D(boxes, qpsf + 1, tnq, i + 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");
    }
    return count;
}

int permutationQueen2D(vector<vector<bool>> &boxes, int qpsf, int tnq, string ans) // boolean[][]
{ //qpsf : queen place so far, tnq: total no of queen
    if (qpsf == tnq)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int i = 0; i < boxes.size() * boxes[0].size(); i++)
    {
        int x = i / boxes[0].size();
        int y = i % boxes[0].size();
        if (!boxes[x][y])
        {
            boxes[x][y] = true;
            count += permutationQueen2D(boxes, qpsf + 1, tnq, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");
            boxes[x][y] = false;
        }
    }
    return count;
}

//NQueen=========================================================

bool isSafeToPlaceQueen(vector<vector<bool>> &boxes, int row, int col)
{
    vector<vector<int>> Qdir = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

    for (int d = 0; d < Qdir.size(); d++)
    {
        for (int rad = 1; rad <= boxes.size(); rad++)
        {
            int r = row + rad * Qdir[d][0];
            int c = col + rad * Qdir[d][1];

            if (r >= 0 && c >= 0 && r < boxes.size() && c < boxes.size())
            {
                if (boxes[r][c])
                    return false;
            }
            else
                break;
        }
    }

    return true;
}

int Nqueen_01(vector<vector<bool>> &boxes, int tnq, int idx, string ans)
{ //qpsf : queen place so far, tnq: total no of queen
    if (tnq == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int i = idx; i < boxes.size() * boxes[0].size(); i++)
    {
        int x = i / boxes.size();
        int y = i % boxes[0].size();
        if (isSafeToPlaceQueen(boxes, x, y))
        {
            boxes[x][y] = true;
            count += Nqueen_01(boxes, tnq - 1, i + 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");
            boxes[x][y] = false;
        }
    }
    return count;
}

vector<bool> rowA;
vector<bool> colA;
vector<bool> diag;  // n+m-1 = 7
vector<bool> adiag; // n+m-1 = 7

int Nqueen_02(int n, int m, int tnq, int idx, string ans)
{ //n = no. of rows, m = no. of columns
    if (tnq == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int i = idx; i < n * m; i++)
    {
        int x = i / n;
        int y = i % m;
        if (!rowA[x] && !colA[y] && !diag[x - y + m - 1] && !adiag[x + y])
        {
            rowA[x] = true;
            colA[y] = true;
            diag[x - y + m - 1] = true;
            adiag[x + y] = true;

            count += Nqueen_02(n, m, tnq - 1, i + 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");

            rowA[x] = false;
            colA[y] = false;
            diag[x - y + m - 1] = false;
            adiag[x + y] = false;
        }
    }
    return count;
}

int rowA_ = 0;
int colA_ = 0;
int diag_ = 0;
int adiag_ = 0;

int Nqueen_03(int n, int m, int tnq, int idx, string ans)
{
    if (tnq == 0)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int i = idx; i < n * m; i++)
    {
        int x = i / m;
        int y = i % m;

        if (!(rowA_ & (1 << x)) && !(colA_ & (1 << y)) && !(diag_ & (1 << (x - y + m - 1))) && !(adiag_ & (1 << (x + y))))
        {
            rowA_ ^= (1 << x);
            colA_ ^= (1 << y);
            diag_ ^= (1 << (x - y + m - 1));
            adiag_ ^= (1 << (x + y));

            count += Nqueen_03(n, m, tnq - 1, i + 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");

            rowA_ ^= (1 << x);
            colA_ ^= (1 << y);
            diag_ ^= (1 << (x - y + m - 1));
            adiag_ ^= (1 << (x + y));
        }
    }
    return count;
}

int Nqueen_03_sub(int n, int m, int tnq, int idx, string ans)
{ 
    if (idx == n * m || tnq == 0)
    {
        if (tnq == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }

    int count = 0;
    int x = idx / m;
    int y = idx % m;

    if (!(rowA_ & (1 << x)) && !(colA_ & (1 << y)) && !(diag_ & (1 << (x - y + m - 1))) && !(adiag_ & (1 << (x + y))))
    {
        rowA_ ^= (1 << x);
        colA_ ^= (1 << y);
        diag_ ^= (1 << (x - y + m - 1));
        adiag_ ^= (1 << (x + y));

        count += Nqueen_03_sub(n, m, tnq - 1, idx + 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");

        rowA_ ^= (1 << x);
        colA_ ^= (1 << y);
        diag_ ^= (1 << (x - y + m - 1));
        adiag_ ^= (1 << (x + y));
    }
    count += Nqueen_03_sub(n, m, tnq, idx + 1, ans);

    return count;
}

int Nqueen_04(int n, int m, int tnq, int r, string ans) // n means houses and m means rooms
{                                                     
    if (r == n || tnq == 0)
    {
        if (tnq == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }

    int count = 0;
    for (int i = 0; i < m; i++)
    {
        int x = r;
        int y = i;

        if (!(rowA_ & (1 << x)) && !(colA_ & (1 << y)) && !(diag_ & (1 << (x - y + m - 1))) && !(adiag_ & (1 << (x + y))))
        {
            rowA_ ^= (1 << x);
            colA_ ^= (1 << y);
            diag_ ^= (1 << (x - y + m - 1));
            adiag_ ^= (1 << (x + y));

            count += Nqueen_04(n, m, tnq - 1, r + 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");

            rowA_ ^= (1 << x);
            colA_ ^= (1 << y);
            diag_ ^= (1 << (x - y + m - 1));
            adiag_ ^= (1 << (x + y));
        }
    }
    return count;
}

int Nqueen_04_sub(int n, int m, int tnq, int r, string ans) // n means houses and m means rooms
{                                                  
    if (r == n || tnq == 0)
    {
        if (tnq == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }

    int count = 0;
    for (int i = 0; i < m; i++)
    {
        int x = r;
        int y = i;

        if (!(rowA_ & (1 << x)) && !(colA_ & (1 << y)) && !(diag_ & (1 << (x - y + m - 1))) && !(adiag_ & (1 << (x + y))))
        {
            rowA_ ^= (1 << x);
            colA_ ^= (1 << y);
            diag_ ^= (1 << (x - y + m - 1));
            adiag_ ^= (1 << (x + y));

            count += Nqueen_04_sub(n, m, tnq - 1, r + 1, ans + "(" + to_string(x) + ", " + to_string(y) + ") ");

            rowA_ ^= (1 << x);
            colA_ ^= (1 << y);
            diag_ ^= (1 << (x - y + m - 1));
            adiag_ ^= (1 << (x + y));
        }
    }
    count += Nqueen_04_sub(n, m, tnq, r + 1, ans);
    return count;
}

void Nqueen()
{
    // rowA=new boolean[n];

    int n = 6;
    int m = 6;
    rowA.resize(n, false);
    colA.resize(m, false);
    diag.resize(n + m - 1, false);
    adiag.resize(n + m - 1, false);

    vector<vector<bool>> boxes(n, vector<bool>(m, false));
    // cout << Nqueen_01(boxes, n, 0, "") << endl;
    // cout << Nqueen_02(n, m, n, 0, "") << endl;
    // cout << Nqueen_03(n, m, n, 0, "") << endl;
    // cout << Nqueen_04(n, m, 4, 0, "") << endl;
    // cout << Nqueen_03_sub(n, m, 4, 0, "") << endl;
    cout << Nqueen_04_sub(n, m, 4, 0, "") << endl;
}

int main()
{
    int n=4;
    // vector <bool> boxes(n,false);
    // cout<<combinationQueen1D(boxes, 0, 3, 0, "");
    // cout<<permutationQueen1D(boxes, 0, 3, "");
    // cout<<permutationQueen1D_sub(boxes, 0, 0, 3, "");
    // cout<<combinationQueen1D_sub(boxes, 0, 3, 0, "");

    vector<vector<bool>> boxes(5,vector<bool>(5,false));
    cout<<permutationQueen2D(boxes, 0, 3, "");

    Nqueen();

    return 0;
}