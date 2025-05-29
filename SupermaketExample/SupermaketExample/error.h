#pragma once
#include <string>

using namespace std;

class Error {
public:
	Error();
	Error(string message);
	string message;
private:
	const string defaultMessage = "标准错误";
};

class StrIsEmpty : public Error {
public:
	StrIsEmpty();
	StrIsEmpty(string message);
private:
	const string defaultMessage = "标准错误";
};

class NumExceedLimit : public Error {
public:
	NumExceedLimit();
	NumExceedLimit(string message);
private:
	const string defaultMessage = "超过数据范围";
};

class EleNoExist : public Error {
public:
	EleNoExist();
	EleNoExist(string message);
private:
	const string defaultMessage = "想要的元素不存在";
};

class PropertyRepeat : public Error {
public:
	PropertyRepeat();
	PropertyRepeat(string message);
private:
	const string defaultMessage = "指定的属性中有重复值发生";
};

class DataFormat : public Error {
public:
	DataFormat();
	DataFormat(string message);
private:
	const string defaultMessage = "数据格式错误";
};
