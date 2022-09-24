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
	if (valor.second.second < (*T)->item.value.second.second)
		Insert(&(*T)->left, valor);
	else if (valor.second.second > (*T)->item.value.second.second)
		Insert(&(*T)->right, valor);
}

void HeightTreeWidth(int *maxCont, Tree **T){
	queue<Tree*> tempFila;
	vector<bool> translate;
	Tree *temp;
	int tempCont=1,cont=0;
	(*maxCont)=0;
	tempFila.push((*T));
	while (!(tempFila.empty())){
		cont=0;
		for (int i = 0; i < tempCont; i++){
			temp =tempFila.front();
			translate=temp->item.translate;
			tempFila.pop();
			if (temp->left) {
				tempFila.push(temp->left);
				temp->left->item.nivel=(*maxCont)+1;
				cont++;
				translate.push_back(0);
				temp->left->item.translate=translate;
			}
			translate=temp->item.translate;
			if (temp->right) {
				tempFila.push(temp->right);
				temp->right->item.nivel=(*maxCont)+1;
				cont++;
				translate.push_back(1);
				temp->right->item.translate=translate;
			}
		}
		tempCont=cont;
		(*maxCont)++;
	}
}