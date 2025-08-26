int Xor(int n){
    if(n%4==0)return n;
    if(n%4==1)return 1;
    if(n%4==2)return n+1;
    return 0;
}
int XorTill(int l,int r){
    if(l==0)return Xor(r);
    else return Xor(r) xor Xor(l-1);
}