#include "AddenGenerate.h"
#include "MultiplierGenerate.h"
#include "SubtractorGenerate.h"
#include "DivisorGenerate.h"
#include "Paper.h"

/* 算法逻辑:
	1.确定题目数量. 如300道
	2.生成一道题目逻辑.
		2.1 生成一个范围内的初始操作数. 如88, 该数入队列
		2.2 首次添加一个操作符和操作数. 如+号和10, 符号和操作数分别入队列
			2.2.1 随机生成一个索引, 确定使用加法, 减法, 乘法还是除法.
			2.2.2 如果能得到合法的操作数, 比如随机到加法, 但是此时被加数是100(最大值)
					那么满足的加数只能是0. 0是无意义的, 所以得换用其它算法, 比如减法
			2.2.3 直到找到一个合理的被操作数和符号
					对上面的100来说, 比如减法100 - 10
		2.3 以某个概率, 比如0.5. 生成后续的操作数和符号. 如 88 + 10 * 2
	3.构造题目
		分别是内容, 和答案
*/
int main(void) {

	AddenGenerate add;
	SubtractorGenerate sub;
	MultiplierGenerate multi;
	DivisorGenerate divi;

	std::vector<Operator*> operators{
		&add,
		&sub,
		&multi,
		&divi,
	};

	Paper paper(300, 1, 100 ,operators);

	paper.ShowPaper();

	return 0;
}