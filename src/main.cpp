#include "map.hpp"

int main(){
	int height=0;

	Tree *T = new Tree;
	Hash *map = new Hash;

	map->fillMap();
	map->normalize();
	map->CreateTree(&T);
	HeightTreeWidth(&height,&T);
	printf("A altura da arvore pelo metodo de HuffMan e:%d\n", height);
	Result(&T);

	return 0;
}