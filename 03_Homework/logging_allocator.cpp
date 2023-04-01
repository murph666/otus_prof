#ifndef __PRETTY_FUNCTION__
#include "pretty.h"
#endif

#include <iostream>
#include <map>
#include <vector>

#define USE_PRETTY 1

template <typename T>
struct logging_allocator {
	using value_type = T;

	using pointer = T *;
	using const_pointer = const T *;
	using reference = T &;
	

	template <typename U>
	struct rebind {
		using other = logging_allocator<U>;
	};

	logging_allocator() = default;
	~logging_allocator() = default;

	template <typename U>
	logging_allocator(const logging_allocator<U> &) {
	}

	T *allocate(std::size_t n) {
#ifndef USE_PRETTY
		std::cout << "allocate: [n = " << n << "]" << std::endl;
#else
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
		std::cout << "Allocating for " << typeid(T).name();
		std::cout << " " << n * sizeof(T) << " bytes\n";
#endif
		auto p = std::malloc(n * sizeof(T));
		std::cout << "Allocating on: " << p << std::endl;
		if (!p)
			throw std::bad_alloc();
		return reinterpret_cast<T *>(p);
	}

	void deallocate(T *p, std::size_t n) {
#ifndef USE_PRETTY
		std::cout << "deallocate: [n  = " << n << "] " << std::endl;
#else
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
		std::cout << p << std::endl;
		std::cout  << std::endl;
#endif
		std::free(p);
	}

	template <typename U, typename... Args>
	void construct(U *p, Args &&...args) {
#ifndef USE_PRETTY
		std::cout << "construct" << std::endl;
#else
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		std::cout << "Construct address:\t " << p << " size " << sizeof(U) << std::endl;
#endif
		new (p) U(std::forward<Args>(args)...);
	}

	template <typename U>
	void destroy(U *p) {
#ifndef USE_PRETTY
		std::cout << "destroy" << std::endl;
#else
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		std::cout << p << std::endl;
		std::cout << std::endl;
#endif
		p->~U();
	}
};

