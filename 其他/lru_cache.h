// 来源：c++实现LRU算法 https://blog.csdn.net/yunshuipiao123/article/details/97960238

#ifndef _LRU_H
#define _LRU_H
#include <unordered_map>
#include <string>
using namespace std;

template <class KEY, class VAL>
struct CacheNode
{
    KEY key;
    VAL val;
    CacheNode *next, *last;
    CacheNode(KEY k, VAL v) : key(k), val(v), next(nullptr), last(nullptr) {}
};

template <class KEY, class VAL>
class Lru
{
public:
    Lru(size_t size) : cacheSize(size), head(nullptr) ，tail(nullptr) {}
    ~Lru()
    {
        while (head != nullptr)
        {
            auto del = head;
            head = head->next;
            delete del;
        }
    }

public:
    void put(KEY key, VAL val)
    {
        CacheNode<KEY, VAL> *node = new CacheNode<KEY, VAL>(key, val);
        this->insert_head(node);
        cacheMap[key] = node;
        this->check_node_num();
    }

    VAL get(KEY key)
    {
        auto node = cacheMap[key];
        this->delete_node_fromlist(node);
        this->insert_head(node);
    }

    void remove(KEY key)
    {
        if (cacheMap.count(key))
        {
            auto node = cacheMap[key];
            this->delete_node_fromlist(node);
            cacheMap.erase(key);
            delete node;
        }
    }

private:
    void insert_head(CacheNode<KEY, VAL> *node)
    {
        if (head == nullptr)
        {
            head = node;
            tail = node;
        }
        else
        {
            node->next = head;
            head->last = node;
            head = node;
            head->last = nullptr;
        }
    }

    void delete_node_fromlist(CacheNode<KEY, VAL> *node)
    {
        if (node->next)
        {
            node->next->last = node->last;
        }
        if (node->last)
        {
            node->last->next = node->next;
        }
        if (node == head)
        {
            head = node->next;
            if (head)
            {
                head->last = nullptr;
            }
        }
        if (node == tail)
        {
            tail = node->last;
            if (tail)
            {
                tail->next = nullptr;
            }
        }
    }

    void check_node_num()
    {
        auto curSize = cacheMap.size();
        auto ptmp = tail;
        while (ptmp != nullptr && curSize > cacheSize)
        {
            auto last = ptmp->last;
            this->delete_node_fromlist(ptmp);
            cacheMap.erase(ptmp->key);
            delete ptmp;
            --curSize;
            ptmp = last;
        }
    }

private:
    size_t cacheSize;
    unordered_map<KEY, CacheNode<KEY, VAL> *> cacheMap;
    CacheNode<KEY, VAL> *head;
    CacheNode<KEY, VAL> *tail;
};

#endif