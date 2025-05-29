#include "goods.h"

unsigned int Goods::staticGoodId = 1;

Goods::Goods() {
	name = "";
	quantity = 0;
	id = Goods::staticGoodId++;
}
Goods::Goods(string name, unsigned int quantity) {
	this->name = name;
	this->quantity = quantity;
	id = Goods::staticGoodId++;
}
void Goods::init(string name, unsigned int quantity) {
	this->name = name;
	this->quantity = quantity;
}
void Goods::decrease(unsigned int less) {
	// 避免数量少于0
	quantity = quantity < less ? 0 : quantity - less;
}
void Goods::increase(unsigned int more) {
	quantity += more;
}
string Goods::getName() {
	return name;
}
unsigned int Goods::getId() {
	return id;
}
unsigned int Goods::getQuantity() {
	return quantity;
}
