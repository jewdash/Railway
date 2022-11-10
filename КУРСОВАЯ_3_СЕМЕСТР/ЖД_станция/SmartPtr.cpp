#include "SmartPtr.h"

template<class T>
SmartPointer<T>::SmartPointer(T* ptr) {
	if (!ptr)
		smartPtr = NULL;
	else {
		smartPtr = new Status<T>();
		smartPtr->ptr = ptr;
		smartPtr->counter = 1;
	}
}

template<class T>
SmartPointer<T>::~SmartPointer() {
	if (smartPtr) {
		smartPtr->counter--;
		if (smartPtr->counter == 0) {
			delete smartPtr->ptr;
			delete smartPtr;
		}
	}
}

template<class T>
SmartPointer<T>::SmartPointer(const SmartPointer& obj) : smartPtr(obj.smartPtr) {
	if (smartPtr) smartPtr->counter++;
}

template<class T>
void SmartPointer<T>::operator=(const SmartPointer& obj) {
	if (smartPtr) {
		smartPtr->counter--;
		if (smartPtr->counter == 0) {
			delete smartPtr->ptr;
			delete smartPtr;
		}
	}
	smartPtr = obj.smartPtr;
	if (smartPtr) smartPtr->counter++;
}

template<class T>
T* SmartPointer<T>::operator->() const {
	if (smartPtr) return smartPtr->ptr;
	else return NULL;
}

template<class T>
void SmartPointer<T>::showCounter() {
	cout << "Значение счетчика для объекта " << smartPtr << " равно: " << smartPtr->counter << endl;
}