#include "tree_Iterator.h"


int tree_Iterator::getValue() {
	return current->value;
}

node* tree_Iterator::begin() {
	return Tree->root;
}

//-------------------------------------------------------------------
//-------------------------------DFS---------------------------------
//-------------------------------------------------------------------

dfs_iter::dfs_iter(tree* T) {
	Tree = T;
	current = Tree->root;
	if (current != nullptr) clear(current);
}

void dfs_iter::clear(node* V) {
	V->visited = false;

	if (V->Left != nullptr) clear(V->Left);
	if (V->Right != nullptr) clear(V->Right);
}

bool dfs_iter::hasNext() {
	if (current != nullptr) {
		if (current->Parent == nullptr) {
			if (current->Left != nullptr && current->Right == nullptr && current->Left->visited) return false;
			else if (current->Right != nullptr && current->Left == nullptr && current->Right->visited) return false;
			else if (current->Left != nullptr && current->Right != nullptr) {
				if (current->Left->visited && current->Right->visited) return false;
			}
		}
		
		return true;
	}
	
	return false;
}

void dfs_iter::next() {
	if (current->Left != nullptr && !current->Left->visited) {
		current = current->Left;
		current->visited = true;
	}
	else if (current->Right != nullptr && !current->Right->visited) {
		current = current->Right;
		current->visited = true;
	}
	else {
		if (current->Left == nullptr && current->Right == nullptr) {
			Tree->notify_observers(current->value);
		}

		do {
			current = current->Parent;
		} while (hasNext() && !(current->Right != nullptr && !current->Right->visited));

		if (current->Right != nullptr && !current->Right->visited) {
			current = current->Right;
			current->visited = true;
		}
	}
}

void dfs_iter::operator= (node& U) {
	if (current != NULL) {
		current = &U;
		clear(current);
	}
}

//-------------------------------------------------------------------
//-------------------------------BFS---------------------------------
//-------------------------------------------------------------------

// s  n b e m
// p: 0	0 1 1
// c: 0 1 0 1
// r: f t f t

bfs_iter::bfs_iter(tree* T) {
	Tree = T;
	current = Tree->root;
	c.push_back(current);
}

bool bfs_iter::hasNext() {
	return !c.empty();
}

void bfs_iter::next() {
	current = c.back();
	p.push_back(current);
	c.pop_back();

	if (current->Left == nullptr && current->Right == nullptr) {
		Tree->notify_observers(current->value);
	}

	if (c.empty()) {
		while (!p.empty()) {
			U = p.front();
			if (U->Left != nullptr) c.push_front(U->Left);
			if (U->Right != nullptr) c.push_front(U->Right);
			p.pop_front();
		}
	}
	
	if (!c.empty()) current = c.back();
}

void bfs_iter::operator= (node& U) {
	current = &U;
}