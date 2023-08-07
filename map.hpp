#pragma once
# include "utils.hpp"
# include "reverse_iterator.hpp"
# include "RedBlackTreeIterator.hpp"
# include "Redb.hpp"
# include <functional>
# include <memory>
# include <map>

namespace ft {

template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > > class map
{
	public :
	typedef Key															key_type;
	typedef T															mapped_type;
	typedef ft::pair<const key_type, mapped_type>						value_type;
	typedef Compare														key_compare;
	class value_compare 
	{
		protected :
		key_compare comp;

		value_compare(key_compare c) : comp(c) {}

		public :
		bool operator()(const value_type &x, const value_type &y) const 
		{return comp(x.first, y.first);}
	};
	typedef Alloc														allocator_type;
	typedef typename allocator_type::reference							reference;
	typedef typename allocator_type::const_reference					const_reference;
	typedef typename allocator_type::pointer							pointer;
	typedef typename allocator_type::const_pointer						const_pointer;
	typedef ft::RBTreeIterator<value_type>								iterator;
	typedef ft::ConstRBTreeIterator<value_type>							const_iterator;
	typedef ft::reverse_iterator<iterator>								reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
	typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
	typedef size_t														size_type;

	typedef typename allocator_type::template rebind<typename ft::Node<T> >::other   node_allocator;
	private :

	RedBTree<value_type>		_bst;
	node_allocator				_alloc;
	Compare						_comp;


	public :

	explicit map (const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type()) : _bst(), _alloc(alloc), _comp(comp) {}

	template <class InputIterator>
  	map (InputIterator first, InputIterator last,
       const key_compare& comp = key_compare(),
       const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp)
	   {
		   for(;first != last; first++)
			   insert(make_pair(first->first, first->second));
	   }

	map (const map& x)
	{
		_bst = x._bst;
		_alloc = x._alloc;
		_comp = x._comp;
	}

	map& operator= (const map& x)
	{
		_bst = x._bst;
		_alloc = x._alloc;
		_comp = x._comp;
		return *this;
	}

	~map() {}

	iterator begin() {return iterator(_bst.min());}

	const_iterator begin() const {return const_iterator(_bst.min());}

	iterator end() {
		ft::RBTreeIterator<value_type>	it = _bst.max();
		it++;
		return it;
	}

	pair<iterator,bool>	insert (const value_type& val)
	{
		if (_bst.getSize() == 0)
		{
			_bst.insert(val);
			return ft::make_pair(find(val.first), true);
		}
		_bst.search(val);
		if (_bst.checkScam() == 1)
		{
			_bst.endScam();
			_bst.insert(val);
			return ft::make_pair(find(val.first), true);
		}
		return ft::make_pair(find(val.first), false);
		//if (_bst.search(val) != nullptr && _bst.search(val)->data.first == val.first)
		//	return make_pair(iterator(_bst.search(val)), false);
		//_bst.insert(val);
		//return make_pair(iterator(_bst.search(val)), true);
	}

	iterator insert (iterator position, const value_type& val)
	{
		position++;
		position--;
		if (_bst.search(val) != nullptr && _bst.search(val)->data.first == val.first)
			return iterator(_bst.search(val));
		_bst.insert(val);
		return iterator(_bst.search(val));
	}

	template <class InputIterator>
  	void insert (InputIterator first, InputIterator last)
	{
		for (; first != last; first++)
			insert(make_pair(first->first, first->second));
	}

	void erase (iterator position)
	{
		if (find(position->first))
		if (_bst.search(*position) != nullptr && _bst.search(*position)->data.first != position->first)
			return;
		_bst.deleteBydata(*position);
	}

	size_type erase (const key_type& k)
	{
		if (_bst.search(ft::make_pair(k, mapped_type())) != nullptr && _bst.search(ft::make_pair(k, mapped_type()))->data.first != k)
			return 0;
		_bst.deleteBydata(ft::make_pair(k, mapped_type()));
		return 1;
	}

	void erase (iterator first, iterator last)
	{
		iterator *it = first;
		while (first != last)
		{
			if (it )
			if (_bst.search(*first) != nullptr && _bst.search(*first)->data.first != first->first)
				return;
			_bst.deleteBydata(*first);
			first++;
		}
	}

	bool empty() const {return _bst.getSize() == 0;}

	size_type size() const {return _bst.getSize();}

	size_type max_size() const 
	{
		return _alloc.max_size();
	}

	iterator find (const key_type& k)
	{
		_bst.search(ft::make_pair(k, mapped_type()));
		if (_bst.checkScam() == 1)
		{
			_bst.endScam();
			return (end());
		}
		return iterator(_bst.search(ft::make_pair(k, mapped_type())));
	}

	const_iterator find (const key_type& k) const
	{return const_iterator(_bst.search(ft::make_pair(k, mapped_type())));}

	mapped_type& operator[] (const key_type& k)
	{
		insert(ft::make_pair(k, mapped_type()));
		return find(k)->second;
	}

};

}