#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>

template <class T>
class Heap {
public:
	Heap(bool descending = false);
	Heap(const Heap<T>& copyHeap);
	~Heap() {};

	Heap<T>& operator=(const Heap<T>& copyHeap);

	/// <summary>
	/// Add to heap
	/// </summary>
	/// <param name="item"></param>
	void Push(T item);

	/// <summary>
	/// Removes top of heap
	/// </summary>
	void Pop();

	void SortDown(const size_t i);
	void SortUp(const size_t i);

	T Top();

private:
	std::vector<T> m_heap;
	bool m_descending;
};

#endif // !HEAP_HPP

template<class T>
inline Heap<T>::Heap(bool descending) {
	m_descending = descending;
}

template<class T>
inline Heap<T>::Heap(const Heap<T>& copyHeap) {
	m_heap = copyHeap.m_heap;
	m_descending = copyHeap.m_descending;
}

template<class T>
inline Heap<T>& Heap<T>::operator=(const Heap<T>& copyHeap) {
	if (this == &copyHeap) return *this;

	m_heap = copyHeap.m_heap;
	m_descending = copyHeap.m_descending;

	return *this;
}

template<class T>
inline void Heap<T>::Push(T item) {
	m_heap.push_back(item);

	SortUp(m_heap.size() - 1);
}

template<class T>
inline void Heap<T>::Pop() {
	if (m_heap.size() > 1) {
		T back = m_heap[m_heap.size() - 1];

		m_heap[m_heap.size() - 1] = m_heap[0];
		m_heap[0] = back;

		m_heap.pop_back();

		SortDown(0);
	}
	else {
		m_heap.pop_back();
	}
}

template<class T>
inline void Heap<T>::SortDown(const size_t i) {
	size_t parent = i;

	while (true) {
		size_t childL = (parent * 2) + 1;
		size_t childR = (parent * 2) + 1;

		size_t swapIndex = 0;

		if (childL < m_heap.size()) {
			swapIndex = childL;

			if (childR < m_heap.size()) {
				bool compareChildren = m_descending ? m_heap[childL] < m_heap[childR] : m_heap[childL] > m_heap[childR];

				if (compareChildren) swapIndex = childR;
			}

			bool compareChild = m_descending ? m_heap[parent] < m_heap[swapIndex] : m_heap[parent] > m_heap[swapIndex];

			if (compareChild) {
				T temp = m_heap[swapIndex];

				m_heap[swapIndex] = m_heap[parent];
				m_heap[parent] = temp;
			}

			parent = swapIndex;

			continue;
		}

		break;
	}
}

template<class T>
inline void Heap<T>::SortUp(const size_t i) {
	int child = (int)i;

	while (true) {
		int parent = (child - 1) / 2;

		if (parent < 0) break;

		bool compare = m_descending ? m_heap[parent] < m_heap[child] : m_heap[parent] > m_heap[child];

		if (compare) {
			T temp = m_heap[child];

			m_heap[child] = m_heap[parent];
			m_heap[parent] = temp;
		}
		else {
			break;
		}

		child = parent;
	}
}

template<class T>
inline T Heap<T>::Top() {
	return m_heap[0];
}
