#include <iostream>
#include <string>
#include "manager.h"
#include "layfolk.h"

using namespace std;

extern AdminGroup<Admin*> adminGroup;
extern CustomerGroup<Buyer*> customerGroup;
extern BookShelf<Book*> bookShelf;

Admin* Manager::loginedAdmin = NULL;
Buyer* Manager::loginedBuyer = NULL;

void Manager::showMenu() {
	cout << "========���ܲ˵�========" << endl;
	cout << "-1: �˳�" << endl;
	cout << "1: ����Ա��½" << endl;
	cout << "2: �˿͵�¼" << endl;
	cout << "3: ����Աע��" << endl;
	cout << "4: �˿�ע��" << endl;
	cout << endl;
}
// login��adminLogin���߼�������, ������Щ΢��ͬ, ֻ���������ƺ���, �Ͳ�ʹ�ú���ģ����
bool Manager::adminLogin() {
	string account;
	string password;
	Admin* pAdmin = NULL;

	cout << "�������˺�: ";
	cin >> account;
	cout << endl;
	cout << "����������: ";
	cin >> password;
	cout << endl;

	// �ڹ���Ա�������ҵ�ָ���˺ŵĹ���Ա
	pAdmin = adminGroup.getEleByAccount(account);
	if (pAdmin == NULL) {
		cout << "�˺Ų�����" << endl;
	}
	else {
		// ������ȷ
		if (pAdmin->passwordVaild(password)) {
			cout << "��¼�ɹ�" << endl;
			// ���õ�ǰ��¼��Ա
			Manager::loginedAdmin = pAdmin;
			Manager::loginedBuyer = NULL;
			return true;
		}
		else {
			cout << "�������" << endl;
		}
	}
	return false;
}
bool Manager::login() {
	string account;
	string password;
	Buyer* pBuyer = NULL;

	cout << "�������˺�: ";
	cin >> account;
	cout << endl;
	cout << "����������: ";
	cin >> password;
	cout << endl;

	pBuyer = customerGroup.getEleByAccount(account);
	if (pBuyer == NULL) {
		cout << "�˺Ų�����" << endl;
	}
	else {
		if (pBuyer->passwordVaild(password)) {
			cout << "��¼�ɹ�" << endl;
			// ����֮ǰд����, ��loginedBuyer��Ϊ��ָ��, ��ȻҲ���ܹ����õ�loginedBuyer�ĳ�Ա����
			Manager::loginedBuyer = pBuyer;
			Manager::loginedAdmin = NULL;
			return true;
		}
		else {
			cout << "�������" << endl;
		}
	}
	return false;
}
void Manager::signIn() {
	string account;
	string password;
	string confirmPassword;
	string address;
	string name;
	Buyer* pBuyer = NULL;

	cout << "�������˺�: ";
	cin >> account;
	cout << endl;
	cout << "����������: ";
	cin >> password;
	cout << endl;
	cout << "��ȷ������ ";
	cin >> confirmPassword;
	cout << endl;
	cout << "�������ַ: ";
	cin >> address;
	cout << endl;
	cout << "����������: ";
	cin >> name;
	cout << endl;

	if (password.compare(confirmPassword)) {
		cout << "�������벻һ��" << endl;
		return;
	}
	else {
		try {
			pBuyer = new LayFolk(name, account, password, address, customerGroup, 0);
			customerGroup.push(pBuyer);
			cout << "ע��ɹ�" << endl;
		}
		catch (int i) { ; }
	}
}
void Manager::signInAdmin() {
	string account;
	string password;
	string confirmPassword;
	string name;
	Admin* pAdmin = NULL;

	cout << "�������˺�: ";
	cin >> account;
	cout << endl;
	cout << "����������: ";
	cin >> password;
	cout << endl;
	cout << "��ȷ������ ";
	cin >> confirmPassword;
	cout << endl;
	cout << "����������: ";
	cin >> name;
	cout << endl;

	if (password.compare(confirmPassword)) {
		cout << "�������벻һ��" << endl;
		return;
	}
	else {
		try {
			pAdmin = new Admin(name, account, password, adminGroup);
			adminGroup.push(pAdmin);
			cout << "ע��ɹ�" << endl;
		}
		catch (int i) { ;  }
	}
}
void Manager::runBase() {
	int choice = -1;
	do {
		system("cls");

		Manager::showMenu();

		cout << endl;
		cout << "�����빦��ѡ��(-1��ʾ�˳�):";
		cin >> choice;
		cin.clear();
		cin.ignore(1000, '\n');
		system("cls");
		cout << endl;

		switch (choice) {
			case -1: break;
			case 1: 
				if (adminLogin()) {
					Manager::runAdminFunc();
				}
				break;
			case 2:
				if (login()) {
					Manager::runBuyerFunc();
				}
				break;
			case 3:
				signInAdmin();
				break;
			case 4:
				signIn();
				break;
			default:
				cout << "��������ȷѡ��: " << endl;
				break;
		}

		if (choice != -1) {
			system("pause");
		}
	} while (choice != -1);
}
void Manager::showCurPerson() {
	if (Manager::loginedAdmin != NULL) {
		Manager::loginedAdmin->display();
	}
	else if (Manager::loginedBuyer != NULL) {
		Manager::loginedBuyer->display();
	}
}
void Manager::runAdminFunc() {
	int choice = -1;
	unsigned int id;
	string title;

	do {
		system("cls");
		Manager::showAdminMenu();

		cout << endl;
		cout << "�����빦��ѡ��(-1��ʾ�˳�): ";
		cin >> choice;
		cin.clear();
		cin.ignore(1000, '\n');
		system("cls");
		cout << endl;

		switch (choice) {
		case -1: 
			// �����ϲ�, ע����¼�Ĺ���Ա
			Manager::loginedAdmin = NULL;
			break;
		case 1:
			Manager::loginedAdmin->addBook(bookShelf);
			break;
		case 2:
			cout << "�������鱾id: ";
			cin >> id;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl;
			// ���ﲻӦ��ʹ�÷���boolֵ�ķ�ʽ,�жϺ����Ƿ�ִ�гɹ�. ���ʹ���׳�����ķ�ʽ
			Manager::loginedAdmin->removeBook(bookShelf, id) ?
				cout << "ɾ���ɹ�" << endl : cout << "idΪ" << id << "���鲻����" << endl;
 			break;
		case 3:
			cout << "�������鱾����: ";
			cin >> title;
			cout << endl;
			Manager::loginedAdmin->removeBook(bookShelf, title) ?
				cout << "ɾ���ɹ�" << endl : cout << "����Ϊ" << title << "���鲻����" << endl;
			title = "";
			break;
		case 4:
			cout << "�������鱾id: ";
			cin >> id;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl;
			Manager::loginedAdmin->setBook(bookShelf, id);
			break;
		case 5:
			cout << "�������鱾����: ";
			cin >> title;
			cout << endl;
			Manager::loginedAdmin->setBook(bookShelf, title);
			break;
		case 6:
			showCurPerson();
			break;
		case 7:
			bookShelf.display();
			break;
		default:
			cout << "��������ȷѡ��: " << endl;
			break;
		}
		
		if (choice != -1) {
			system("pause");
		}
	} while (choice != -1);
}
void Manager::showAdminMenu() {
	cout << "========����Ա�����б�========" << endl;
	cout << "-1: �ص���һ��" << endl;
	cout << "1: �����鼮" << endl;
	cout << "2: ͨ��idɾ���鼮" << endl;
	cout << "3: ͨ������ɾ���鼮" << endl;
	cout << "4: ͨ��id�޸��鼮��Ϣ" << endl;
	cout << "5: ͨ�������޸��鼮��Ϣ" << endl;
	cout << "6: ��ʾ��ǰ��¼����Ա��Ϣ" << endl;
	cout << "7: ��ʾ�����鼮" << endl;
	cout << endl;
}
void Manager::runBuyerFunc() {
	int choice = -1;
	unsigned int amount;
	unsigned int id;
	unsigned int money;
	string title;

	do {
		system("cls");
		Manager::showBuyerMenu();

		cout << endl;
		cout << "�����빦��ѡ��(-1��ʾ�˳�):";
		cin >> choice;
		// ����cin״̬���
		cin.clear();
		// ��ձ�׼�������е��ַ�
		cin.ignore(1000, '\n');
		// �������������
		system("cls");
		cout << endl;

		switch (choice) {
		case -1: 
			Manager::loginedBuyer = NULL;
			break;
		case 1:
			bookShelf.display();
			break;
		case 2:
			cout << "�������鱾id: ";
			cin >> id;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl;

			cout << "�����빺������: ";
			cin >> amount;
			cin.clear();
			cin.ignore(1000, '\n');
			Manager::loginedBuyer->buyBookById(id, amount, bookShelf);
			break;
		case 3:
			cout << "�������鱾id: ";
			cin >> id;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl;

			cout << "������ɾ������: ";
			cin >> amount;
			cin.clear();
			cin.ignore(1000, '\n');
			Manager::loginedBuyer->removeBookById(id, amount);
			break;
		case 4:
			cout << "�������鱾id: ";
			cin >> id;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl;

			cout << "������������: ";
			cin >> amount;
			cin.clear();
			cin.ignore(1000, '\n');
			Manager::loginedBuyer->setBookById(id, amount, bookShelf);
			break;
		case 5:
			cout << "����������: ";
			cin >> title;
			cout << endl;
			cout << "�����빺������: ";
			cin >> amount;
			cin.clear();
			cin.ignore(1000, '\n');
			Manager::loginedBuyer->buyBookByTitle(title, amount, bookShelf);
			break;
		case 6:
			cout << "����������: ";
			cin >> title;
			cout << endl;
			cout << "������ɾ������: ";
			cin >> amount;
			cin.clear();
			cin.ignore(1000, '\n');
			Manager::loginedBuyer->removeBookByTitle(title, amount);
			break;
		case 7:
			cout << "����������: ";
			cin >> title;
			cout << endl;
			cout << "������������: ";
			cin >> amount;
			cin.clear();
			cin.ignore(1000, '\n');
			Manager::loginedBuyer->setBookByTitle(title, amount, bookShelf);
			break;
		case 8:
			Manager::loginedBuyer->showOrder();
			break;
		case 9:
			Manager::loginedBuyer->showMoney();
			break;
		case 10:
			cout << "�������ֵ���: " << endl;
			cin >> money;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl;
			Manager::loginedBuyer->recharge(money);
			break;
		case 11:
			Manager::loginedBuyer->resetOrder();
			break;
		case 12:
			Manager::loginedBuyer->pay(bookShelf);
			break;
		case 13:
			Manager::loginedBuyer->display();
			break;
		default:
			cout << "��������ȷѡ��: " << endl;
			break;
		}

		if (choice != -1) {
			system("pause");
		}
	} while (choice != -1);
}
void Manager::showBuyerMenu() {
	cout << "========�����߹��ܲ˵�========" << endl;
	cout << "-1: �˻���һ��" << endl;
	cout << "1: �鿴�����鼮" << endl;
	cout << "2: ͨ��id< ���� >ָ���������鼮" << endl;
	cout << "3: ͨ��id< ɾ�� >�����е��鼮����" << endl;
	cout << "4: ͨ��id< �޸� >�����е��鼮����(�����в�����ʱ, ��������鼮������)" << endl;
	cout << "5: ͨ������< ���� >ָ���������鼮" << endl;
	cout << "6: ͨ������< ɾ�� >�����е��鼮����" << endl;
	cout << "7: ͨ������< �޸� >�����е��鼮����(�����в�����ʱ, ��������鼮������)" << endl;
	cout << "8: �鿴����" << endl;
	cout << "9: �鿴���" << endl;
	cout << "10: ��ֵ���" << endl;
	cout << "11: ��չ����嵥" << endl;
	cout << "12: ����" << endl;
	cout << "13: ��ʾ������Ϣ" << endl;
	cout << endl;
}

