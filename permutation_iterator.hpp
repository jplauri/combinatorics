// permutation_iterator.hpp
//
// Generates all permutations of the {0,...n-1} element universe.
// The generation algorithm used is from the standard library.

#ifndef PERMUTATION_ITERATOR_HPP
#define PERMUTATION_ITERATOR_HPP

#include <cstdint>
#include <numeric>
#include <algorithm>
#include <type_traits>
#include <vector>
#include <cassert>

#include <boost/iterator/iterator_facade.hpp>

template <typename T>
class permutation_iterator
	: public boost::iterator_facade <
	permutation_iterator<T>,
	const std::vector<T>&,
	boost::forward_traversal_tag
	>
{
private:
	static_assert(std::is_integral<T>::value, "T must be integral");

public:
	permutation_iterator() : end_(true), perm_() { }

	explicit permutation_iterator(int n) : end_(false), perm_(n)
	{
		std::iota(perm_.begin(), perm_.end(), 0);
	}

private:
	friend class boost::iterator_core_access;

	void increment()
	{
		end_ = !std::next_permutation(perm_.begin(), perm_.end());
	}

	bool equal(const permutation_iterator& other) const
	{
		return end_ == other.end_;
	}

	const std::vector<T>& dereference() const
	{
		return perm_;
	}

	bool end_;
	std::vector<T> perm_;
};

#endif
