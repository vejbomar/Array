
// Author: Martin Vejbora

#include <stdlib.h>
#include <utility>
#include <new>


template <class T>
class Array
{
private:

	// pointer to memory where are stored items or nullptr
	T* items;
	size_t capacity;
	size_t count;

	// Makes sure that n more items can be stored in Array
	// Allocates more memory if needed
	// Can throw bad_alloc exception if problem occurs with memory allocation
	void ensureCapacity(size_t n)
	{
		T* newItems;
		// there is enough space
		if (capacity - count >= n) return;

		// allocate double capacity if that is enough
		if (capacity * 2 - count >= n)
		{
			capacity *= 2;
			newItems = (T*)malloc(sizeof(T) * capacity);
		}
		// allocate memory to store exactly current items plus new n items
		else
		{
			capacity += n;
			newItems = (T*)malloc(sizeof(T) * capacity);
		}

		if (newItems == nullptr) throw std::bad_alloc();

		move(items, newItems, count);
		freeItems(items, 0, count);
		free(items);
		items = newItems;
	}

	// Move items from old memory to new one
	// used for reallocation
	void move(T* oldPtr, T* newPtr, size_t count)
	{
		for (size_t i = 0; i < count; ++i)
		{
			newPtr[i] = std::move(oldPtr[i]);
		}
	}

	// Call destructors on items
	void freeItems(T* items, size_t pos, size_t count)
	{
		for (T* i = items + pos; i < items + pos + count; ++i)
		{
			i->~T();
		}
	}

public:
	// Default constructor
	Array()
	{
		count = 0;
		capacity = 0;
		items = nullptr;
	}

	// Copy constructor
	Array(const Array& x)
	{
		count = x.count;
		ensureCapacity(count);
		for (size_t i = 0; i < count; ++i)
		{
			items[i] = x[i];
		}
	}

	// Move constructor
	Array(Array&& x)
	{
		count = x.count;
		capacity = x.capacity;
		items = x.items;

		x.count = 0;
		x.capacity = 0;
		x.items = nullptr;
	}

	// Copy assignment
	Array<T>& operator=(const Array<T>& x)
	{
		if (&x != this)
		{
			freeItems(items, 0, count);
			ensureCapacity(x.count);
			for (size_t i = 0; i < x.count; ++i)
			{
				items[i] = x[i];
			}
			count = x.count;
		}

		return *this;
	}

	// Move assignment
	Array<T>& operator=(Array<T>&& x)
	{
		if (&x != this)
		{
			freeItems(items, 0, count);
			free(items);
			count = x.count;
			capacity = x.capacity;
			items = x.items;

			x.count = 0;
			x.capacity = 0;
			x.items = nullptr;
		}

		return *this;
	}

	// Destructor
	~Array()
	{
		freeItems(items, 0, count);
		free(items);
	}

	bool empty() const
	{
		return count == 0;
	}

	void push_back(const T& val)
	{
		ensureCapacity(1);
		new(items + count) T();
		items[count] = val;
		++count;
	}

	void pop_back()
	{
		freeItems(items, count - 1, 1);
		--count;
	}

	T& back()
	{
		return items[count - 1];
	}

	const T& back() const
	{
		return items[count - 1];
	}

	T& front()
	{
		return *items;
	}

	const T& front() const
	{
		return *items;
	}

	void swap(Array<T>& other)
	{
		Array<T> tmp = Array<T>(std::move(*this));
		*this = std::move(other);
		other = std::move(tmp);
	}

	size_t size() const
	{
		return count;
	}

	void clear()
	{
		freeItems(items, 0, count);
		count = 0;
	}

	// Accessing items out of range [0, count - 1] is undefined behavior
	T& operator[](size_t index)
	{
		return items[index];
	}

	// Accessing items out of range [0, count - 1] is undefined behavior
	const T& operator[](size_t index) const
	{
		return items[index];
	}

	// Copy append
	void append(const Array<T>& other)
	{
		ensureCapacity(other.count);
		for (size_t i = 0; i < other.count; ++i)
		{
			items[count + i] = other[i];
		}
		count += other.count;
	}

	// Move append
	void append(Array<T>&& other)
	{
		ensureCapacity(other.count);
		for (size_t i = 0; i < other.count; ++i)
		{
			items[count + i] = std::move(other[i]);
		}
		count += other.count;
		other.count = 0;
	}

	void reserve(size_t n)
	{
		if (n > capacity) ensureCapacity(n - count);
	}

	void resize(size_t n)
	{
		// deleting items
		if (n < count)
		{
			freeItems(items, n, n - count);
			count = n;
		}
		// adding and initializing items
		if (n > count)
		{
			ensureCapacity(n - count);
			while (n > count) new(items + count++) T();
		}
	}

	class iterator
	{
		T* ptr;

	public:
		iterator(T* ptr) : ptr(ptr)
		{}

		// Pre-increment
		iterator& operator++()
		{
			++ptr;
			return *this;
		}

		// Post-increment
		iterator operator++ (int)
		{
			return ptr++;
		}

		bool operator==(const iterator& other) const
		{
			return ptr == other.ptr;
		}

		bool operator!=(const iterator& other) const
		{
			return ptr != other.ptr;
		}

		T& operator*()
		{
			return *ptr;
		}

		T* operator->()
		{
			return ptr;
		}
	};

	iterator begin() const
	{
		return iterator(items);
	}

	iterator end() const
	{
		return iterator(items + count);
	}
};