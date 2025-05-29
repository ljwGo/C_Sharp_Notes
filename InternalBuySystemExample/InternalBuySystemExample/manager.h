#include "admin.h"
#include "buyer.h"
#include "bookShelf.h"
#include "customerGroup.h"
#include "adminGroup.h"

class Manager {
public:
	static void runBase(); // ���л�������
	static void showMenu(); // չʾ��������
	static bool adminLogin(); // ����Ա��¼
	static bool login(); // �˿͵�¼
	static void signInAdmin(); // ����Աע��
	static void signIn(); // �˿�ע��
	static void showCurPerson(); // չʾ��ǰ��¼��Ա��Ϣ

	static void showAdminMenu(); // չʾ����Ա����
	static void runAdminFunc(); // ����ֻ�й���Ա����ʹ�õĹ���

	static void showBuyerMenu(); // չʾ�û�������
	static void runBuyerFunc(); // չʾֻ���û�����ʹ�õĹ���
private:
	static Admin* loginedAdmin;
	static Buyer* loginedBuyer;
};
