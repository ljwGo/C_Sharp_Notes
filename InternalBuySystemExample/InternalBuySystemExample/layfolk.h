#include "buyer.h"

class LayFolk : public Buyer {
public:
	LayFolk(string name,
		string account,
		string password,
		string address,
		CustomerGroup<Buyer*>& customerGroup,
		double money = 0);// layFolk类没有自己独有的属性, 故原封调用基类构造函数即可
	void setPayMoney(double orderPayMoney);
	void display();
};
