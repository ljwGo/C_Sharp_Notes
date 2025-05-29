// ����ͷ�ļ��ظ����뷽ʽһ
#ifndef _BOOK_H
#define _BOOK_H

#include <string>
#include <iostream>
using namespace std;

class Book {
public:
	//Book();
	Book(string title, string author, string publishing, double price, unsigned int amount);
	void display() const; // չʾ�����Ϣ
	void setPrice(double price);
	void setPublishing(string publishing);
	void setTitle(string title);
	void setAmount(unsigned int amount);
	void setAuthor(string author);
	void decreaseBook(unsigned int amount); // �����������
	void init(string title, string author, string publishing, double price, unsigned int amount); // ��ʼ��|������ĳ�Ա
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
	unsigned int amount; // ����
	double price; // �۸�
	string publishing; // ������
	string title; // ����
	string author; // ����
	//bool _isInit;
};

std::ostream& operator<< (std::ostream& out, Book& book);
#endif