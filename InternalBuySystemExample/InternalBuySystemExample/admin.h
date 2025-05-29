#ifndef _ADMIN_H
#define _ADMIN_H
#include <string>
#include "book.h"
#include "bookShelf.h"
#include "adminGroup.h"
using namespace std;

// ����admin�໹��֧���޸� �˺� ���ƺ������
class Admin {
public:
	//Admin(); // �޲ι��캯��
	Admin(string name, string account, string password, AdminGroup<Admin*>& adminGroup); // �вι��캯��
	void addBook(BookShelf<Book*>& bookShelf); // ����µ��鼮
	bool removeBook(BookShelf<Book*>& bookShelf, unsigned int id); // ����idɾ���鼮
	bool removeBook(BookShelf<Book*>& bookShelf, string title); // ��������ɾ���鼮
	void setBook(BookShelf<Book*>& bookShelf, unsigned int id); // ����idɾ���鼮
	void setBook(BookShelf<Book*>& bookShelf, string title); // �������������鼮
	string getName() const;
	string getAccount() const;
	bool passwordVaild(string password) const; // ���������Ƿ�Ϸ�
	//bool hasInit();
	void display() const; // ��ʾ����Ա�����е���Ϣ
	friend std::ostream& operator << (std::ostream& out, Admin& admin);	
private:
	static unsigned int staticAdminId; // ������̬��ų�Ա
	string name; // ����
	string account; // �˺�
	string password; // ����
	unsigned int id; // ���
	//bool _isInit;
};

std::ostream& operator<< (std::ostream& out, Admin& admin);

#endif