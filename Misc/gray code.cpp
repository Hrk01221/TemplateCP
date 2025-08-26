int gray_code(int x){return x ^ (x >> 1);}
int inverse_gray_code(int x){
    int h = 1, res = 0;
    do{
        if (x & 1) res ^= h;
        x >>= 1, h = (h << 1) + 1;
    } while (x);
    return res;
}