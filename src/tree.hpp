#ifndef Tree_HPP
#define Tree_HPP

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Record{
	pair<string, pair<int,float>> value;
	vector<bool> t;
    int nivel;
};

struct Tree{
	Record item;
	Tree *left, *right;
};

void initializeTree(Tree **T);
void Insert(Tree **T, pair<string, pair<int,float>> valor);
void HeightTreeWidth(int *maxCont, Tree **T);

#endif