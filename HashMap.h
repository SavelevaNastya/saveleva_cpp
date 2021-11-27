#pragma once
#include "bucket.h"


template<typename Key, typename Value, typename Hash = std::hash<Key>, typename TAllocator = std::allocator<bucket<Key, Value>>>
class HashMap {
public:
	class const_iterator {};
	class iterator {};
	HashMap();
	explicit HashMap(const node_allocator_type& alloc);
	HashMap(std::initializer_list<value_type> il, const TAllocator& alloc);
	HashMap(const HashMap<Key, T, TAllocator>& other);
	HashMap(HashMap<Key, T, TAllocator>&& other);
	virtual ~HashMap();
	HashMap& operator=(const HashMap<Key, T, TAllocator>& right);
	HashMap& operator=(HashMap<Key, T, TAllocator>&& right);
	void swap(HashMap<Key, T, TAllocator>& other);
	template <class E, class P>
	iterator insert(E&& k, P&& value);
	std::optional<T> get(const Key& key);
	template <class... Args>
	std::pair<iterator, bool> emplace(Args&&... args);
	T& operator[](const Key& key);
	T& operator[](Key&& key);
	node_type extract(const_iterator position);
	node_type extract(const key_type& x);
	iterator find(const Key& key);
	const_iterator find(const Key& key) const;
	size_type size() const noexcept;
	bool empty() const noexcept;
	void clear();
	// Iterators and such
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;
};

