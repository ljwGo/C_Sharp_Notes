#include "error.h"

Error::Error() {
	message = Error::defaultMessage;
}
Error::Error(string message) {
	this->message = message;
}

StrIsEmpty::StrIsEmpty(){
	message = StrIsEmpty::defaultMessage;
}
StrIsEmpty::StrIsEmpty(string message) {
	this->message = message;
}

NumExceedLimit::NumExceedLimit() {
	message = NumExceedLimit::defaultMessage;
}
NumExceedLimit::NumExceedLimit(string message) {
	this->message = message;
}

EleNoExist::EleNoExist() {
	message = EleNoExist::defaultMessage;
}
EleNoExist::EleNoExist(string message) {
	this->message = message;
}

PropertyRepeat::PropertyRepeat() {
	message = PropertyRepeat::defaultMessage;
}
PropertyRepeat::PropertyRepeat(string message) {
	this->message = message;
}

DataFormat::DataFormat() {
	message = DataFormat::defaultMessage;
}
DataFormat::DataFormat(string message) {
	this->message = message;
}