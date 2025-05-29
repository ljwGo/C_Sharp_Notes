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

	cout << "请输入要增加商品的类型: " << endl;
	cin >> choice;
	if (!cin.good()) {
		cin.clear();
		cin.ignore(1000, '\n');
	}

	switch (choice) {
	case 1:
		cout << "请输入商品名称" << endl;
		cin >> name;

		if (name == "") {
			throw new StrIsEmpty("名称不能为空字符串!!!");
		}

		// 查看原来是否有该商品
		if (newGood = dailyGoodsCon.getEle(name)) {
			cout << "请输入增加数量" << endl;
			cin >> more;
			if (!cin.good()) {
				cin.clear();
				cin.ignore(1000, '\n');
			}

			newGood->increase(more);
			cout << "成功增加!" << endl;
		}
		// 有原商品就添加数量
		else {
			cout << "请输入商品数量" << endl;
			cin >> quantity;
			if (!cin.good()) {
				cin.clear();
				cin.ignore(1000, '\n');
			}

			newGood = new DailyGoods(name, quantity);
			dailyGoodsCon.push(newGood);
			cout << "新建日用商品" << endl;
		}
		break;
	case 2:
		cout << "请输入商品名称" << endl;
		cin >> name;
		// 查看原来是否有该商品
		if (newGood = foodCon.getEle(name)) {
			cout << "请输入增加数量" << endl;
			cin >> more;
			if (!cin.good()) {
				cin.clear();
				cin.ignore(1000, '\n');
			}

			newGood->increase(more);
			cout << "成功增加!" << endl;
		}
		else {
			cout << "请输入商品数量" << endl;
			cin >> quantity;
			if (!cin.good()) {
				cin.clear();
				cin.ignore(1000, '\n');
			}
			cout << "请输入保质期年, 月, 日(如输入: 0 2 0)" << endl;
			cin >> year >> month >> day;
			if (!cin.good()) {
				cin.clear();
				cin.ignore(1000, '\n');
			}

			newGood = new Food(name, quantity, year, month, day);
			foodCon.push(newGood);
			cout << "新建食物" << endl;
		}
		break;
	case 3:
		cout << "请输入商品名称" << endl;
		cin >> name;
		// 查看原来是否有该商品
		if (newGood = EACon.getEle(name)) {
			cout << "请输入增加数量" << endl;
			cin >> more;
			if (!cin.good()) {
				cin.clear();
				cin.ignore(1000, '\n');
			}

			newGood->increase(more);
			cout << "成功增加!" << endl;
		}
		else {
			cout << "请输入商品数量" << endl;
			cin >> quantity;
			if (!cin.good()) {
				cin.clear();
				cin.ignore(1000, '\n');
			}
			cout << "请输入家具颜色" << endl;
			cin >> color;

			newGood = new ElectricalAppliance(name, quantity, color);
			EACon.push(newGood);
			cout << "新建家具商品" << endl;
		}
		break;
	default:
		// 可以通过错误抛异常, 将错误信息返回给view层, 但是一些提示信息不行; 
		// 就应该将录入数据的步骤, 交给view层;
		// 有空再重构吧
		throw new NumExceedLimit("不存在的选项");
	}
}
void Supermarket::showClassify() {
	cout << "可以增加的商品类别有:" << endl;
	cout << "1: 日常用品" << endl;
	cout << "2: 食物" << endl;
	cout << "3: 家具" << endl;
	cout << endl;
}
void Supermarket::sale() {
	
	Goods* newGood = NULL;
	string name;
	unsigned int quantity;

	cout << "请输入要出售的商品名称" << endl;
	cin >> name;
	
	// 无法使用短路运算, 只能这样做了; 在三个容器中找到对应名称的商品
	if (newGood = dailyGoodsCon.getEle(name));
	else if (newGood = foodCon.getEle(name));
	else if (newGood = EACon.getEle(name));
	else {
		throw new EleNoExist("商品名指定的商品不存在!!!");
	}

	cout << "请输入售卖的数量" << endl;
	cin >> quantity;
	if (!cin.good()) {
		cin.clear();
		cin.ignore(1000, '\n');
	}

	if (newGood->getQuantity() < quantity) {
		throw new NumExceedLimit("删除数量大于商品原有数量");
	}
	else {
		newGood->decrease(quantity);
		cout << "出售成功!!!" << endl;
	}
}
void Supermarket::search() {
	dailyGoodsCon.display("日常用品分区");
	foodCon.display("食物分区");
	EACon.display("家具分区");
}
