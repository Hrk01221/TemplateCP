int fun(int pos,int cnt,bool under,bool started){
    if(pos == num.size()){...basecase...}
    int &ret = dp[pos][cnt][under][started];
    if(ret != -1)return ret;
    ret = 0;
    for(int i=0;i<=9;i++){
        int digit = num[pos] - '0';
        if(!under and i > digit)break;
        int is_under = under;
        if(i < digit)is_under = 1;
        int is_started = started || i != 0;
        ret += fun(pos + 1 , cnt + (i!=0) , is_under , is_started);
    }return ret;
}