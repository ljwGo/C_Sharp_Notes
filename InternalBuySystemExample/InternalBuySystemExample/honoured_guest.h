#include "buyer.h"

class Honoured_Guest: public Buyer{
public:
	Honoured_Guest(
		string name,
		string account, 
		string password, 
		string address, 
		CustomerGroup<Buyer*>& customerGroup, 
		double money=0, 
		double discount_rate=0.4); // 默认折扣为0.4, 应付金额为0
	void setPayMoney(double orderPayMoney);
	void display();
private:
	double discount_rate; // 折扣率
};