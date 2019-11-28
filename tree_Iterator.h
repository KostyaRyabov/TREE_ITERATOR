#pragma once

#include "node.h"
#include <deque>
#include "tree.h"

class tree_Iterator {
protected:
	tree* Tree = nullptr;

	node *current = nullptr;
public:
	virtual bool hasNext() = 0;
	virtual void next() = 0;
	int getValue();

	node* begin();
};

class dfs_iter : tree_Iterator
{
private:
	void clear(node* V);
public:
	dfs_iter(tree* T);
	bool hasNext();
	void next();
	void operator= (node& U);
};

class bfs_iter : tree_Iterator
{
private:
	node* U;
	std::deque<node*> p, c;
public:
	bfs_iter(tree* T);
	bool hasNext();
	void next();
	void operator= (node& U);
};