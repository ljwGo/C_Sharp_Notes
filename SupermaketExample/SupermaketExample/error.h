#pragma once
#include <string>

using namespace std;

class Error {
public:
	Error();
	Error(string message);
	string message;
private:
	const string defaultMessage = "��׼����";
};

class StrIsEmpty : public Error {
public:
	StrIsEmpty();
	StrIsEmpty(string message);
private:
	const string defaultMessage = "��׼����";
};

class NumExceedLimit : public Error {
public:
	NumExceedLimit();
	NumExceedLimit(string message);
private:
	const string defaultMessage = "�������ݷ�Χ";
};

class EleNoExist : public Error {
public:
	EleNoExist();
	EleNoExist(string message);
private:
	const string defaultMessage = "��Ҫ��Ԫ�ز�����";
};

class PropertyRepeat : public Error {
public:
	PropertyRepeat();
	PropertyRepeat(string message);
private:
	const string defaultMessage = "ָ�������������ظ�ֵ����";
};

class DataFormat : public Error {
public:
	DataFormat();
	DataFormat(string message);
private:
	const string defaultMessage = "���ݸ�ʽ����";
};
