#pragma once
class node
{
	node* Parent = nullptr;

	node* Left = nullptr;
	node* Right = nullptr;

	bool visited = false;
public:
	node(int value);
	node();
	~node();

	int value;

	friend class tree;
	friend class tree_Iterator;
	friend class dfs_iter;
	friend class bfs_iter;
};