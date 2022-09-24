#include "tree.hpp"

void initializeTree(Tree **T){
	(*T) = nullptr;
}

void Insert(Tree **T, pair<string, pair<int,float>> valor){
	if ((*T) == nullptr)
	{
		(*T) = new Tree;
		(*T)->item.value = valor;
		(*T)->item.nivel = 0;
		(*T)->left = nullptr;
		(*T)->right = nullptr;
		return;
	}
}

void HeightTreeWidth(int *maxCont, Tree **T){
	queue<Tree*> tempFila;
	vector<bool> t;
	Tree *temp;
	int tempCont=1,cont=0;
	(*maxCont)=0;
	tempFila.push((*T));
	while (!(tempFila.empty())){
		cont=0;
		for (int i = 0; i < tempCont; i++){
			temp =tempFila.front();
			t=temp->item.t;
			tempFila.pop();
			if (temp->left) {
				tempFila.push(temp->left);
				temp->left->item.nivel=(*maxCont)+1;
				cont++;
				t.push_back(0);
				temp->left->item.t=t;
			}
			t=temp->item.t;
			if (temp->right) {
				tempFila.push(temp->right);
				temp->right->item.nivel=(*maxCont)+1;
				cont++;
				t.push_back(1);
				temp->right->item.t=t;
			}
		}
		tempCont=cont;
		(*maxCont)++;
	}
}