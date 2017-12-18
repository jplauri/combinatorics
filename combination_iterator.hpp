// combination_iterator.hpp
//
// Produces all k-combinations of the universe {0,...,n-1} in
// lexicographical order. The algorithm is a tuned-up version
// of a simple generation method ("Algorithm T") described in:
//
//   Knuth, Donald E. 
//   The Art of Computer Programming, Volume 4A: Combinatorial Algorithms, Part 1. 
//   Pearson Education Inc., 2011.

#ifndef COMBINATION_ITERATOR_HPP
#define COMBINATION_ITERATOR_HPP

#include "common.hpp"
#include <boost/iterator/iterator_facade.hpp>

#include <vector>
#include <numeric>
#include <cassert>

template <typename T>
class combination_iterator
	: public boost::iterator_facade<
	combination_iterator<T>,
	const std::vector<T>&,
	boost::forward_traversal_tag
	>
{
public:
	combination_iterator() : end_(true), n_(0), t_(0), comb_() 
	{ 
		assert(end_);
	}

	explicit combination_iterator(index_t n, index_t k) : end_(false), n_(n), t_(k), comb_(k)
	{
		assert(k != 0 && n_ > k);
		std::iota(comb_.begin(), comb_.end(), 0);
		assert(!end_);
	}

private:
	friend class boost::iterator_core_access;

	void increment()
	{
		// Must be signed
		std::int64_t j = t_ - 1;

		for (const T end = n_ - t_; j >= 0 && comb_[j] >= end + j; --j) {}

		if (j < 0)
		{
			assert(comb_.front() == n_ - t_);
			end_ = true;
			return;
		}

		++comb_[j];

		for (const std::int64_t end = t_ - 1; j < end; ++j)
		{
			comb_[j + 1] = comb_[j] + 1;
		}

		return;
	}

	bool equal(const combination_iterator& other) const
	{
		return end_ == other.end_;
	}

	const std::vector<T>& dereference() const
	{
		return comb_;
	}

	bool end_;
	const index_t n_;
	const index_t t_;
	std::vector<T> comb_;
};

#endif
