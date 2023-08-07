#pragma once
#include "utils.hpp"
#include <type_traits>
#include <cstddef>

namespace ft{
template<typename _Iterator>
  class bidirectional_iterator {

	public :
	typedef _Iterator	iterator_type;
	typedef	bidirectional_iterator_tag									iterator_category;
	typedef typename	iterator_traits<_Iterator *>::value_type		value_type;
	typedef typename	iterator_traits<_Iterator *>::difference_type	difference_type;
	typedef typename	iterator_traits<_Iterator *>::pointer			pointer;
	typedef typename	iterator_traits<_Iterator *>::reference			reference;
	
	private :
	pointer _current;
				
	public :

	bidirectional_iterator() : _current() {}

	bidirectional_iterator(pointer p) : _current(p) {}

	bidirectional_iterator (const bidirectional_iterator &src) : _current(src._current) {}

	~bidirectional_iterator() {}

	pointer base() const {return _current;}

	bidirectional_iterator	&operator=(const bidirectional_iterator &src)
	{
		if (this == &src)
			return *this;
		_current = src._current;
		return *this;
	}

	bidirectional_iterator &operator++()
	{
		_current++;
		return *this;
	}

	bidirectional_iterator operator++(int)
	{
		bidirectional_iterator tmp = *this;
		++_current;
		return (tmp);
	}

	bidirectional_iterator &operator--()
	{
		_current--;
		return *this;
	}

	bidirectional_iterator operator--(int)
	{
		bidirectional_iterator tmp = *this;
		--_current;
		return tmp;
	}



	reference operator*() const 
	{
		return *_current;
	}

	pointer operator->() {return &(operator*());}

    operator bidirectional_iterator<const _Iterator> () const
    { return (bidirectional_iterator<const _Iterator>(_current)); }


 };

	template <class Iterator>
	bool operator== (const bidirectional_iterator<Iterator>& lhs,
                   const bidirectional_iterator<Iterator>& rhs)
	{ return lhs.base() == rhs.base();}	

	template<typename T_L, typename T_R>
    typename ft::bidirectional_iterator<T_L>::difference_type
    operator==(const ft::bidirectional_iterator<T_L> lhs,
              const ft::bidirectional_iterator<T_R> rhs)
    {
        return (lhs.base() == rhs.base());
    }

	template <class Iterator>
	bool operator!= (const bidirectional_iterator<Iterator>& lhs,
                   const bidirectional_iterator<Iterator>& rhs)
	{ return lhs.base() != rhs.base();}

	template<typename T_L, typename T_R>
    typename ft::bidirectional_iterator<T_L>::difference_type
    operator!=(const ft::bidirectional_iterator<T_L> lhs,
              const ft::bidirectional_iterator<T_R> rhs)
    {
        return (lhs.base() != rhs.base());
    }



}