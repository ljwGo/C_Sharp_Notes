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
	string getName() const; // 返回购买者名字
	string getAccount() const; // 返回账户
	string getAddress() const; // 返回购买者地址
	double getPayMoney() const; // 返回购买者应付金额
	unsigned int getId() const; // 返回购买者编号
	void buyBookById(unsigned int id, unsigned int amount, BookShelf<Book*>& bookShelf); // 购买书籍id购买书籍
	void buyBookByTitle(string title, unsigned int amount, BookShelf<Book*>& bookShelf); // 通过书名购买书籍
	void removeBookById(unsigned int id, unsigned int amount); // 根据id删除订单中的购买书的数量
	void removeBookByTitle(string title, unsigned int amount); // 根据书名删除订单中的购买书的数量
	void setBookById(unsigned int id, unsigned int amount, BookShelf<Book*>& bookShelf); // 根据id设置书的数量
	void setBookByTitle(string title, unsigned int amount, BookShelf<Book*>& bookShelf); // 根据书名设置书的数量
	void pay(BookShelf<Book*>& bookShelf); // 付款功能
	void resetOrder(); // 重置订单
	void showOrder(); // 展示订单信息
	void recharge(double more); // 充值金额
	void showMoney() const; // 查看余额
	bool passwordVaild(string password) const;
	//bool hasInit();
	// 虚函数
	virtual void display()=0; // 显示购买者信息
	virtual void setPayMoney(double money)=0; // 计算购买者应付金额
protected:
	static unsigned int staticBuyerId;
	unsigned int id;
	double payMoney; // 最终应付金额
	double money; // 余额
	string name;
	string address;
	string account;
	string password;
	Order* pCurOrder; // 用户订单对象指针, 有且仅有一个
	//OrderGroup<Order*> orderGroup; // 历史订单, 该功能先不做
	//bool _isInit;  // 是否有效， 如果是无参构造函数形成的， 不允许使用, 先不做
};

#endif // !_BUYER_H