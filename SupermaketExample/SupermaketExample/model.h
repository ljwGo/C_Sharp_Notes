#pragma once
#include <fstream>
#include "container.h"
#include "goods.h"

using namespace std;

class Model {
	class Goods;
public:
	template<class ElE> 
	void load(ifstream& iFile, Container<ELE>& container);
	void save(ofstream& oFile, Container<Goods*>& container);
};

template <class ElE>
void Model::load<ElE>(ifstream& iFile, Container<ELE*>& container) {
	Goods* pGood = new ElE();

	if (iFile.is_open()) {
		while (!iFile.eof()) {
			iFile >> *pGood;
			container.push(pGood);
		}
	}
}

void Model::save(ofstream& oFile, Container<Goods*>& container) {
	Goods* pGood = NULL;

	container.resetIterator();
	
	if (oFile.is_open()) {
		while ((pGood = container.next()) != NULL) {
			oFile << *pGood;
		}
	}
}
