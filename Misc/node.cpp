struct node{
    int id,cost,k;
    node(int _id,int _cost,int _k){
        id = _id;
        cost = _cost;
        k = _k;
    }
    bool operator < (const node &a) const {
        return a.cost < cost;
    }
};