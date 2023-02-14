#include <cassert>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

struct data_t {
	string group;
};

class Vector {
private:
	int size{ 0 };
	data_t* array{ nullptr };
public:
	Vector() {}
	~Vector() { delete[] array; }
	void init(size_t n) {
		array = new data_t[n];
		size = n;
	}
	void input() {
		for (int i = 0; i < size; i++) cin >> array[i].group;
	}
	void output() {
		for (int i = 0; i < size; i++) cout << array[i].group << ' ';
	}
	data_t find(string word) {
		for (int i = 0; i < size; i++) if (array[i].group == word) return array[i];
		return data_t();
	}
	void edit(size_t n, string word) {
		array[n].group = word;
	}
	int getSize() { return size; }

	void push_back(const data_t val) {
		data_t* tmpArr = new data_t[++size];
		for (int i = 0; i < size - 1; i++) tmpArr[i] = array[i];
		tmpArr[size - 1] = val;
		array = tmpArr;
	}
	void pop_back() {
		data_t* tmpArr = new data_t[--size];
		for (int i = 0; i < size; i++) tmpArr[i] = array[i];
		array = tmpArr;
	}
	void remove(size_t pos) {
		data_t* tmpArr = new data_t[--size];
		for (int i = 0; i < pos; i++) tmpArr[i] = array[i];
		for (int i = pos; i < size; i++) tmpArr[i] = array[i + 1];
		array = tmpArr;
	}
	void insert(size_t pos, const data_t val) {
		data_t* tmpArr = new data_t[++size];
		for (int i = 0; i < pos; i++) tmpArr[i] = array[i];
		tmpArr[pos] = val;
		for (int i = pos + 1; i < size; i++) tmpArr[i] = array[i - 1];

		array = tmpArr;
	}
};

int main(int argc, char const* argv[])
{
	Vector v1;
	string search_term, edit_term;
	size_t index = 0, count = 0;

	cin >> search_term >> edit_term >> count >> index;

	v1.init(count);
	v1.push_back({ "one" });
	v1.push_back({ "two" });
	v1.push_back({ "three" });
	assert(3 == v1.getSize());
	v1.insert(index, { edit_term });
	assert(edit_term == v1.find(search_term).group);
	v1.remove(index);
	v1.pop_back();
	assert(2 == v1.getSize());
	v1.output();
}
