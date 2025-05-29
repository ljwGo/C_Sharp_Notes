#include "buyer.h"
#include <vector>
#include <map>
using namespace std;

unsigned int Buyer::staticBuyerId = 1;

//Buyer::Buyer(){
//	payMoney = 0;
//	money = 0;
//	name = "";
//	address = "";
//	password = "";
//	account = "";
//	pCurOrder = new Order(staticBuyerId);
//	id = staticBuyerId++;
//	//_isInit = false;
//}
Buyer::Buyer(string name, string account, string password, string address, double money, CustomerGroup<Buyer*>& customerGroup) {
	if (account == "") {
		cout << "账号不能为空!!!" << endl;
		throw 0;
	}
	if (customerGroup.isAccountExist(account)) {
		cout << "账号已经存在了!!!" << endl;
		throw 0;
	}
	this->payMoney = 0;
	this->money = money;
	this->name = name;
	this->account = account;
	this->password = password;
	this->address = address;
	this->pCurOrder = new Order(staticBuyerId);
	id = Buyer::staticBuyerId++;
	//this->_isInit = true;
}
Buyer::~Buyer() {
	delete pCurOrder;
	pCurOrder = NULL;
}
string Buyer::getName() const {
	return name;
}
string Buyer::getAccount() const {
	return account;
}
string Buyer::getAddress() const {
	return address;
}
double Buyer::getPayMoney() const {
	return payMoney;
}
unsigned int Buyer::getId() const {
	return id;
}
void Buyer::buyBookById(unsigned int id, unsigned int amount, BookShelf<Book*>& bookShelf) {
	Book* pBook;
	// 从书架上取书
	pBook = bookShelf.getEleById(id);

	if (amount == 0) {
		cout << "购买数量不能为0" << endl;
	}
	// 如果书存在, 且数量足够, 且购买数量不为0
	else if (pBook != NULL && pBook->getAmount() >= amount + this->pCurOrder->getBookAmount(pBook)) {
		pCurOrder->addBook(pBook, amount);
		cout << "成功订购编号为" << id << "的书" << amount << "本" << endl;
		cout << endl;
	}
	// 书不存在
	else if(pBook == NULL) {
		cout << "编号为" << id << "的书不存在" << endl;
		cout << endl;
	}
	// 书数量不够
	else {
		cout << "编号为" << id << "的书数量不足" << endl;
		cout << endl;
	}
}
void Buyer::buyBookByTitle(string title, unsigned int amount, BookShelf<Book*>& bookShelf) {
	Book* pBook;
	pBook = bookShelf.getEleByTitle(title);
	if (amount == 0) {
		cout << "购买数量不能为0" << endl;
	}
	else if (pBook != NULL && pBook->getAmount() >= amount + this->pCurOrder->getBookAmount(pBook)) {
		pCurOrder->addBook(pBook, amount);
		cout << "成功订购书名为<< " << title << " >>的书" << amount << "本" << endl;
		cout << endl;
	}
	else if (pBook == NULL) {
		cout << "书名为<< " << title << " >>的书不存在" << endl;
		cout << endl;
	}
	else {
		cout << "书名为<< " << title << " >>的书数量不足" << endl;
		cout << endl;
	}
}
void Buyer::removeBookById(unsigned int id, unsigned int amount) {
	bool success = false;
	for (map<Book*, unsigned int>::iterator it = pCurOrder->begin(); it != pCurOrder->end(); it++) {
		Book* pBook = it->first;

		// 相同则减少书的购买数量
		if (pBook->getId() == id) {
			success = true;
			pCurOrder->_isChange = true;

			// 订单原有数量小于要减去的数量(unsigned整形不能用<0的方式比较), 就将它从订单中移除
			if (it->second <= amount) {
				pCurOrder->tables.erase(it);
				break;
			}

			// 减少数量
			it->second -= amount;

			break;
		}
	}

	if (success) {
		cout << "成功减少编号为 " << id << " 的书" << amount << "本" << endl;
	}
	else {
		cout << "编号为 " << id << " 的书" << "不在订单中" << endl;
	}
}
void Buyer::removeBookByTitle(string title, unsigned int amount) {
	bool success = false;

	for (map<Book*, unsigned int>::iterator it = pCurOrder->begin(); it != pCurOrder->end(); it++) {
		Book* pBook = it->first;

		// 相同则较少书的购买数量
		if (!title.compare(pBook->getTitle())) {
			success = true;
			pCurOrder->_isChange = true;

			// 数量小于0, 就将它从订单中移除
			if (it->second <= amount) {
				pCurOrder->tables.erase(it);
				break;
			}
			// 减少数量
			it->second -= amount;
			break;
		}
	}
	
	if (success) {
		cout << "成功减少书名为<< " << title << " >>的书" << amount << "本" << endl;
	}
	else {
		cout << "书名为" << title << "的书" << "不在订单中" << endl;
	}
}
void Buyer::setBookById(unsigned int id, unsigned int amount, BookShelf<Book*>& bookShelf) {
	bool success = false;

	for (map<Book*, unsigned int>::iterator it = pCurOrder->begin(); it != pCurOrder->end(); it++) {
		Book* pBook = it->first;

		if (pBook->getId() == id) {
			// 书的数量足够
			if (pBook->getAmount() >= amount){
				success = true;
				// 设置订单中书的数量
				it->second = amount;
				pCurOrder->_isChange = true;

				if (it->second == 0) {
					pCurOrder->tables.erase(it);
				}
			}
			break;
		}
	}

	if (success) {
		cout << "成功修改数量为" << (amount <= 0 ? 0 : amount) << "本" << endl;
	}
	else {
		cout << "编号为 " << id << " 的书" << "不在订单中" << endl;
	}
}
void Buyer::setBookByTitle(string title, unsigned int amount, BookShelf<Book*>& bookShelf) {
	bool success = false;

	for (map<Book*, unsigned int>::iterator it = pCurOrder->begin(); it != pCurOrder->end(); it++) {
		Book* pBook = it->first;

		if (!pBook->getTitle().compare(title)) {
			// 书的数量足够
			if (pBook->getAmount() >= amount) {
				success = true;
				// 设置订单中书的数量
				it->second = amount;
				pCurOrder->_isChange = true;

				if (it->second == 0) {
					pCurOrder->tables.erase(it);
				}
			}
			break;
		}
	}

	if (success) {
		cout << "成功修改数量为" << (amount <= 0 ? 0 : amount) << "本" << endl;
	}
	else {
		cout << "书名为<< " << title << " >>的书" << "不在订单中" << endl;
	}
}
void Buyer::resetOrder() {
	pCurOrder->reset();
}
void Buyer::pay(BookShelf<Book*>& bookShelf) {
	double orderPrice = 0;
	// 如果订单中的书, 在书架上都能找到, 并且数量足够
	if (bookShelf.check(pCurOrder)) {
		// 获取订单价格
		orderPrice = pCurOrder->getOrderPrice();
		// 根据顾客等级打折扣
		setPayMoney(orderPrice);
		// 查看余额是否充足
		if (money >= getPayMoney()) {
			// 扣除金额
			money -= getPayMoney();
			payMoney = 0;
			// 更新书架上书的数量信息
			for (typename map<Book*, unsigned int>::iterator it = pCurOrder->tables.begin(); it != pCurOrder->tables.end(); it++) {
				it->first->decreaseBook(it->second);
			}
			// 清除订单, 生成新的订单对象
			delete pCurOrder;
			pCurOrder = new Order(id);
			cout << "购买成功!!!" << endl;
			cout << endl;
		}
		else {
			cout << "您的余额不足, 支付失败, 请查看订单信息和您的余额" << endl;
			cout << endl;
		}
	}
}
void Buyer::showOrder() {
	pCurOrder->showOrderInfo();
}
void Buyer::recharge(double more) {
	money += more;
}
void Buyer::showMoney() const {
	cout << "余额为: " << money << endl;
}
//bool Buyer::hasInit() {
//	return _isInit;
//}
//}
bool Buyer::passwordVaild(string password) const {
	return !password.compare(this->password);
}

ostream& operator << (ostream& out, Buyer& buyer) {
	buyer.display();
	return out;
}