#include "bucket.h"
#include <shared_mutex>
#include <mutex> //????

template<typename Key, typename Value>
bucket<Key, Value>::bucket() {
	data.assign(0,data_type());
};

template<typename Key, typename Value>
bucket<Key, Value>::bucket(Key&& key, Value&& val) {
	data.push_back(std::make_pair<Key, Value>(std::move(key), std::move(value)));
}

template<typename Key, typename Value>
bucket<Key, Value>::bucket(const bucket<Key, Value>& other) {
	data = data.other;
}

template<typename Key, typename Value>
typename bucket<Key, Value>::bucket_iterator bucket<Key, Value>::find(const Key& key) {

}

template<typename Key, typename Value>
bucket<Key, Value>& bucket<Key, Value>::operator=(const bucket<Key, Value>& other) {

}

template<typename Key, typename Value>
Value bucket<Key, Value>::GetValue(const Key& key) {
	
}

template<typename Key, typename Value>
void bucket<Key, Value>::Remove(const Key& key) {

}

template<typename Key, typename Value>
size_t bucket<Key, Value>::size() const {

}

template<typename Key, typename Value>
bool bucket<Key, Value>::empty() const {

}

template<typename Key, typename Value>
typename bucket<Key, Value>::bucket_iterator bucket<Key, Value>::begin() {

}

template<typename Key, typename Value>
typename bucket<Key, Value>::bucket_iterator bucket<Key, Value>::end() {

}