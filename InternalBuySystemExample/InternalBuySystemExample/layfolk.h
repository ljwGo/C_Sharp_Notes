#include "buyer.h"

class LayFolk : public Buyer {
public:
	LayFolk(string name,
		string account,
		string password,
		string address,
		CustomerGroup<Buyer*>& customerGroup,
		double money = 0);// layFolk��û���Լ����е�����, ��ԭ����û��๹�캯������
	void setPayMoney(double orderPayMoney);
	void display();
};
