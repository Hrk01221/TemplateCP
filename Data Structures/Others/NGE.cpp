vector<int> nextGreater(const vector<int>& a) {
    int n = a.size();
    vector<int> nge(n, -1); // -1 if none exists
    stack<int> st;// store indices
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] < a[i]) {
            nge[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return nge;
}
