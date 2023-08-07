#pragma once
#include "utils.hpp"

namespace ft{

template <class Iterator> class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
                      typename iterator_traits<Iterator>::value_type,
                      typename iterator_traits<Iterator>::difference_type,
                      typename iterator_traits<Iterator>::pointer,
                      typename iterator_traits<Iterator>::reference> 
{

	public :
	typedef Iterator													iterator_type;
	typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
	typedef typename ft::iterator_traits<Iterator>::reference			reference;

	private:
	iterator_type _current;

	public:

	reverse_iterator() : _current(iterator_type()) {}

	explicit reverse_iterator (iterator_type it) : _current(it) {};

	template <class Iter>
	reverse_iterator (const reverse_iterator<Iter>& rev_it) : _current(rev_it.base()) {}

	virtual ~reverse_iterator() {}

	iterator_type	base() const {return _current;}

	reference operator*() const
	{
		Iterator tmp = _current;
		return (*(--tmp));
	}

	reverse_iterator& operator++() 
	{
		_current--;
		return *this;
	}

	reverse_iterator  operator++(int)
	{
		reverse_iterator tmp = *this;
		_current--;
		return tmp;
	}

	reverse_iterator operator+ (difference_type n) const
	{
		return reverse_iterator(_current - n);
	}

	reverse_iterator& operator+= (difference_type n)
	{
		_current -= n;
		return *this;
	}

	reverse_iterator operator- (difference_type n) const
	{
		return reverse_iterator(_current + n);
	}

	reverse_iterator& operator--()
	{
		++_current;
		return *this;
	}

	reverse_iterator  operator--(int)
	{
		reverse_iterator tmp = *this;
		--(*this);
		return tmp;
	}

	reverse_iterator& operator-= (difference_type n)
	{
		_current += n;
		return *this;
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	reference operator[] (difference_type n) const
	{
		return *(*this + n);
	}

    operator reverse_iterator<iterator_type const> () const
    { return (reverse_iterator<iterator_type const>(_current)); }
};

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs)
	{ return lhs.base() == rhs.base();}

	template<typename T, typename U>
    bool operator==(const ft::reverse_iterator<T> lhs,
              const ft::reverse_iterator<U> rhs)
    {
        return (lhs.base() == rhs.base());
    }

	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() != rhs.base());}

	template<typename T, typename U>
    bool operator!=(const ft::reverse_iterator<T> lhs,
              const ft::reverse_iterator<U> rhs)
    {
        return (lhs.base() != rhs.base());
    }

	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs)
	{return lhs.base() > rhs.base();}

	template<typename T, typename U>
    bool operator< (const ft::reverse_iterator<T> lhs,
              const ft::reverse_iterator<U> rhs)
    {
        return (lhs.base() > rhs.base());
    }

	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs)
	{return !(lhs <= rhs);}

	template<typename T, typename U>
    bool operator> (const ft::reverse_iterator<T> lhs,
              const ft::reverse_iterator<U> rhs)
    {
        return !(lhs <= rhs);
    }

	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs)
	{return (lhs == rhs || lhs < rhs);}

	template<typename T, typename U>
    bool operator<=(const ft::reverse_iterator<T> lhs,
              const ft::reverse_iterator<U> rhs)
    {
        return (lhs == rhs || lhs < rhs);
    }

	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs)
		{return !(lhs < rhs);}

	template<typename T, typename U>
    bool operator>= (const ft::reverse_iterator<T> lhs,
              const ft::reverse_iterator<U> rhs)
    {
        return !(lhs < rhs);
    }

    template <class Iter>
    reverse_iterator<Iter>
    operator-(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& rhs)
    { return reverse_iterator<Iter>(rhs.base() + n); }

    template <typename Iter1, typename Iter2>
    typename reverse_iterator<Iter1>::difference_type
    operator-(reverse_iterator<Iter1> const & lhs, reverse_iterator<Iter2> const & rhs)
    { return rhs.base() - lhs.base();}


	template <class Iterator>
	reverse_iterator<Iterator> operator+ (
    typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>& rev_it)
	{return rev_it + n;}
}