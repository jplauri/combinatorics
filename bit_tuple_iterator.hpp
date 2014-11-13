// bit_tuple_iterator.hpp
//
// Generate all n-tuples where each element is drawn
// from the set {0,1}. The algorithm is based on 
// incrementing a binary counter. (Note the difference
// to e.g. Gray code).

#ifndef BIT_TUPLE_ITERATOR_HPP
#define BIT_TUPLE_ITERATOR_HPP

#include <cstdint>
#include <numeric>
#include <type_traits>
#include <cassert>

#include <boost/iterator/iterator_facade.hpp>

template <typename T>
class bit_tuple_iterator
	: public boost::iterator_facade <
	bit_tuple_iterator<T>,
	const T&,
	boost::forward_traversal_tag
	>
{
private:
	static_assert(std::is_integral<T>::value, "T must be integral");

public:
	bit_tuple_iterator() : end_(true), n_(0), p_(0) { }

	explicit bit_tuple_iterator(int p) : end_(false), n_(0), p_(std::pow(2, p) - 1)
	{
		assert(p_ == std::pow(2, p) - 1 && "T not large enough to hold 2^p");
		assert(p <= sizeof(T) * 8 && "T not large enough to hold n tuples");
		assert(n_ == 0);
	}

private:
	friend class boost::iterator_core_access;

	void increment()
	{
		if (p_ == n_)
		{
			end_ = true;
		}

		++n_;
	}

	bool equal(const bit_tuple_iterator& other) const
	{
		return end_ == other.end_;
	}

	const T& dereference() const
	{
		return n_;
	}

	bool end_;
	T n_;
	const T p_;
};

#endif
