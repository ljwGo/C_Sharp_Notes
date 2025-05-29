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
		cout << "�˺Ų���Ϊ��!!!" << endl;
		throw 0;
	}
	if (customerGroup.isAccountExist(account)) {
		cout << "�˺��Ѿ�������!!!" << endl;
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
	// �������ȡ��
	pBook = bookShelf.getEleById(id);

	if (amount == 0) {
		cout << "������������Ϊ0" << endl;
	}
	// ��������, �������㹻, �ҹ���������Ϊ0
	else if (pBook != NULL && pBook->getAmount() >= amount + this->pCurOrder->getBookAmount(pBook)) {
		pCurOrder->addBook(pBook, amount);
		cout << "�ɹ��������Ϊ" << id << "����" << amount << "��" << endl;
		cout << endl;
	}
	// �鲻����
	else if(pBook == NULL) {
		cout << "���Ϊ" << id << "���鲻����" << endl;
		cout << endl;
	}
	// ����������
	else {
		cout << "���Ϊ" << id << "������������" << endl;
		cout << endl;
	}
}
void Buyer::buyBookByTitle(string title, unsigned int amount, BookShelf<Book*>& bookShelf) {
	Book* pBook;
	pBook = bookShelf.getEleByTitle(title);
	if (amount == 0) {
		cout << "������������Ϊ0" << endl;
	}
	else if (pBook != NULL && pBook->getAmount() >= amount + this->pCurOrder->getBookAmount(pBook)) {
		pCurOrder->addBook(pBook, amount);
		cout << "�ɹ���������Ϊ<< " << title << " >>����" << amount << "��" << endl;
		cout << endl;
	}
	else if (pBook == NULL) {
		cout << "����Ϊ<< " << title << " >>���鲻����" << endl;
		cout << endl;
	}
	else {
		cout << "����Ϊ<< " << title << " >>������������" << endl;
		cout << endl;
	}
}
void Buyer::removeBookById(unsigned int id, unsigned int amount) {
	bool success = false;
	for (map<Book*, unsigned int>::iterator it = pCurOrder->begin(); it != pCurOrder->end(); it++) {
		Book* pBook = it->first;

		// ��ͬ�������Ĺ�������
		if (pBook->getId() == id) {
			success = true;
			pCurOrder->_isChange = true;

			// ����ԭ������С��Ҫ��ȥ������(unsigned���β�����<0�ķ�ʽ�Ƚ�), �ͽ����Ӷ������Ƴ�
			if (it->second <= amount) {
				pCurOrder->tables.erase(it);
				break;
			}

			// ��������
			it->second -= amount;

			break;
		}
	}

	if (success) {
		cout << "�ɹ����ٱ��Ϊ " << id << " ����" << amount << "��" << endl;
	}
	else {
		cout << "���Ϊ " << id << " ����" << "���ڶ�����" << endl;
	}
}
void Buyer::removeBookByTitle(string title, unsigned int amount) {
	bool success = false;

	for (map<Book*, unsigned int>::iterator it = pCurOrder->begin(); it != pCurOrder->end(); it++) {
		Book* pBook = it->first;

		// ��ͬ�������Ĺ�������
		if (!title.compare(pBook->getTitle())) {
			success = true;
			pCurOrder->_isChange = true;

			// ����С��0, �ͽ����Ӷ������Ƴ�
			if (it->second <= amount) {
				pCurOrder->tables.erase(it);
				break;
			}
			// ��������
			it->second -= amount;
			break;
		}
	}
	
	if (success) {
		cout << "�ɹ���������Ϊ<< " << title << " >>����" << amount << "��" << endl;
	}
	else {
		cout << "����Ϊ" << title << "����" << "���ڶ�����" << endl;
	}
}
void Buyer::setBookById(unsigned int id, unsigned int amount, BookShelf<Book*>& bookShelf) {
	bool success = false;

	for (map<Book*, unsigned int>::iterator it = pCurOrder->begin(); it != pCurOrder->end(); it++) {
		Book* pBook = it->first;

		if (pBook->getId() == id) {
			// ��������㹻
			if (pBook->getAmount() >= amount){
				success = true;
				// ���ö������������
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
		cout << "�ɹ��޸�����Ϊ" << (amount <= 0 ? 0 : amount) << "��" << endl;
	}
	else {
		cout << "���Ϊ " << id << " ����" << "���ڶ�����" << endl;
	}
}
void Buyer::setBookByTitle(string title, unsigned int amount, BookShelf<Book*>& bookShelf) {
	bool success = false;

	for (map<Book*, unsigned int>::iterator it = pCurOrder->begin(); it != pCurOrder->end(); it++) {
		Book* pBook = it->first;

		if (!pBook->getTitle().compare(title)) {
			// ��������㹻
			if (pBook->getAmount() >= amount) {
				success = true;
				// ���ö������������
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
		cout << "�ɹ��޸�����Ϊ" << (amount <= 0 ? 0 : amount) << "��" << endl;
	}
	else {
		cout << "����Ϊ<< " << title << " >>����" << "���ڶ�����" << endl;
	}
}
void Buyer::resetOrder() {
	pCurOrder->reset();
}
void Buyer::pay(BookShelf<Book*>& bookShelf) {
	double orderPrice = 0;
	// ��������е���, ������϶����ҵ�, ���������㹻
	if (bookShelf.check(pCurOrder)) {
		// ��ȡ�����۸�
		orderPrice = pCurOrder->getOrderPrice();
		// ���ݹ˿͵ȼ����ۿ�
		setPayMoney(orderPrice);
		// �鿴����Ƿ����
		if (money >= getPayMoney()) {
			// �۳����
			money -= getPayMoney();
			payMoney = 0;
			// ������������������Ϣ
			for (typename map<Book*, unsigned int>::iterator it = pCurOrder->tables.begin(); it != pCurOrder->tables.end(); it++) {
				it->first->decreaseBook(it->second);
			}
			// �������, �����µĶ�������
			delete pCurOrder;
			pCurOrder = new Order(id);
			cout << "����ɹ�!!!" << endl;
			cout << endl;
		}
		else {
			cout << "��������, ֧��ʧ��, ��鿴������Ϣ���������" << endl;
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
	cout << "���Ϊ: " << money << endl;
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