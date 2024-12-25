int kadane(int st,int ed,vector<int>&v){
   int max_so_far = -1e9,max_yet=0;
   for(int i=st;i<=ed;i++){
      max_yet += v[i];
      if(max_yet > max_so_far){max_so_far = max_yet;
      if(max_yet < 0) max_yet = 0;
   }
   return max_so_far;
}