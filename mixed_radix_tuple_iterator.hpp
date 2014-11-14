// mixed_radix_tuple_iterator.hpp
//
// Generates all mixed radix n-tuples, where each digit has a user
// specified upper bound. The generation algorithm is straightforward.

#ifndef MIXED_RADIX_TUPLE_ITERATOR_HPP
#define MIXED_RADIX_TUPLE_ITERATOR_HPP

#include <cstdint>
#include <numeric>
#include <type_traits>
#include <vector>
#include <initializer_list>
#include <cassert>

#include <boost/iterator/iterator_facade.hpp>

template <typename T>
class mixed_radix_tuple_iterator
	: public boost::iterator_facade <
	mixed_radix_tuple_iterator<T>,
	const std::vector<T>&,
	boost::forward_traversal_tag
	>
{
private:
	static_assert(std::is_integral<T>::value, "T must be integral");

public:
	mixed_radix_tuple_iterator() : end_(true), size_(), t_() { }

	explicit mixed_radix_tuple_iterator(std::initializer_list<T> r) : end_(false), size_(r.size()), r_(r), t_(r.size())
	{
		for (auto e : r)
		{
			assert(e >= 0 && "elements must be non-negative");
		}

		assert(!end_);
	}

private:
	friend class boost::iterator_core_access;

	void increment()
	{
		if (t_.back() < r_.back())
		{
			++t_.back();
			return;
		}

		T j = size_ - 2;

		for(; j >= 0; --j)
		{
			t_[j + 1] = 0;

			if (t_[j] < r_[j])
				break;
		}

		if (j < 0)
		{
			end_ = true;
			return;
		}

		++t_[j];
	}

	bool equal(const mixed_radix_tuple_iterator& other) const
	{
		return end_ == other.end_;
	}

	const std::vector<T>& dereference() const
	{
		return t_;
	}

	bool end_;
	const int size_;
	const std::vector<T> r_;
	std::vector<T> t_;
};

#endif
