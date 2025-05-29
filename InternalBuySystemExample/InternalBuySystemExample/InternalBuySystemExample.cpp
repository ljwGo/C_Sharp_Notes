#include "container.h"
#include "bookShelf.h"
#include "adminGroup.h"
#include "customerGroup.h"
#include "admin.h"
#include "book.h"
#include "order.h"
#include "member.h"
#include "honoured_guest.h"
#include "layfolk.h"
#include "manager.h"
#include <iostream>

using namespace std;

// 容器类, 用来存放和管理动态生成的对象
AdminGroup<Admin*> adminGroup;
CustomerGroup<Buyer*> customerGroup;
BookShelf<Book*> bookShelf;

int main() {
	Admin* pAdmin01 = new Admin("赖建威", "ljw123", "123456", adminGroup);
	Admin* pAdmin02 = new Admin("张三", "2333", "2333", adminGroup);
	Book *pBook01 = new Book("时光代理人", "未知", "b站", 150, 10);
	Book *pBook02 = new Book("罗小黑", "未知", "北京", 200, 2);
	Buyer* pBuyer01 = new Member("李四", "123456", "123456", "北京", customerGroup, 200, 2);
	Buyer* pBuyer02 = new Honoured_Guest("王五", "2333", "2333", "上海", customerGroup, 300);
	Buyer* pBuyer03 = new LayFolk("老六", "212121", "212121", "广州", customerGroup, 1000);
	
	adminGroup.push(pAdmin01);
	adminGroup.push(pAdmin02);
	bookShelf.push(pBook01);
	bookShelf.push(pBook02);
	customerGroup.push(pBuyer01);
	customerGroup.push(pBuyer02);
	customerGroup.push(pBuyer03);

	Manager::runBase();

	return 0;
}