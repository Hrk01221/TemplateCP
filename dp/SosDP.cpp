for(int mask = 0 ; mask < (1<<n) ; mask++){
    for(int submask = mask ; submask ; submask = (submask - 1) & mask){
        int rem = mask ^ submask;
            dp[mask] = max(dp[mask],dp[submask]+dp[rem]);
    }
}