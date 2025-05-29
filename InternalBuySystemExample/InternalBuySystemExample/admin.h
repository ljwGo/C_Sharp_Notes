#ifndef _ADMIN_H
#define _ADMIN_H
#include <string>
#include "book.h"
#include "bookShelf.h"
#include "adminGroup.h"
using namespace std;

// 现在admin类还不支持修改 账号 名称和密码等
class Admin {
public:
	//Admin(); // 无参构造函数
	Admin(string name, string account, string password, AdminGroup<Admin*>& adminGroup); // 有参构造函数
	void addBook(BookShelf<Book*>& bookShelf); // 添加新的书籍
	bool removeBook(BookShelf<Book*>& bookShelf, unsigned int id); // 根据id删除书籍
	bool removeBook(BookShelf<Book*>& bookShelf, string title); // 根据名称删除书籍
	void setBook(BookShelf<Book*>& bookShelf, unsigned int id); // 根据id删除书籍
	void setBook(BookShelf<Book*>& bookShelf, string title); // 根据名称设置书籍
	string getName() const;
	string getAccount() const;
	bool passwordVaild(string password) const; // 返回密码是否合法
	//bool hasInit();
	void display() const; // 显示管理员不敏感的信息
	friend std::ostream& operator << (std::ostream& out, Admin& admin);	
private:
	static unsigned int staticAdminId; // 自增静态编号成员
	string name; // 名字
	string account; // 账号
	string password; // 密码
	unsigned int id; // 编号
	//bool _isInit;
};

std::ostream& operator<< (std::ostream& out, Admin& admin);

#endif