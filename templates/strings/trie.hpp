struct node {
	node *child[2] = {NULL, NULL};
	int below = 0;
};

node* getnode()
{
	node *temp = new node;
	return temp;
}

// finally in the end should return root.
node* insert(node* curr,int x,int level=30)
{
	curr->below++;
	// reached last node.
	if(level == -1)
		return curr;

	int bit = (x>>level)&1;
	if(curr->child[bit] == NULL)
		curr->child[bit] = getnode();

	curr->child[bit] = insert(curr->child[bit], x, level - 1);
	return curr;
}

int nodecount(node* nc)
{
	if(nc==NULL) return 0;
	else return nc->below;
}

// count x^a[j] < k
int count(node* curr,int x,int k,int level=30)
{
	if(level == -1 or curr == NULL)
		return 0;

	int xbit = (x>>level)&1;
	int kbit = (k>>level)&1;
	if(kbit == 1)
	{
		// add 0 and go 1.
		if(xbit == 1) return nodecount(curr->child[1]) + count(curr->child[0], x, k, level-1);
		if(xbit == 0) return nodecount(curr->child[0]) + count(curr->child[1], x, k, level-1);
	}
	else
	{
		// go 0. 
		if(xbit == 1) return count(curr->child[1], x, k, level-1);
		if(xbit == 0) return count(curr->child[0], x, k, level-1);
	}
}