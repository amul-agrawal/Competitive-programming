// TODO: set block size
const int block_size;

bool cmp(pair<int, int> p, pair<int, int> q) {
    if (p.first / block_size != q.first / block_size)
        return p < q;
    return (p.first / block_size & 1) ? (p.second < q.second) : (p.second > q.second);
}

struct Query {
    int l, r, idx;
};

class MO
{
public:
	void remove(idx);  // TODO: remove value at idx from data structure
	void add(idx);     // TODO: add value at idx from data structure
	int get_answer();  // TODO: extract the current answer of the data structure
	vector<int> run(vector<Query> queries) {
	    vector<int> answers(queries.size());
	    sort(queries.begin(), queries.end(), cmp);

	    // TODO: initialize data structure

	    int cur_l = 0;
	    int cur_r = -1;
	    // invariant: data structure will always reflect the range [cur_l, cur_r]
	    for (Query q : queries) {
	        while (cur_l > q.l) {
	            cur_l--;
	            add(cur_l);
	        }
	        while (cur_r < q.r) {
	            cur_r++;
	            add(cur_r);
	        }
	        while (cur_l < q.l) {
	            remove(cur_l);
	            cur_l++;
	        }
	        while (cur_r > q.r) {
	            remove(cur_r);
	            cur_r--;
	        }
	        answers[q.idx] = get_answer();
	    }
	    return answers;
	}
};