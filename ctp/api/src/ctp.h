#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include <codecvt>
#include <condition_variable>
#include <locale>

#ifdef __APPLE__
#include <iconv.h>
#endif

#include "pybind11/pybind11.h"

using namespace std;

// Task structure
struct Task
{
    int task_name;		// Callback function type
    void *task_data;	// Data pointer
    void *task_error;	// Error pointer
    int task_id;		// Request ID
    bool task_last;		// Is it the last return
};

class TerminatedError : std::exception
{};

class TaskQueue
{
private:
    std::queue<Task> queue_;					// Task queue
    std::mutex mutex_;							// Mutex
    std::condition_variable cond_;				// Condition variable

    std::atomic<bool> _terminate{false};

public:

    // Push new task
    void push(const Task &task)
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        queue_.push(task);					// Write task to queue
        mlock.unlock();						// Release lock
        cond_.notify_one();					// Notify waiting threads
    }

    // Get task from queue
    Task pop()
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        cond_.wait(mlock, [&]() {
            return !queue_.empty() || _terminate;
        });				// Wait for notification
        if (_terminate)
            throw TerminatedError();
        Task task = queue_.front();			// Get first task from queue
        queue_.pop();						// Remove from queue
        return task;						// Return task
    }

    void terminate()
    {
        _terminate = true;
        cond_.notify_all();					// Notify all waiting threads
    }
};


// Get integer value from dict
void getInt(const pybind11::dict &d, const char *key, int *value)
{
    if (d.contains(key))		// Check if key exists
    {
        pybind11::object o = d[key];		// Get value
        *value = o.cast<int>();
    }
};


// Get double value from dict
void getDouble(const pybind11::dict &d, const char *key, double *value)
{
    if (d.contains(key))
    {
        pybind11::object o = d[key];
        *value = o.cast<double>();
    }
};


// Get char value from dict
void getChar(const pybind11::dict &d, const char *key, char *value)
{
    if (d.contains(key))
    {
        pybind11::object o = d[key];
        *value = o.cast<char>();
    }
};


template <size_t size>
using string_literal = char[size];

// Get string value from dict
template <size_t size>
void getString(const pybind11::dict &d, const char *key, string_literal<size> &value)
{
    if (d.contains(key))
    {
        pybind11::object o = d[key];
        std::string s = o.cast<std::string>();
        const char *buf = s.c_str();
        strncpy(value, buf, size - 1);
        value[size - 1] = '\0';
    }
};


// Convert GBK string to UTF8
#ifndef __APPLE__
inline std::string toUtf(const std::string &gb2312)
{

    #ifdef _MSC_VER
        const static std::locale loc("zh-CN");
    #else
        const static std::locale loc("zh_CN.GB18030");
    #endif

        std::vector<wchar_t> wstr(gb2312.size());
        wchar_t* wstrEnd = nullptr;
        const char* gbEnd = nullptr;
        mbstate_t state = {};
        int res = std::use_facet<std::codecvt<wchar_t, char, mbstate_t> >
            (loc).in(state,
                gb2312.data(), gb2312.data() + gb2312.size(), gbEnd,
                wstr.data(), wstr.data() + wstr.size(), wstrEnd);

        if (std::codecvt_base::ok == res)
        {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> cutf8;
            return cutf8.to_bytes(std::wstring(wstr.data(), wstrEnd));
        }

        return std::string();
}
#else
inline std::string toUtf(const std::string &gb2312)
{
    iconv_t cd = iconv_open("UTF-8", "GB2312");
    if (cd == (iconv_t)-1) {
        return "";
    }

    size_t inlen = gb2312.size();
    size_t outlen = inlen * 2 + 1;
    std::vector<char> temp(outlen, 0);

    char *inbuf = const_cast<char*>(gb2312.c_str());
    char *outbuf = temp.data();

    if (iconv(cd, &inbuf, &inlen, &outbuf, &outlen) == (size_t)-1) {
        iconv_close(cd);
        return "";
    }
    iconv_close(cd);

    return std::string(temp.data());
}
#endif
