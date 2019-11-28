#pragma once

#define mem_height 100
#define mem_width 200
#define mem_offset 0
#define mem_step 3
#define pos(x,y) (memory + mem_width * ((y) % mem_height)  + ((x) % mem_width))

#include "node.h"
#include "Observer.h"
#include "tree_Iterator.h"

#include <iostream>
#include <vector>
#include <string>

class tree {
private:
	node* root = nullptr;
	std::vector<Observer*> observers;

	//for drawing
	int height = 0;
	char* memory = nullptr;
	void draw_bind(int level, int X, bool left, bool right);
	int dfs(node* U, int level, bool isLeft, int offset);
	
	void addNode(node* lastNode, int newVal);
	void cascade_delete(node* U);
public:
	~tree();

	node* begin();
	void Fill();
	void Draw();
	void attach(Observer& o);
	void notify_observers(int value);

	//binding iterator to tree
	tree_Iterator* createDFSiterator();
	tree_Iterator* createBFSiterator();

	friend class tree_Iterator;
	friend class dfs_iter;
	friend class bfs_iter;
};