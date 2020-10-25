//
// Created by ira on 25.10.2020.
//

#ifndef LAB1_LINKEDHASHMAP_LRUCACHE_H
#define LAB1_LINKEDHASHMAP_LRUCACHE_H

#include <cassert>
#include <cstddef>
#include <optional>
#include <list>
#include <unordered_map>

template<typename KeyType, typename ValueType>
class LRUCache {
public:
    LRUCache(std::size_t capacity) : capacity(capacity) {}

    void Put(KeyType key, ValueType value);

    std::optional<ValueType> Get(KeyType key);

    size_t GetSize() const;

private:
    void CheckSize() {
        assert(size <= capacity);
        assert(size == map.size());
        assert(size == list.size());
    }

    std::size_t capacity = 0;
    std::unordered_map<KeyType, std::list<std::pair<int, std::string>>::iterator> map;
    std::list<std::pair<KeyType, ValueType>> list;
    std::size_t size = 0;
};

template<typename KeyType, typename ValueType>
void LRUCache<KeyType, ValueType>::Put(KeyType key, ValueType value) {
    CheckSize();
    size_t init_size_for_assert = size;

    if (capacity == 0) return;
    assert(capacity > 0);

    if (map.contains(key)) {
        list.erase(map[key]);
        list.push_front({key, value});
        map[key] = list.begin();

        assert(size == init_size_for_assert);
    } else {
        if (size < capacity) {
            ++size;
            list.push_front({key, value});
            map[key] = list.begin();

            assert(size == init_size_for_assert + 1);
        } else {
            map.erase(list.back().first);
            list.pop_back();
            list.push_front({key, value});
            map[key] = list.begin();

            assert(size == init_size_for_assert);
        }
    }

    CheckSize();
    assert(map.contains(key));
    assert(map[key] == list.begin());
    assert((*map[key]).second == value);
}

template<typename KeyType, typename ValueType>
std::optional<ValueType> LRUCache<KeyType, ValueType>::Get(KeyType key) {
    CheckSize();
    size_t init_size_for_assert = size;

    if (!map.contains(key)) return {};

    assert(map.contains(key));
    assert((*map[key]).first == key);

    auto element = *map[key];
    list.erase(map[key]);
    list.push_front(element);

    CheckSize();
    assert(size == init_size_for_assert);
    assert(map.contains(key));
    assert(map[key] == list.begin());
    assert((*map[key]).first == key);
    assert((*map[key]).second == element.second);

    return element.second;
}

template<typename KeyType, typename ValueType>
size_t LRUCache<KeyType, ValueType>::GetSize() const {
    return size;
}

#endif //LAB1_LINKEDHASHMAP_LRUCACHE_H
