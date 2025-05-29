#include "supermarket.h"
#include <string>

unsigned int Supermarket::staticId = 1;

Supermarket::Supermarket() {
	id = Supermarket::staticId++;
}
void Supermarket::add() {
	showClassify();
	
	int choice;
	string name;
	string color;
	unsigned int more;
	unsigned int quantity;
	unsigned int year;
	unsigned int month;
	unsigned int day;
	Goods *newGood = NULL;

	cout << "������Ҫ������Ʒ������: " << endl;
	cin >> choice;
	if (!cin.good()) {
		cin.clear();
		cin.ignore(1000, '\n');
	}

	switch (choice) {
	case 1:
		cout << "��������Ʒ����" << endl;
		cin >> name;

		if (name == "") {
			throw new StrIsEmpty("���Ʋ���Ϊ���ַ���!!!");
		}

		// �鿴ԭ���Ƿ��и���Ʒ
		if (newGood = dailyGoodsCon.getEle(name)) {
			cout << "��������������" << endl;
			cin >> more;
			if (!cin.good()) {
				cin.clear();
				cin.ignore(1000, '\n');
			}

			newGood->increase(more);
			cout << "�ɹ�����!" << endl;
		}
		// ��ԭ��Ʒ���������
		else {
			cout << "��������Ʒ����" << endl;
			cin >> quantity;
			if (!cin.good()) {
				cin.clear();
				cin.ignore(1000, '\n');
			}

			newGood = new DailyGoods(name, quantity);
			dailyGoodsCon.push(newGood);
			cout << "�½�������Ʒ" << endl;
		}
		break;
	case 2:
		cout << "��������Ʒ����" << endl;
		cin >> name;
		// �鿴ԭ���Ƿ��и���Ʒ
		if (newGood = foodCon.getEle(name)) {
			cout << "��������������" << endl;
			cin >> more;
			if (!cin.good()) {
				cin.clear();
				cin.ignore(1000, '\n');
			}

			newGood->increase(more);
			cout << "�ɹ�����!" << endl;
		}
		else {
			cout << "��������Ʒ����" << endl;
			cin >> quantity;
			if (!cin.good()) {
				cin.clear();
				cin.ignore(1000, '\n');
			}
			cout << "�����뱣������, ��, ��(������: 0 2 0)" << endl;
			cin >> year >> month >> day;
			if (!cin.good()) {
				cin.clear();
				cin.ignore(1000, '\n');
			}

			newGood = new Food(name, quantity, year, month, day);
			foodCon.push(newGood);
			cout << "�½�ʳ��" << endl;
		}
		break;
	case 3:
		cout << "��������Ʒ����" << endl;
		cin >> name;
		// �鿴ԭ���Ƿ��и���Ʒ
		if (newGood = EACon.getEle(name)) {
			cout << "��������������" << endl;
			cin >> more;
			if (!cin.good()) {
				cin.clear();
				cin.ignore(1000, '\n');
			}

			newGood->increase(more);
			cout << "�ɹ�����!" << endl;
		}
		else {
			cout << "��������Ʒ����" << endl;
			cin >> quantity;
			if (!cin.good()) {
				cin.clear();
				cin.ignore(1000, '\n');
			}
			cout << "������Ҿ���ɫ" << endl;
			cin >> color;

			newGood = new ElectricalAppliance(name, quantity, color);
			EACon.push(newGood);
			cout << "�½��Ҿ���Ʒ" << endl;
		}
		break;
	default:
		// ����ͨ���������쳣, ��������Ϣ���ظ�view��, ����һЩ��ʾ��Ϣ����; 
		// ��Ӧ�ý�¼�����ݵĲ���, ����view��;
		// �п����ع���
		throw new NumExceedLimit("�����ڵ�ѡ��");
	}
}
void Supermarket::showClassify() {
	cout << "�������ӵ���Ʒ�����:" << endl;
	cout << "1: �ճ���Ʒ" << endl;
	cout << "2: ʳ��" << endl;
	cout << "3: �Ҿ�" << endl;
	cout << endl;
}
void Supermarket::sale() {
	
	Goods* newGood = NULL;
	string name;
	unsigned int quantity;

	cout << "������Ҫ���۵���Ʒ����" << endl;
	cin >> name;
	
	// �޷�ʹ�ö�·����, ֻ����������; �������������ҵ���Ӧ���Ƶ���Ʒ
	if (newGood = dailyGoodsCon.getEle(name));
	else if (newGood = foodCon.getEle(name));
	else if (newGood = EACon.getEle(name));
	else {
		throw new EleNoExist("��Ʒ��ָ������Ʒ������!!!");
	}

	cout << "����������������" << endl;
	cin >> quantity;
	if (!cin.good()) {
		cin.clear();
		cin.ignore(1000, '\n');
	}

	if (newGood->getQuantity() < quantity) {
		throw new NumExceedLimit("ɾ������������Ʒԭ������");
	}
	else {
		newGood->decrease(quantity);
		cout << "���۳ɹ�!!!" << endl;
	}
}
void Supermarket::search() {
	dailyGoodsCon.display("�ճ���Ʒ����");
	foodCon.display("ʳ�����");
	EACon.display("�Ҿ߷���");
}
