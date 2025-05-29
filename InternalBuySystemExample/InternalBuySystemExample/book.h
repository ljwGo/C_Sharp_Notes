// 避免头文件重复导入方式一
#ifndef _BOOK_H
#define _BOOK_H

#include <string>
#include <iostream>
using namespace std;

class Book {
public:
	//Book();
	Book(string title, string author, string publishing, double price, unsigned int amount);
	void display() const; // 展示书的信息
	void setPrice(double price);
	void setPublishing(string publishing);
	void setTitle(string title);
	void setAmount(unsigned int amount);
	void setAuthor(string author);
	void decreaseBook(unsigned int amount); // 减少书的数量
	void init(string title, string author, string publishing, double price, unsigned int amount); // 初始化|更新书的成员
	string getTitle() const;
	string getPublishing() const;
	string getAuthor() const;
	double getPrice() const;
	unsigned int getId() const;
	unsigned int getAmount() const;
	//bool hasInit();
	//bool operator< (const Book& book) const;
	//bool operator== (const Book& book) const;
	friend std::ostream& operator<< (std::ostream& out, Book& book);
private:
	static unsigned int staticBookId;
	unsigned int id;
	unsigned int amount; // 数量
	double price; // 价格
	string publishing; // 出版社
	string title; // 书名
	string author; // 作者
	//bool _isInit;
};

std::ostream& operator<< (std::ostream& out, Book& book);
#endif