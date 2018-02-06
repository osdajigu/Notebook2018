struct ahocorasick {
	vector<vector<int>> next;
	vector<int> fail, out, finish, cnt;
	vector<string> words;
    // if there are repeated words and it is necessary to show them
    // 'finish' has to be vvi
	ahocorasick () {
		next.push_back(vector<int>(26));
		finish.push_back(0);
		cnt.push_back(0);
	}
	void insert (string &s) {
		int u = 0;
		for (int i = 0; i < s.size(); ++i) {
			int c = s[i] - 'a';
			if (!next[u][c]) {
				next[u][c] = next.size();
				next.push_back(vector<int>(26));
				finish.push_back(-1);
				cnt.push_back(0);
			}
			u = next[u][c];
		}
		finish[u] = words.size();
		++cnt[u];
		words.push_back(s);
	}
	int get_fail (int pfail, int c) {
		while (!next[pfail][c] && pfail != 0)
			pfail = fail[pfail];
		return next[pfail][c];
	}
	void update_out (int u) {
		out[u] = fail[u];
		while (finish[out[u]] == -1)
			out[u] = fail[out[u]];
	}
	void buildf () {
		queue<int> q;
		fail.assign(next.size(), 0);
		out.assign(next.size(), 0);
		for (int i = 0; i < 26; ++i)
			if(next[0][i]) q.push(next[0][i]);
		while (q.size()) {
			int u = q.front();
			q.pop();
			for (int i = 0; i < 26; ++i) {
				int v = next[u][i];
				if (v) {
					fail[v] = get_fail(fail[u], i);
					cnt[v] += cnt[ fail[v] ];
					q.push(v);
					update_out(v);
				}
			}
		}
	}
	int match (string &s) {
		int cur = 0, matches = 0;
		for (int i = 0; i < s.size(); ++i) {
			int c = s[i] - 'a';
			if (next[cur][c]) cur = next[cur][c];
            else cur = get_fail(fail[cur], c);
			matches += cnt[cur];
			int t = cur;
			while (t != 0) {
				if (finish[t] != -1)
					cout << words[ finish[t] ] << endl;
				t = out[t];
			}
		}
		return matches;
	}
};
