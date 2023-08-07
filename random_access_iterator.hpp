#pragma once
#include "utils.hpp"
#include <type_traits>
#include <cstddef>

namespace ft{
template<typename _Iterator>
  class random_access_iterator  : public iterator<random_access_iterator_tag, _Iterator>{

	public :
	typedef typename	ft::iterator_traits<_Iterator>::value_type		value_type;
	typedef typename	ft::iterator_traits<_Iterator>::difference_type	difference_type;
	typedef typename	ft::iterator_traits<_Iterator>::pointer			pointer;
	typedef typename	ft::iterator_traits<_Iterator>::reference			reference;
	
	private :
	pointer _current;

	public :

	random_access_iterator() : _current(nullptr) {}

	random_access_iterator(pointer p) : _current(p) {}

	random_access_iterator (const random_access_iterator &src) : _current(src.base()) {}

	~random_access_iterator() {}

	pointer base() const {return _current;}

	random_access_iterator	&operator=(const random_access_iterator &src)
	{
		if (this == &src)
			return *this;
		_current = src._current;
		return *this;
	}

	random_access_iterator &operator++()
	{
		_current++;
		return *this;
	}

	random_access_iterator operator++(int)
	{
		random_access_iterator tmp = *this;
		++_current;
		return (tmp);
	}

	random_access_iterator &operator--()
	{
		_current--;
		return *this;
	}

	random_access_iterator operator--(int)
	{
		random_access_iterator tmp = *this;
		--_current;
		return tmp;
	}

	reference operator[](difference_type n)
	{
		return _current[n];
	}

	random_access_iterator &operator+=(difference_type n)
	{
		_current += n;
		return *this;
	}

	random_access_iterator operator+(difference_type n) const
	{
		return _current + n;
	}

	random_access_iterator &operator-=(difference_type n)
	{
		_current -= n;
		return *this;
	}

	random_access_iterator operator-(difference_type n) const
	{
		return _current - n;
	}

	reference operator*() const 
	{
		return *_current;
	}

	pointer operator->() {return &(operator*());}

    operator random_access_iterator<value_type const *> () const
    { return (random_access_iterator<value_type const *>(_current)); }


 };

	template <class Iterator>
	bool operator== (const random_access_iterator<Iterator>& lhs,
                   const random_access_iterator<Iterator>& rhs)
	{ return lhs.base() == rhs.base();}	

	template<typename T, typename U>
    bool operator==(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<U> rhs)
    {
        return (lhs.base() == rhs.base());
    }

	template <class Iterator>
	bool operator!= (const random_access_iterator<Iterator>& lhs,
                   const random_access_iterator<Iterator>& rhs)
	{ return lhs.base() != rhs.base();}

	template<typename T, typename U>
    bool operator!=(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<U> rhs)
    {
        return (lhs.base() != rhs.base());
    }

	template <class Iterator>
	bool operator<  (const random_access_iterator<Iterator>& lhs,
                   const random_access_iterator<Iterator>& rhs)
	{return lhs.base() < rhs.base();}

	template <typename T, typename U>
	bool operator<  (const random_access_iterator<T>& lhs,
                   const random_access_iterator<U>& rhs)
	{return lhs.base() < rhs.base();}

	template <class Iterator>
	bool operator>  (const random_access_iterator<Iterator>& lhs,
                   const random_access_iterator<Iterator>& rhs)
	{return lhs.base() > rhs.base();}

	template <typename T, typename U>
	bool operator>  (const random_access_iterator<T>& lhs,
                   const random_access_iterator<U>& rhs)
	{return lhs.base() > rhs.base();}

	template <class Iterator>
	bool operator<= (const random_access_iterator<Iterator>& lhs,
                   const random_access_iterator<Iterator>& rhs)
	{return lhs.base() <= rhs.base();}

	template <typename T, typename U>
	bool operator<=  (const random_access_iterator<T>& lhs,
                   const random_access_iterator<U>& rhs)
	{return lhs.base() <= rhs.base();}

	template <class Iterator>
	bool operator>= (const random_access_iterator<Iterator>& lhs,
                   const random_access_iterator<Iterator>& rhs)
		{return lhs.base() >= rhs.base();}

	template <typename T, typename U>
	bool operator>=  (const random_access_iterator<T>& lhs,
                   const random_access_iterator<U>& rhs)
	{return lhs.base() >= rhs.base();}

	template <class Iterator>
  typename random_access_iterator<Iterator>::difference_type operator- (
    const random_access_iterator<Iterator>& lhs,
    const random_access_iterator<Iterator>& rhs)
	{return lhs.base() - rhs.base();}

	template <typename T, typename U>
  typename random_access_iterator<T>::difference_type operator- (
    const random_access_iterator<T>& lhs,
    const random_access_iterator<U>& rhs)
	{return lhs.base() - rhs.base();}


	template <class Iterator>
  random_access_iterator<Iterator> operator+ (
    typename random_access_iterator<Iterator>::difference_type n,
    const random_access_iterator<Iterator>& rev_it)
	{return &(*rev_it) + n;}

}