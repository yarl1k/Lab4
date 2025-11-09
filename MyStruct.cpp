#include "MyStruct.h"
#include <thread>


using namespace std;

MyStruct::MyStruct(int m) : fields(m), mtx(m) {
	for (int i = 0; i < m; i++){
		fields[i] = 0;
	}
}

int MyStruct::get(int i) {
	scoped_lock lck(mtx[i]);
	return fields[i];
}

void MyStruct::set(int i, int value) {
	scoped_lock lck(mtx[i]);
	fields[i] = value;
}

string MyStruct::to_string() {
	if (fields.empty()) {
		return "";
	}
	scoped_lock lck(mtx[0], mtx[1], mtx[2]);
	ostringstream oss;
	oss << "Fields: ";
	for (int i = 0; i < fields.size(); i++) {
		if (i > 0) oss << ", ";
		oss << fields[i];
	}
	return oss.str();
}
