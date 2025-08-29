const int nmax = 4;
long long int mod = 1e9+7;
struct Matrix{
    long long int val[nmax][nmax];
    int row, col;
    Matrix(int _r, int _c){
        row = _r;
        col = _c;
        for(int i = 0; i<row; i++)
            for(int j = 0; j<col; j++)
                val[i][j] = 0;
    }
    Matrix operator*(Matrix other){
        Matrix result(row, other.col);
        for(int i = 0; i<row; i++){
            for(int j = 0; j<other.col; j++){
                for(int k = 0; k<col; k++){
                    result.val[i][j] += val[i][k] * other.val[k][j];
                    result.val[i][j] %= mod;
                }
            }
        }
        return result;
    }
};
Matrix Matexpo(Matrix X, long long int n){
    Matrix Y(X.row, X.col);
    if(n == 0){
        for(int i = 0; i<X.row; i++)
            Y.val[i][i] = 1;
        return Y;
    }
    Y = Matexpo(X, n/2);
    Y = Y * Y;
    if(n % 2 == 1){
        Y = Y * X;
    }

    return Y;
}
/*
    adjust the matrix size as per requirement as it can cause time limit
    X2 is enough for 1e9
    Matrix F(2, 1);
    F.val[0][0] = a; // change the initial value
    F.val[1][0] = b;
    Matrix M(2, 2);
    M.val[0][0] = 0, M.val[0][1] = 1;//co-efficients
    M.val[1][0] = 1, M.val[1][1] = 1;
    M = Matexpo(M,n); //it will be n-j if base case starts from jth term 
    F = M * F;
    cout<< F.val[0][0]<<endl;
    O(log n)
*/