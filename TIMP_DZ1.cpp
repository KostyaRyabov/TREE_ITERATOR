#include <iostream>
#include <vector>
#include "tree.h"

#include <conio.h>

int main()
{
	tree *Tree = new tree();
	Tree->Fill();
	Tree->Draw();

	Observer observer;
	Tree->attach(observer);

	tree_Iterator* iter = Tree->createDFSiterator();
	std::cout << std::endl << "__dfs__" << std::endl << std::endl;
	while (iter->hasNext()) {
		std::cout << "[" << iter->getValue() << "] " << std::endl;
		iter->next();
	}

	tree_Iterator* iter1 = Tree->createBFSiterator();
	std::cout << std::endl << "__bfs__" << std::endl << std::endl;
	while (iter1->hasNext()) {
		std::cout << "[" << iter1->getValue() << "] " << std::endl;
		iter1->next();
	}

	delete Tree, iter, iter1;

	_getch();
};