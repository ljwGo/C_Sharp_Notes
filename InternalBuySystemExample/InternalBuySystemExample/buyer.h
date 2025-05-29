#ifndef _BUYER_H
#define _BUYER_H

#include <iostream>
#include <string>
#include "order.h"
#include "book.h"
#include "bookShelf.h"
#include "customerGroup.h"

using namespace std;

class Buyer {
public:
	//Buyer();
	Buyer(string name, string account, string password, string address, double money, CustomerGroup<Buyer *>& customerGroup);
	~Buyer();
	string getName() const; // ���ع���������
	string getAccount() const; // �����˻�
	string getAddress() const; // ���ع����ߵ�ַ
	double getPayMoney() const; // ���ع�����Ӧ�����
	unsigned int getId() const; // ���ع����߱��
	void buyBookById(unsigned int id, unsigned int amount, BookShelf<Book*>& bookShelf); // �����鼮id�����鼮
	void buyBookByTitle(string title, unsigned int amount, BookShelf<Book*>& bookShelf); // ͨ�����������鼮
	void removeBookById(unsigned int id, unsigned int amount); // ����idɾ�������еĹ����������
	void removeBookByTitle(string title, unsigned int amount); // ��������ɾ�������еĹ����������
	void setBookById(unsigned int id, unsigned int amount, BookShelf<Book*>& bookShelf); // ����id�����������
	void setBookByTitle(string title, unsigned int amount, BookShelf<Book*>& bookShelf); // �������������������
	void pay(BookShelf<Book*>& bookShelf); // �����
	void resetOrder(); // ���ö���
	void showOrder(); // չʾ������Ϣ
	void recharge(double more); // ��ֵ���
	void showMoney() const; // �鿴���
	bool passwordVaild(string password) const;
	//bool hasInit();
	// �麯��
	virtual void display()=0; // ��ʾ��������Ϣ
	virtual void setPayMoney(double money)=0; // ���㹺����Ӧ�����
protected:
	static unsigned int staticBuyerId;
	unsigned int id;
	double payMoney; // ����Ӧ�����
	double money; // ���
	string name;
	string address;
	string account;
	string password;
	Order* pCurOrder; // �û���������ָ��, ���ҽ���һ��
	//OrderGroup<Order*> orderGroup; // ��ʷ����, �ù����Ȳ���
	//bool _isInit;  // �Ƿ���Ч�� ������޲ι��캯���γɵģ� ������ʹ��, �Ȳ���
};

#endif // !_BUYER_H