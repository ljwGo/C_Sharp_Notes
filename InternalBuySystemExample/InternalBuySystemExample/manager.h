#include "admin.h"
#include "buyer.h"
#include "bookShelf.h"
#include "customerGroup.h"
#include "adminGroup.h"

class Manager {
public:
	static void runBase(); // 运行基本功能
	static void showMenu(); // 展示基本功能
	static bool adminLogin(); // 管理员登录
	static bool login(); // 顾客登录
	static void signInAdmin(); // 管理员注册
	static void signIn(); // 顾客注册
	static void showCurPerson(); // 展示当前登录人员信息

	static void showAdminMenu(); // 展示管理员功能
	static void runAdminFunc(); // 运行只有管理员才能使用的功能

	static void showBuyerMenu(); // 展示用户共功能
	static void runBuyerFunc(); // 展示只有用户才能使用的功能
private:
	static Admin* loginedAdmin;
	static Buyer* loginedBuyer;
};
