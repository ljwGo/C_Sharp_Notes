#ifndef _ORDER_H
#define _ORDER_H

#include <map>
#include <string>
#include "book.h"

using namespace std;

class Order {
public:
	//Order();
	Order(unsigned int buyerId); // 将订单和购买者关联起来
	void reset(); // 充值订单
	void calcPrice(); // 计算订单内书籍的总价格
	double getOrderPrice(); // 返回订单中书的总价格
	unsigned int getBuyerId() const; // 返回订单的所属者id
	void addBook(Book* pBook, unsigned int amount); // 往订单加入指定数量的书籍
	void removeBook(Book* pBook, unsigned int amount); // 删除指定数量的书籍
	void setBook(Book* pBook, unsigned int amount); // 设置书籍数量
	//bool hasInit();
	unsigned int getBookAmount(Book* pBook); // 返回订单中该书的数量
	void showOrderInfo(); // 显示订单信息
	map<Book*, unsigned int>::iterator begin(); // order对象的begin函数返回封装map的begin迭代器
	map<Book*, unsigned int>::iterator end();
	friend std::ostream& operator<< (std::ostream& out, Order& order);
	friend class Buyer;
private:
	static unsigned int orderId; // 静态订单号
	unsigned int id; // 订单号
	unsigned int buyerId; // 谁的订单(购买者的id)
	double orderPrice; // 订单内书籍的总价格
	map<Book*, unsigned int> tables; // 购物清单, key是书, value是购买书的数量(注意, 不等于书的库存量)
	bool _isChange; // 避免频繁计算总价格, 该属性用于标记order是否发生了改变
	//bool _isInit;
};

#endif