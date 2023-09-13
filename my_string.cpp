#include "my_string.h"

MyString::MyString() : m_size(0), m_capacity(0), m_array(nullptr) {}

MyString::MyString(const char* array, size_t count) {
	m_size = count;
	m_capacity = m_size + 1;
	m_array = new char[m_capacity];
	memcpy(m_array, array, m_size);
	m_array[m_size] = 0;
}

MyString::MyString(const char* array) : MyString(array, strlen(array)) {}

MyString::MyString(initializer_list<char> array) : MyString(array.begin(), array.size()) {}

MyString::MyString(string array) : MyString(array.c_str()) {}

MyString::MyString(size_t count, char symbol) {
	m_size = count;
	m_capacity = m_size + 1;
	m_array = new char[m_capacity];
	for (size_t i = 0; i < m_size; ++i)
		m_array[i] = symbol;
	m_array[m_size] = 0;
}

MyString::MyString(const MyString& object) : MyString(object.m_array, object.m_size) {}

MyString::MyString(MyString&& o) noexcept : m_size(o.m_size), m_capacity(o.m_capacity) {
	m_array = new char[m_capacity];
	memcpy(m_array, o.m_array, m_size);
	m_array[m_size] = 0;
}


MyString::~MyString() {
	if (m_array != nullptr)
		delete[] m_array;
}
size_t MyString::size()  const {
	return m_size;
}
size_t MyString::length()  const {
	return m_size;
}
size_t MyString::capacity() const {
	return m_capacity;
}
char* MyString::c_str() const {
	return m_array;
}
const char* MyString::data() const {
	return m_array;
}
void MyString::clear() {
	if (m_capacity > 0)
		m_array[0] = 0;
	m_size = 0;
}

void MyString::extend(size_t count) {
	size_t taget_size = m_size + count + 1;
	if (m_capacity < taget_size) {
		if (m_capacity <= 0) {
			m_capacity = taget_size;
		}
		while (m_capacity < taget_size)
			m_capacity *= 2;

		char* array2 = new char[m_capacity];
		if (m_array != nullptr) {
			memcpy(array2, m_array, m_size);
			delete[] m_array;
		}
		m_array = array2;
	}
}
void MyString::append(const char* string, size_t index, size_t count) {
	extend(count);
	memcpy(m_array + m_size, string + index, count);
	m_size += count;
	m_array[m_size] = 0;
}
void MyString::append(const char* string) {
	append(string, 0, strlen(string));
}
void MyString::append(const string array) {
	append(array.c_str(), 0, array.size());
}
void MyString::append(const string array, size_t index, size_t count) {
	append(array.c_str(), index, count);
}
void MyString::append(size_t count, char symbol) {
	auto str = MyString(count, symbol);
	append(str.c_str());
}

void MyString::insert(size_t index, const char* string, size_t count) {
	if (m_array == nullptr || index == m_size) {
		append(string, index, count);
		return;
	}
	extend(count);
	memcpy(m_array + index + count, m_array + index, m_size - index);
	memcpy(m_array + index, string, count);
	m_size += count;
	m_array[m_size] = 0;
}
void MyString::insert(size_t index, const string array, size_t count) {
	insert(index, array.c_str(), count);
}
void MyString::insert(size_t index, const char* string) {
	insert(index, string, strlen(string));
}
void MyString::insert(size_t index, const string array) {
	insert(index, array.c_str(), array.size());
}
void MyString::insert(size_t index, size_t count, char symbol) {
	auto str = MyString(count, symbol);
	insert(index, str.c_str(), count);
}
void MyString::replace(size_t index, size_t count, const char* string) {
	if (count != strlen(string)) {
		erase(index, count);
		insert(index, string);
	}
	else {
		memcpy(m_array + index, string, count);
	}
}
void MyString::replace(size_t index, size_t count, const string array) {
	replace(index, count, array.c_str());
}
void MyString::shrink_to_fit() {
	if (m_capacity == m_size + 1) return;
	m_capacity = m_size + 1;
	char* array2 = new char[m_capacity];
	memcpy(array2, m_array, m_size);
	array2[m_size] = 0;
	delete[] m_array;
	m_array = array2;
}

MyString MyString::substr(size_t index, size_t count) const {
	return MyString(m_array + index, count);
}
MyString MyString::substr(size_t index) const {
	return MyString(m_array + index);
}
bool MyString::empty() {

	return m_size == 0;
}

int MyString::find(const char* string, size_t index) const {
	size_t len = strlen(string);
	for (int i = index; i <= m_size - len; ++i) {
		int tmp = memcmp(m_array + i, string, len);
		if (tmp == 0)
			return i;
	}
	return -1;
}
int MyString::find(const char* string)const {
	return find(string, 0);
}
int MyString::find(string array) const {
	return find(array.c_str(), 0);
}
int MyString::find(string array, size_t index) const {
	return find(array.c_str(), index);
}
void MyString::erase(size_t index, size_t count) {
	memcpy(m_array + index, m_array + index + count, m_size - index - count);
	m_size -= count;
	m_array[m_size] = 0;
}
int MyString::lexic_compare(const MyString& right)const {
	if (m_size < right.size()) return 1;
	if (m_size > right.size()) return -1;
	return strcmp(m_array, right.c_str());
}

MyString& MyString::operator=(const MyString& right) {
	clear();
	append(right.m_array, 0, right.m_size);
	return *this;
}
MyString& MyString::operator=(const char* right) {
	return *this = MyString(right);
}
MyString& MyString::operator=(const string right) {
	return *this = MyString(right);
}
MyString& MyString::operator=(const char right) {
	return *this = MyString(&right);
}

std::ostream& operator<<(std::ostream& s, const MyString& str) {
	if (str.m_array == nullptr) {
		return s << "";
	}
	return s << str.m_array;
}

MyString operator+ (const MyString& left, const MyString& right) {
	MyString sum = left;
	sum += right;
	return sum;
}
MyString operator+(const MyString& left, const char* right) {
	return left + MyString(right);
}
MyString operator+(const MyString& left, const string right)
{
	return left + MyString(right);
}
MyString& MyString::operator += (const MyString& str) {
	auto s = MyString(str);
	append(s.c_str(), 0, s.size());
	return *this;
}
MyString& MyString::operator += (const char* s) {
	append(s);
	return *this;
}

MyString& MyString::operator+=(const string s) {
	append(s);
	return *this;
}
const char& MyString::operator [] (size_t i) const {
	return *(m_array + i);
}
std::istream& operator>> (std::istream& is, MyString& str) {
	char s[1];
	str.clear();
	do {
		char c = is.get();
		if (c == '\n' || c == ' ')
			break;
		s[0] = c;
		str.append(s, 0, 1);
	} while (true);
	return is;
}
bool operator == (const MyString& left, const MyString& right) {
	return left.lexic_compare(right) == 0;
}
bool operator!=(const MyString& left, const MyString& right) {
	return left.lexic_compare(right) != 0;
}
bool operator>(const MyString& left, const MyString& right) {
	return left.lexic_compare(right) == 1;
}
bool operator < (const MyString& left, const MyString& right) {
	return left.lexic_compare(right) == -1;
}
bool operator>=(const MyString& left, const MyString& right) {
	return left.lexic_compare(right) >= 0;
}
bool operator <= (const MyString& left, const MyString& right) {
	return left.lexic_compare(right) <= 0;
}