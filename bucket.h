#pragma once
#include <list>

template <typename Key, typename Value>
class bucket {
public:
	using data_type = typename std::pair<Key, Value>;
	using bucket_iterator = typename std::list<data_type>::iterator;

	bucket();

	bucket(Key&&, Value&&);

	bucket(const bucket&);

	bucket_iterator find(const Key& key);

	bucket& operator=(const bucket&);

	Value GetValue(const Key&);

	void Remove(const Key&);

	size_t size() const;

	bool empty() const;

	bucket_iterator begin();

	bucket_iterator end();

private:
	std::list<data_type> data;
	std::shared_mutex shm;
};