// gray_code_iterator.hpp
//
// Produces all n-tuples of {0,1} in a minimal change ordering 
// (i.e. Gray code). In particular, two consecutive elements
// have Hamming distance equal to 1. The algorithm is a loopless
// generation method described in:
//
//   Bitner, James R., Gideon Ehrlich, and Edward M. Reingold. 
//   "Efficient generation of the binary reflected Gray code and its applications."
//   Communications of the ACM 19.9 (1976): 517-521.

#ifndef GRAY_CODE_ITERATOR_HPP
#define GRAY_CODE_ITERATOR_HPP

#include <cstdint>
#include <numeric>
#include <type_traits>

#include <boost/iterator/iterator_facade.hpp>

template <typename T>
class gray_code_iterator
	: public boost::iterator_facade <
	gray_code_iterator<T>,
	const T&,
	boost::forward_traversal_tag
	>
{
private:
	typedef std::uint_fast8_t focus_ptr_t;
	static_assert(std::is_integral<T>::value, "T must be integral");

public:
	gray_code_iterator() : end_(true), n_(0), a_(0), f_(0) { }

	explicit gray_code_iterator(int n) : end_(false), n_(n), a_(0), f_(new focus_ptr_t[n + 1])
	{
		assert(n <= sizeof(T) * 8 && "T not large enough to hold n tuples");

		std::iota(f_, f_ + n + 1, 0);

		assert(a_ == 0);
	}

	~gray_code_iterator()
	{
		if (f_)
		{
			delete[] f_;
		}
	}

private:
	friend class boost::iterator_core_access;

	void increment()
	{
		const focus_ptr_t j = f_[0];

		if (j == n_)
		{
			end_ = true;
			return;
		}

		f_[0] = 0;
		f_[j] = f_[j + 1];
		f_[j + 1] = j + 1;

		a_ ^= (1 << j);
	}

	bool equal(const gray_code_iterator& other) const
	{
		return end_ == other.end_;
	}

	const T& dereference() const
	{
		return a_;
	}

	bool end_;
	const int n_;
	T a_;
	focus_ptr_t* f_;
};

#endif
