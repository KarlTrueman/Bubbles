#ifndef LIST_H
#define LIST_H

#include <algorithm>
#include <functional>
#include <list>
#include <mutex>

template <typename T>
class List
{
public:
    void for_each(std::function<void(T)> f)
    {
        std::unique_lock<std::mutex> mlock(m_mutex);
        std::for_each(m_List.begin(), m_List.end(), f);
    }

    void push(const T& item)
    {
        std::unique_lock<std::mutex> mlock(m_mutex);
        m_List.push_back(item);
    }
    int length()
    {
        return m_List.size();
    }

    List() = default;
    List(const List&) = delete;            // disable copying
    List& operator=(const List&) = delete; // disable assignment

private:
    std::list<T> m_List;
    std::mutex m_mutex;
};



#endif // !LIST_H