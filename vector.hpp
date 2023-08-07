#pragma once
#include "reverse_iterator.hpp"
#include "random_access_iterator.hpp"
#include <memory>
#include <algorithm>
#include "utils.hpp"
namespace ft{

template < class T, class Alloc = std::allocator<T> > 

	class vector{
		public :
		typedef T														value_type;
		typedef Alloc													allocator_type;
		typedef typename allocator_type::reference 						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef ft::random_access_iterator<pointer>					iterator;
		typedef ft::random_access_iterator<const_pointer>			const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef	ptrdiff_t												difference_type;
		typedef size_t													size_type;

		private :
		allocator_type	_alloc;
		size_type		_size;
		size_type		_capacity;
		pointer			_start;

		public :

		explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0), _start(0) {}

		explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n)
				{
					_start = _alloc.allocate(n);
					for (size_type i = 0; i != _size; i++)
						_alloc.construct(_start + i, val);
				}

		template <class InputIterator>
			vector (InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr) : _alloc(alloc)
		{
			_capacity = ft::distance(first, last);
			_start = _alloc.allocate(_capacity);
			std::uninitialized_copy(first, last, _start);
			_size = _capacity;
		}

		vector& operator= (const vector& x)
		{
			if (this == &x)
				return *this;
			for (size_type i = 0; i != _size; i++)
				_alloc.destroy(_start + i);
			_size = x._size;
			if (_capacity < _size)
			{
				if (_capacity != 0)
					_alloc.deallocate(_start, _capacity);
				_capacity = _size;
				_start = _alloc.allocate(_capacity);
			}
			for (size_type i = 0; i != _size; i++)
				_alloc.construct(_start + i, x[i]);
			return *this;
		}

		vector (const vector& x) : _alloc(x._alloc), _size(0), _capacity(0), _start(0) 
		{
			insert(begin(), x.begin(), x.end());
		}

		~vector() 
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_start + i);
			if(_capacity)
				_alloc.deallocate(_start, _capacity);
		}

		void assign (size_type n, const value_type& val)
		{
			if (n < 0)
				return;
			pointer newvec = _alloc.allocate(n);
			for(size_type i = 0; i != n; i++)
				_alloc.construct(newvec + i, val);
			clear();
			_alloc.deallocate(_start, _capacity);
			_start = newvec;
			_size = n;
			_capacity = n;
		}

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
		{
			size_type dis = ft::distance(first ,last);
			pointer newvec = _alloc.allocate(dis > _capacity ? dis : _capacity);
			for (size_type i = 0; i != dis; i++, first++)
				_alloc.construct(newvec + i, (*first));
			clear();
			_alloc.deallocate(_start, _capacity);
			_capacity = dis > _capacity ? dis : _capacity;
			_size = dis;
			_start = newvec;
		}

		void	push_back(const value_type &val)	
		{
			if (_size == _capacity)
				reserve(_capacity * 2 == 0 ? 1 : _capacity * 2);
			_alloc.construct(_start + _size, val);
			_size++;
		}

		void pop_back()
		{
			_alloc.destroy(_start + _size - 1);
			_size--;
		}

		void	clear()	
		{
			for (size_type i = 0; i != _size; i++)
				_alloc.destroy(_start + i);
			_size = 0;
		}

		void reserve (size_type n) 
		{
			if (n > max_size())
				throw (std::length_error("vector::reserve"));	
			size_type old_size = _size;
			if (n <= _capacity)
				return;
			pointer newvec = _alloc.allocate(n);
			for (size_type i = 0; i != _size; i++)
				_alloc.construct(newvec + i, _start[i]);
			clear();
			for (size_type i = 0; i != _size; i++)
				_alloc.destroy(_start + i);
			_alloc.deallocate(_start, _capacity);
			_size = old_size;
			_start = newvec;
			_capacity = n;
		}

		void resize (size_type n, value_type val = value_type())
		{
			if (n > max_size())
				throw (std::length_error("vector::resize"));
			else if (n <size())
			{
				while (size() > n)
				{
					--_size;
					_alloc.destroy(_start + _size);
				}
			}
			else
			insert(end(), n - size(), val);
		}

		iterator insert (iterator position, const value_type& val)
		{
			if (position < begin() || position > end())
				throw std::logic_error("vector");
			difference_type pos = position - begin();
			if (_capacity == _size)
			{
				pointer newvec = _alloc.allocate(_capacity * 2 + (_capacity == 0));
				std::uninitialized_copy(begin(), position, iterator(newvec));
				_alloc.construct(newvec + pos, val);
				std::uninitialized_copy(position, end(), iterator(newvec + pos + 1));
				clear();
				_alloc.deallocate(_start, _capacity);
				_size = _capacity + 1;
				_capacity = _capacity * 2 + (_capacity == 0); 
				_start = newvec;
				return (begin() + pos);
			}
			size_type old_size = _size;	
			pointer newvec = _alloc.allocate(_capacity);
			std::uninitialized_copy(begin(), position, iterator(newvec));
			_alloc.construct(newvec + pos, val);
			std::uninitialized_copy(position, end(), iterator(newvec + pos + 1));
			clear();
			_alloc.deallocate(_start, _capacity);
			_size = old_size + 1;
			_start = newvec;			
			return (begin() + pos);
		}

		void insert (iterator position, size_type n, const value_type& val)
		{
			if (n == 0)
				return ;
			if (max_size() - _size < n)
				throw std::logic_error("vector");
			difference_type pos = position - begin();
			if (_capacity < _size + n)
			{
				size_type old_size = _size;
				size_type new_capacity = _capacity * 2 >= _size + n ? _capacity * 2 : _size + n;
				pointer newvec = _alloc.allocate(new_capacity);
				std::uninitialized_copy(begin(), position, iterator(newvec));
				for (size_type i = 0; i < n; i++)
					_alloc.construct(newvec + pos + i, val);
				std::uninitialized_copy(position, end(), iterator(newvec + pos + n));
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_start + i);
				_alloc.deallocate(_start, _capacity);
				_size = old_size + n;
				_capacity = new_capacity; 
				_start = newvec;
			}
			else {
				size_type old_size = _size;	
				pointer newvec = _alloc.allocate(_capacity);
				std::uninitialized_copy(begin(), position, iterator(newvec));
				for (size_type i = 0; i < n; i++)
					_alloc.construct(newvec + pos + i, val);
				std::uninitialized_copy(position, end(), iterator(newvec + pos + n));
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_start + i);
				_alloc.deallocate(_start, _capacity);
				_size = old_size + n;
				_start = newvec;
			}
		}

		template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
		{
			if (position < begin() || position > end())
				throw std::logic_error("vector");
			difference_type pos = position - begin();
			difference_type dis = ft::distance(first, last);
			if (_capacity < _size + dis)
			{
				size_type new_size = _size + dis;
				size_type new_capacity = _capacity * 2 >= _size + dis ? _capacity * 2 : _size + dis;
				pointer newvec = _alloc.allocate(new_capacity);
				std::uninitialized_copy(begin(), position, iterator(newvec));
				try {
					for (long i = 0; i < dis; i++, first++)
						_alloc.construct(newvec + pos + i, *first);
				}
				catch (...){
					for (long i = 0; i < dis + pos; ++i)
						_alloc.destroy(newvec + i);
					_alloc.deallocate(newvec, new_capacity);
					throw;
				}
				std::uninitialized_copy(position, end(), iterator(newvec + pos + dis));
				clear();
				_alloc.deallocate(_start, _capacity);
				_size = new_size;
				_capacity = new_capacity; 
				_start = newvec;
				return;
			}
				for (long i = _size; i > pos; i--) {
					_alloc.destroy(_start + i + dis - 1);
					_alloc.construct(_start + i + dis - 1, *(_start + i - 1));
				}
				for (long i = 0; i < dis; i++, first++) {
					_alloc.destroy(_start + i + dis);
					_alloc.construct(_start + pos + i, *first);
				}
				_size += dis;	
		}

		iterator erase (iterator position)
		{
			size_type old_size = _size;
			difference_type dif = position - begin();
			pointer newvec = _alloc.allocate(_capacity);
			std::uninitialized_copy(begin(), position, newvec);
			std::uninitialized_copy(position + 1, end(), newvec + dif);
			clear();
			_alloc.deallocate(_start, _capacity);
			_size = old_size - 1;
			_start = newvec;
			return (iterator(_start + dif));
		}

		iterator erase(iterator first, iterator last)
		{
			size_type old_size = _size;
			difference_type dis = last - first;
			difference_type dis2 = first - begin();
			pointer newvec = _alloc.allocate(_capacity);
			std::uninitialized_copy(begin(), first, newvec);
			std::uninitialized_copy(last, end(), newvec + dis2);
			clear();
			_alloc.deallocate(_start, _capacity);
			_size = old_size - dis;
			_start = newvec;
			return (iterator(_start + dis2));
		}

		void swap (vector& x)
		{
			std::swap(_alloc, x._alloc);
			std::swap(_start, x._start);
			std::swap(_size, x._size);
			std::swap(_capacity, x._capacity);
		}

		iterator begin() {return iterator(_start);}

		const_iterator begin() const {return const_iterator(_start);}

		iterator end() 
		{
			if (this->empty())
					return (this->begin());
				return (iterator(_start + _size));}

		const_iterator end() const {				
			if (this->empty())
				return (this->begin());
			return (const_iterator(_start + _size));}

		reverse_iterator rbegin() {return reverse_iterator(end());}

		const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}

		reverse_iterator rend() {return reverse_iterator(begin());}

		const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

		size_type size() const {return _size;}

		size_type max_size() const {return _alloc.max_size();}

		size_type capacity() const {return _capacity;}

		bool empty() const {return !_size;}

		reference at (size_type n) 
		{
			if (n > _size)
				throw std::out_of_range("vector");
			return *(_start + n);
		}

		const_reference at (size_type n) const 
		{
			if (n > _size)
				throw std::out_of_range("vector");
			return *(_start + n);
		}

		reference front() {return *_start;}

		const_reference front() const {return *_start;}

		reference back() {return *(_start + _size - 1);}
		
		const_reference back() const {return *(_start + _size - 1);}

		reference operator[] (size_type n) {return _start[n];}

		const_reference operator[] (size_type n) const {return _start[n];};

		allocator_type get_allocator() const {return _alloc;};
	};

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i != lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{return !(rhs == lhs);}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{return rhs < lhs;}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{return !(lhs > rhs);}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{return !(lhs < rhs);}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{x.swap(y);}
}