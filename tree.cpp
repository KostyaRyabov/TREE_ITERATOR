#include "tree.h"

void tree::addNode(node* lastNode, int newVal) {

	if (root == nullptr) {
		root = new node(newVal);
	}
	else {
		if (newVal < lastNode->value) {
			if (lastNode->Left == nullptr)
			{
				lastNode->Left = new node(newVal);
				lastNode->Left->Parent = lastNode;
			}
			else addNode(lastNode->Left, newVal);
		}
		else if(newVal > lastNode->value){
			if (lastNode->Right == nullptr)
			{
				lastNode->Right = new node(newVal);
				lastNode->Right->Parent = lastNode;
			}
			else addNode(lastNode->Right, newVal);
		}
	}
}

void tree::Fill() {
	int input;

	std::cout << std::endl << "__Fill tree!__ (before entering letters)" << std::endl << std::endl;

	while (std::cin >> input)
	{
		addNode(root, input);
	}
}

void tree::attach(Observer& o)
{
	observers.push_back(&o);
}

node* tree::begin() {
	return root;
}

void tree::notify_observers(int value)
{
	for (Observer* o : observers) {
		o->update(value);
	}
}

tree_Iterator* tree::createDFSiterator() {
	return (tree_Iterator*)(new dfs_iter(this));
}

tree_Iterator* tree::createBFSiterator() {
	return (tree_Iterator*)(new bfs_iter(this));
}

void tree::draw_bind(int level, int X, bool left, bool right) {
	int i;

	//*pos(X, level + 1) = 179;
	
	if (right && left) *pos(X, level + 1) = 193;
	else if (left) *pos(X, level + 1) = 217;
	else *pos(X, level + 1) = 192;

	if (left) {
		for (i = X - 1; *pos(i, level + 1) == 0; i--) *(pos(i, level + 1)) = 196;
	}

	if (right) {
		for (i = X + 1; *pos(i, level + 1) == 0; i++) *(pos(i, level + 1)) = 196;
	}
}

int tree::dfs(node* U, int level, bool isLeft, int offset = 0) {
	int val_len = 0, leftPos = -1, rightPos = -1, tmp = U->value;
	
	if (level > height) height = level;

	if (U->value < 0) val_len++;

	tmp = std::abs(tmp);

	while (tmp > 0) {
		tmp /= 10;
		val_len++;
	}

	val_len += 2;


	if (U->Left != nullptr) {
		leftPos = dfs(U->Left, level + 2, true, offset);
		offset = leftPos;
	}
	
	if (level > 0) {
		if (isLeft) *pos(offset + val_len / 2, level - 1) = 218;
		else *pos(offset + val_len / 2, level - 1) = 191;
		//*pos(offset + val_len / 2, level - 1) = 179;
	}

	if (U->Right != nullptr) {
		rightPos = dfs(U->Right, level + 2, false, offset + mem_offset + val_len);

		if (leftPos != -1) {
			snprintf(pos(offset, level), val_len + 3, "[%d]", U->value);
			draw_bind(level, offset + val_len/2, true, true);
		}
		else {
			snprintf(pos(offset, level), val_len + 3, "[%d]", U->value);
			draw_bind(level, offset + val_len / 2, false, true);
		}

		return rightPos + mem_offset;
	}
	else {
		snprintf(pos(offset, level), val_len + 2, "[%d]", U->value);
		if (leftPos != -1) draw_bind(level, offset + val_len / 2, true, false);
		
		return offset + val_len + mem_offset;
	}
}

void tree::Draw() {
	std::cout << "__Display_Tree__" << std::endl;

	if (root != nullptr) {
		memory = new char[mem_width * mem_height];
		memset(memory, 0, sizeof(char) * mem_width * mem_height);

		dfs(root, 0, false);

		for (int j = 0; j <= height && j < mem_height; j++)
		{
			for (int i = 0; i < mem_width; i++)
			{
				std::cout << *pos(i,j);
			}

			std::cout << std::endl;
		}

		delete[] memory;
	}
}

void tree::cascade_delete(node* U) {
	if (U->Left != nullptr) cascade_delete(U->Left);
	if (U->Right != nullptr) cascade_delete(U->Right);

	delete U;
}

tree::~tree()
{
	if (root != nullptr) cascade_delete(root);
}