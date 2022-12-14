#include "map.hpp"
Hash::Hash(){

}

void Hash::normalize(){
    auto itmin = min_element(this->umap.begin(), this->umap.end(),[](decltype(this->umap)::value_type& l, decltype(this->umap)::value_type& r) -> bool { return l.second.first < r.second.first; });
    auto itmax = min_element(this->umap.begin(), this->umap.end(),[](decltype(this->umap)::value_type& l, decltype(this->umap)::value_type& r) -> bool { return l.second.first > r.second.first; });
    unordered_map<string, pair<int,float>>::iterator itr;
    for (itr = this->umap.begin(); itr != this->umap.end(); itr++)
        itr->second.second=((float)(itr->second.first)/((itmax->second.first) - (itmin->second.first)));
}

void Hash::fillMap(){
    fstream myFile;
    string caminho,palavras,linha,arquivos,fileName;
    fileName = "politica.txt";
    caminho="files/";
    myFile.open(caminho.append(fileName));
    if (!myFile)
        printf("Arquivo não encontrado\n");
    while (myFile >> palavras)
    {
        while(palavras.back() == ',' || palavras.back() =='.' || palavras.back() =='!' || palavras.back() =='?' || palavras.back() ==';' || palavras.back() ==':' || palavras.back() ==')' || palavras.back() =='-' || palavras.back() =='\'' || palavras.back() =='\"' || palavras.back() =='/') palavras.pop_back();
        while(palavras.front()=='('||palavras.front()=='-'||palavras.front()=='\''||palavras.front()=='\"') palavras.erase(palavras.begin());
        transform(palavras.begin(), palavras.end(), palavras.begin(),[](unsigned char c){ return tolower(c); });
        //tratamento para remoção de StopWords
        if (palavras.size()>0){
            if (palavras.compare("a")&&palavras.compare("nos")&&palavras.compare("à")&&palavras.compare("e")&&palavras.compare("ser")
            &&palavras.compare("é")&&palavras.compare("uma")&&palavras.compare("em")&&palavras.compare("como")
            &&palavras.compare("por")&&palavras.compare("da")&&palavras.compare("das")&&palavras.compare("dos")&&palavras.compare("um")
            &&palavras.compare("com")&&palavras.compare("o")&&palavras.compare("de")&&palavras.compare("do")
            &&palavras.compare("no")&&palavras.compare("na")&&palavras.compare("que")&&palavras.compare("se")&&palavras.compare("ao")
            &&palavras.compare("as")&&palavras.compare("não")){
                if(this->umap.find(palavras)==this->umap.end())
                    this->umap[palavras].first=1;
                else
                    this->umap[palavras].first+=1;
            }
        }
    }
    myFile.close();
}



void Hash::CriaArvore(Tree **TREE){
    vector<pair<string, pair<int,float>>> vec;
    for (auto& it : this->umap)
        vec.push_back(it);
    sort(vec.begin(), vec.end(), comparadores);

    vector<Tree*> rec;
    for (size_t i = 0; i < vec.size(); i++){
        Tree *T;
        initializeTree(&T);
        Insert(&T,vec[i]);
        rec.push_back(T);
    }
    while (rec.size()>2){
        Tree *T = new Tree;
        (*T).item.value.second.second=rec[0]->item.value.second.second+rec[1]->item.value.second.second;
        (*T).right=rec[1];
        (*T).left=rec[0];
        rec.erase(rec.begin());
        rec.erase(rec.begin());
        rec.push_back(T);
        sort(rec.begin(), rec.end(), comparadoresTree);
    }
    (*TREE)->item.value.second.second=rec[0]->item.value.second.second+rec[1]->item.value.second.second;
    (*TREE)->left=rec[0];
    rec.erase(rec.begin());
    if (!(rec.empty()))
        (*TREE)->right=rec[1];
}

void Result(Tree **T){
    string caminho, palavras,nome;
    fstream myFile;
    ofstream binaryFile("files/fileresult.txt");
    unordered_map <string, vector<bool>> hash;
    queue<Tree*> tempFila;
	Tree *temp;
	int tempCont=1,cont=0,valor;
	tempFila.push((*T));
	while (!(tempFila.empty())){
		cont=0;
		for (int i = 0; i < tempCont; i++){
			temp =tempFila.front();
            if (temp->item.value.first!="")
                hash[temp->item.value.first]=temp->item.t;
			tempFila.pop();
			if (temp->left) {
				tempFila.push(temp->left);
				cont++;
			}
			if (temp->right) {
				tempFila.push(temp->right);
				cont++;
			}
		}
		tempCont=cont;
    }
    caminho="files/";
    nome = "politica.txt";
    myFile.open(caminho.append(nome));
    while (myFile >> palavras)
    {
        while(palavras.back() == ',' || palavras.back() =='.' || palavras.back() =='!' || palavras.back() =='?' || palavras.back() ==';' || palavras.back() ==':' || palavras.back() ==')' || palavras.back() =='-' || palavras.back() =='\'' || palavras.back() =='\"' || palavras.back() =='/')
            palavras.pop_back();
        while(palavras.front()=='('||palavras.front()=='-'||palavras.front()=='\''||palavras.front()=='\"')
            palavras.erase(palavras.begin());
        valor=palavras[1];
        if(palavras.front()==-61 && valor>=-128 && valor<=-99)
            palavras[1]=palavras[1]+32;
        transform(palavras.begin(), palavras.end(), palavras.begin(),[](unsigned char c){ return tolower(c); });
        //tratamento para remoção de StopWords
        if (palavras.size()>0){
            if (palavras.compare("a")&&palavras.compare("nos")&&palavras.compare("à")&&palavras.compare("e")&&palavras.compare("ser")
            &&palavras.compare("é")&&palavras.compare("uma")&&palavras.compare("em")&&palavras.compare("como")
            &&palavras.compare("por")&&palavras.compare("da")&&palavras.compare("das")&&palavras.compare("dos")
            &&palavras.compare("um")&&palavras.compare("com")&&palavras.compare("o")&&palavras.compare("de")&&palavras.compare("do")
            &&palavras.compare("no")&&palavras.compare("na")&&palavras.compare("que")&&palavras.compare("se")&&palavras.compare("ao")
            &&palavras.compare("as")&&palavras.compare("não")){
                for (size_t i = 0; i < hash[palavras].size(); i++)
                    binaryFile << hash[palavras][i];
                binaryFile << " ";
            }
        }
    }
    binaryFile.close();
    myFile.close();
}
bool comparadores(pair<string, pair<int,float>>&a,pair<string, pair<int,float>>& b){
    return a.second.second < b.second.second;
}
bool comparadoresTree(Tree*&a,Tree*& b){
    return a->item.value.second.second < b->item.value.second.second;
}