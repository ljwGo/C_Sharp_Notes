#include "buyer.h"

class Member : public Buyer {
public:
	Member(string name,
		string account,
		string password,
		string address,
		CustomerGroup<Buyer*>& customerGroup,
		double money = 0,
		unsigned int leaguer_grade = 1); // 默认vip等级为1, 应付金额为0
	void setPayMoney(double orderPayMoney); // 设置最终应该交付的金额(打折后的)
	void display(); // 显示购买者信息
private:
	unsigned int leaguer_grade; // vip等级
};
