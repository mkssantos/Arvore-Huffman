#ifndef MAP_HPP
#define MAP_HPP
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include "tree.hpp"

using namespace std;
class Hash{
    private:
        unordered_map <string, pair<int,float>> umap;
    public:
        ~Hash();
        Hash();
    void fillMap();
    void normalize();
    void CreateTree(Tree **TREE);
};
bool comparadores(pair<string, pair<int,float>>& a,pair<string, pair<int,float>>& b);
bool comparadoresTree(Tree*&a,Tree*& b);
void Result(Tree **T);

#endif