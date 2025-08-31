__int128 sum = 1e20;
vector<char>dig;
while (ans)dig.pb(ans % 10 | 48), ans /= 10;
if (dig.size()) {
	reverse(all(dig));
	for (auto it : dig)cout << it;
}
else cout << 0 << endl;