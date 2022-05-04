#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <string>
template <typename T>
class queue
{
public:
    T pop() // Blocking pop
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        cond_.wait(mlock, [this] {return !queue_.empty(); });
        auto val = queue_.front();
        queue_.pop();
        return val;
    }

    void pop(T& item) // pop will not wait with an empty queue
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        if (queue_.empty())
        {
            return;
        }
        item = queue_.front();
        queue_.pop();
    }

    void push(const T& item)
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        queue_.push(item);
        cond_.notify_one();
    }
    queue() = default;
    queue(const queue&) = delete;            // disable copying
    queue& operator=(const queue&) = delete; // disable assignment

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_;
};