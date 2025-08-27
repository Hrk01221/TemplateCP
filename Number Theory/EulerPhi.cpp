//phi
void calculatePhi(){
    //phi[i] = i * (1-1/p1) * (1-1/p2) ......;
    for(int i=1;i<=N;i++)phi[i] = i;
    for(int i=2;i<=N;i++){
        if(phi[i]==i)
            for(int j=i;j<=N;j+=i){
                phi[j] -= (phi[j]/i);
            }
    }
}