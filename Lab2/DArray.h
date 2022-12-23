#pragma once
#include <iostream>

using namespace std;

template<typename T>
class DArray final {
public://вроде говорилось на лекции что сначала стоит писать публичные, потом приватные
	class Iterator {
		T* cur;
		T* first;
		DArray<T>* arr;
		bool isReversed;
	public:
		Iterator(T* first1, DArray<T>* input, bool isReversed) {
			cur = first = first1;
			arr = input;
			this->isReversed = isReversed;
		}

		const T& get() const { return *cur; };
		void set(const T& value) { *cur = value; };

		void next() {
			if (!isReversed) cur += 1;
			else cur -= 1;
		};

		bool hasNext() const {
			if (!isReversed) {
				if (cur == arr->size_ + first) return false;
				return true;
			}
			else {
				if (cur == first - arr->size_) return false;
				return true;
			}
		};
	};
	Iterator iterator() { return Iterator(_data, this, false); };
	Iterator reverseIterator() { return Iterator(_data + size_ - 1, this, true); };
	DArray();
	DArray(DArray& other);
	DArray(DArray&& other) noexcept;
	DArray(int capacity);
	~DArray();

	int insert(const T& value);
	int insert(int index, const T& value);

	void remove(int index);
	void swap(DArray& other);

	const T& operator[](int index) const;
	T& operator[](int index);
	DArray<T>& operator=(DArray other);
	//DArray<T>& operator=(DArray& other);
	DArray<T>& operator=(DArray&& other) noexcept;
	int size() const;
	int capacity() const;
private:
	T* _data;
	size_t size_;
	size_t _capacity;
	const size_t defaultSize_ = 8;
	void plusMemory();
};

//Конструктор по умолчанию
template<typename T> DArray<T>::DArray() {
	_capacity = defaultSize_;
	size_ = 0;
	_data = (T*)malloc(sizeof(T) * _capacity);
}

//Конструктор с параметрами
template<typename T> DArray<T>::DArray(int capacity) {
	_capacity = capacity;
	size_ = 0;
	_data = (T*)malloc(sizeof(T) * _capacity);
}

//Деструктор
template<typename T> DArray<T>::~DArray() {
	for (int i = 0; i < size_; i++)  _data[i].~T();
	free(_data);
}

//Конструктор присваивания
template<typename T> DArray<T>::DArray(DArray& other) {
	size_ = other.size_;
	_capacity = other._capacity;
	_data = (T*)malloc(sizeof(T) * _capacity);
	for (size_t i = 0; i < other.size_; ++i) new (_data + i) T(other._data[i]); // размещающий new чтобы вызвать копирующий конструктор

}

//Перемещающий конструктор
template<typename T> DArray<T>::DArray(DArray&& other) noexcept {
	if (this != &other) {
		_data = other._data;
		size_ = other.size_;
		_capacity = other._capacity;
		other._data = nullptr;
		other.size_ = 0;
		other._capacity = 0;
	}
}

//Оператор присваивания(Without Copy-Swap)
//template<typename T> DArray<T>& DArray<T>::operator=(DArray& other) {
//	for (int i = 0; i < size_; i++) _data[i].~T();
//	free(_data);
//	size_ = other.size_;
//	_capacity = other._capacity;
//	_data = (T*)malloc(sizeof(T) * _capacity);
//	for (int i = 0; i < other.size_; ++i) new (_data + i) T(other._data[i]);
//
//	return *this;
//}
 
//Оператор присваивания
template<typename T> DArray<T>& DArray<T>::operator=(DArray other) {
	swap(other);
	return *this;
}

//Оператор перемещения 
template<typename T> DArray<T>& DArray<T>::operator=(DArray&& other) noexcept {
	if (this != &other) { //Защищаемся от присваивания самому себе
		for (int i = 0; i < size_; i++) _data[i].~T();
		free(_data);
		_data = other._data;
		size_ = other.size_;
		_capacity = other._capacity;
		other._data = nullptr;
		other.size_ = 0;
		other._capacity = 0;
	}
	return *this;
}

template<typename T> void DArray<T>::plusMemory() {
	_capacity *= 2;
	T* new__data = (T*)malloc(_capacity * sizeof(T));

	for (int i = 0; i < size_; i++) new (new__data + i) T(move(_data[i]));
	for (int i = 0; i < size_; i++) _data[i].~T();
	free(_data);
	_data = new__data;
	new__data = nullptr;
}

template<typename T> int DArray<T>::insert(const T& value) {
	if (size_ == _capacity) plusMemory();

	new (_data + size_) T(value);
	size_++;
	return size_ - 1;
}

//Вставить элемент по определенному индексу
template<typename T> int DArray<T>::insert(int index, const T& value) {

	if (index < 0 || index >= size_) return -1;
	if (size_ == _capacity)  plusMemory();
	size_++;
	for (int i = size_ - 1; i > index; i--) {
		new (_data + i) T(move(_data[i - 1]));
		_data[i - 1].~T();//освобождаем память для перенесенного элемента
	}
	new (_data + index) T(value);
	return index;
}

template<typename T> void DArray<T>::remove(int index) {
	if (index < 0 || index >= size_) throw "Empty container\n";
	_data[index].~T();
	for (int i = index; i < size_ - 1; i++) {
		_data[i].~T();
		new (_data + i) T(move(_data[i + 1]));
	}
	size_--;
}

template<typename T> void DArray<T>::swap(DArray& other){
	swap(_data, other._data);
	swap(size_, other.size_);
	swap(_capacity, other._capacity);
}

//Оператор возвращающий константную ссылку на элемент
template<typename T> const T& DArray<T>::operator[](int index) const {
	if (index < 0 || index >= size_) throw "Invalid index\n";
	return *(_data + index);
}
template<typename T> T& DArray<T>::operator[](int index)
{
	if (index < 0 || index >= size_) throw "Invalid index\n";
	return *(_data + index);
}
template<typename T> int DArray<T>::size() const { return size_; }
template<typename T> int DArray<T>::capacity() const { return _capacity; }

