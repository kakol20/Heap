#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>

// Heap sort using vector, second parameter determines if it to be sorted in descending order
template <class T, bool D>
class Heap {
public:
	Heap();
	Heap(const Heap<T, D>& copyHeap);
	~Heap() {};

	Heap<T, D>& operator=(const Heap<T, D>& copyHeap);

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
};

#endif // !HEAP_HPP

template<class T, bool D>
inline Heap<T, D>::Heap() {
}

template<class T, bool D>
inline Heap<T, D>::Heap(const Heap<T, D>& copyHeap) {
	m_heap = copyHeap.m_heap;
}

template<class T, bool D>
inline Heap<T, D>& Heap<T, D>::operator=(const Heap<T, D>& copyHeap) {
	if (this == &copyHeap) return *this;

	m_heap = copyHeap.m_heap;

	return *this;
}

template<class T, bool D>
inline void Heap<T, D>::Push(T item) {
	m_heap.push_back(item);

	SortUp(m_heap.size() - 1);
}

template<class T, bool D>
inline void Heap<T, D>::Pop() {
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

template<class T, bool D>
inline void Heap<T, D>::SortDown(const size_t i) {
	size_t parent = i;

	while (true) {
		size_t childL = (parent * 2) + 1;
		size_t childR = (parent * 2) + 2;

		size_t swapIndex = 0;

		if (childL < m_heap.size()) {
			swapIndex = childL;

			if (childR < m_heap.size()) {
				bool compareChildren = D ? m_heap[childL] < m_heap[childR] : m_heap[childL] > m_heap[childR];

				if (compareChildren) swapIndex = childR;
			}

			bool compareChild = D ? m_heap[parent] < m_heap[swapIndex] : m_heap[parent] > m_heap[swapIndex];

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

template<class T, bool D>
inline void Heap<T, D>::SortUp(const size_t i) {
	int child = (int)i;

	while (true) {
		int parent = (child - 1) / 2;

		if (parent < 0) break;

		bool compare = D ? m_heap[parent] < m_heap[child] : m_heap[parent] > m_heap[child];

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

template<class T, bool D>
inline T Heap<T, D>::Top() {
	return m_heap[0];
}
