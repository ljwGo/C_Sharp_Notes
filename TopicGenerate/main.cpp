#include "AddenGenerate.h"
#include "MultiplierGenerate.h"
#include "SubtractorGenerate.h"
#include "DivisorGenerate.h"
#include "Paper.h"

/* �㷨�߼�:
	1.ȷ����Ŀ����. ��300��
	2.����һ����Ŀ�߼�.
		2.1 ����һ����Χ�ڵĳ�ʼ������. ��88, ���������
		2.2 �״����һ���������Ͳ�����. ��+�ź�10, ���źͲ������ֱ������
			2.2.1 �������һ������, ȷ��ʹ�üӷ�, ����, �˷����ǳ���.
			2.2.2 ����ܵõ��Ϸ��Ĳ�����, ����������ӷ�, ���Ǵ�ʱ��������100(���ֵ)
					��ô����ļ���ֻ����0. 0���������, ���Եû��������㷨, �������
			2.2.3 ֱ���ҵ�һ������ı��������ͷ���
					�������100��˵, �������100 - 10
		2.3 ��ĳ������, ����0.5. ���ɺ����Ĳ������ͷ���. �� 88 + 10 * 2
	3.������Ŀ
		�ֱ�������, �ʹ�
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