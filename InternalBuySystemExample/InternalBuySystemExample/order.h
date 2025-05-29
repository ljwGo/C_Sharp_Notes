#ifndef _ORDER_H
#define _ORDER_H

#include <map>
#include <string>
#include "book.h"

using namespace std;

class Order {
public:
	//Order();
	Order(unsigned int buyerId); // �������͹����߹�������
	void reset(); // ��ֵ����
	void calcPrice(); // ���㶩�����鼮���ܼ۸�
	double getOrderPrice(); // ���ض���������ܼ۸�
	unsigned int getBuyerId() const; // ���ض�����������id
	void addBook(Book* pBook, unsigned int amount); // ����������ָ���������鼮
	void removeBook(Book* pBook, unsigned int amount); // ɾ��ָ���������鼮
	void setBook(Book* pBook, unsigned int amount); // �����鼮����
	//bool hasInit();
	unsigned int getBookAmount(Book* pBook); // ���ض����и��������
	void showOrderInfo(); // ��ʾ������Ϣ
	map<Book*, unsigned int>::iterator begin(); // order�����begin�������ط�װmap��begin������
	map<Book*, unsigned int>::iterator end();
	friend std::ostream& operator<< (std::ostream& out, Order& order);
	friend class Buyer;
private:
	static unsigned int orderId; // ��̬������
	unsigned int id; // ������
	unsigned int buyerId; // ˭�Ķ���(�����ߵ�id)
	double orderPrice; // �������鼮���ܼ۸�
	map<Book*, unsigned int> tables; // �����嵥, key����, value�ǹ����������(ע��, ��������Ŀ����)
	bool _isChange; // ����Ƶ�������ܼ۸�, ���������ڱ��order�Ƿ����˸ı�
	//bool _isInit;
};

#endif