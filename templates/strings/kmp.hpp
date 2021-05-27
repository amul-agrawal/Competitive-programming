// pi[i] => longest suffix ending at i, which is also a prefix.
// pi[n-1] <= n-1
vector<int> prefix_function(string s)
{
	int n = s.length();
	vector<int> pi(n);
	for(int i=1;i<n;i++)
	{
		int j = pi[i-1];
		while(j > 0 and s[i] != s[j])
			j = pi[j-1];
		if(s[i] == s[j])
			j++;
		pi[i] = j;
	}
	return pi;
}

// It computes automation for string s, 
// if we know current pi is i and we are going to add character ch,
// then new pi will be aut[i][ch]
void compute_automaton(string s, vector<vector<int>>& aut) {
    s += '#';
    int n = s.size();
    vector<int> pi = prefix_function(s);
    aut.assign(n, vector<int>(26));
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
            if (i > 0 && 'a' + c != s[i])
                aut[i][c] = aut[pi[i-1]][c];
            else
                aut[i][c] = i + ('a' + c == s[i]);
        }
    }
}