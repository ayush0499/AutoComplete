#include<bits/stdc++.h>
using namespace std;

class TrieNode
{
public:
	unordered_map<char,TrieNode*>children;
	bool isWordEnd;
	TrieNode()
	{
		isWordEnd=false;
	}
};

void insert(TrieNode *root, string key)
{
	TrieNode *pCrawl = root;

	for (int level = 0; level < key.size(); level++)
	{
		char index = key[level];
		if (!pCrawl->children[index])
			pCrawl->children[index] = new TrieNode();

		pCrawl = pCrawl->children[index];
	}

	pCrawl->isWordEnd = true;
}

bool search(TrieNode *root,string key)
{
	int length = key.size();
	struct TrieNode *pCrawl = root;
	for (int level = 0; level < length; level++)
	{
		char index = key[level];

		if (!pCrawl->children[index])
			return false;

		pCrawl = pCrawl->children[index];
	}

	return pCrawl->isWordEnd;
}

bool isLastNode(TrieNode* root)
{
	return root->children.empty();
}

void suggestionsRec(TrieNode* root, string currPrefix)
{
	if (root->isWordEnd)
	{
		cout << currPrefix;
		cout << endl;
	}

	
	if (isLastNode(root))
		return;

	for(auto x:root->children)
	{
		currPrefix.push_back(x.first);
		suggestionsRec(x.second, currPrefix);
		currPrefix.pop_back();

	}
}

int printAutoSuggestions(TrieNode* root,string query)
{
	TrieNode* pCrawl = root;

	int level;
	int n = query.size();
	for (level = 0; level < n; level++)
	{
		char index = query[level];

		if (!pCrawl->children[index])
			return 0;

		pCrawl = pCrawl->children[index];
	}

	bool isWord = (pCrawl->isWordEnd == true);

	bool isLast = isLastNode(pCrawl);

	if (isWord && isLast)
	{
		cout << query << endl;
		return -1;
	}

	if (!isLast)
	{
		string prefix = query;
		suggestionsRec(pCrawl, prefix);
		return 1;
	}
}

int main()
{
	freopen("trieoutput.txt","w",stdout);
	TrieNode* root = new TrieNode();
	insert(root, "hello");
	insert(root, "dog");
	insert(root, "hell");
	insert(root, "cat");
	insert(root, "a");
	insert(root, "hel");
	insert(root, "help");
	insert(root, "helps");
	insert(root, "helping");
	int comp = printAutoSuggestions(root, "hel");

	if (comp == -1)
		cout << "No other strings found with this prefix\n";

	else if (comp == 0)
		cout << "No string found with this prefix\n";

	return 0;
}