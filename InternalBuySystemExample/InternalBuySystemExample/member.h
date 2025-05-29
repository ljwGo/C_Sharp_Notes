#include "buyer.h"

class Member : public Buyer {
public:
	Member(string name,
		string account,
		string password,
		string address,
		CustomerGroup<Buyer*>& customerGroup,
		double money = 0,
		unsigned int leaguer_grade = 1); // Ĭ��vip�ȼ�Ϊ1, Ӧ�����Ϊ0
	void setPayMoney(double orderPayMoney); // ��������Ӧ�ý����Ľ��(���ۺ��)
	void display(); // ��ʾ��������Ϣ
private:
	unsigned int leaguer_grade; // vip�ȼ�
};
