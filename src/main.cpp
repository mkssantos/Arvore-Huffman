#include "map.hpp"

int main(){
	int height=0;
	Tree *T = new Tree;
	Hash *map = new Hash;

	map->fillMap();
	map->normalize();
	map->CriaArvore(&T);
	HeightTreeWidth(&height,&T);

	cout << "A altura da arvore pelo metodo de HuffMan e: " << height << endl;
	cout << "Arquivo resultante atualizado" << endl;
	Result(&T);

	return 0;
}