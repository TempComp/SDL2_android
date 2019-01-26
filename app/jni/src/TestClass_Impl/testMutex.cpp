#include <chrono>
#include <thread>
#include <mutex>
#include <iostream>
#include "SDL.h"

std::mutex g_mtx;

class guard {
    std::mutex& mtx;
public:
    guard(std::mutex& m) : mtx(m)
    {
        mtx.lock();
        SDL_Log ("Mutex locked\n");
    }

    ~guard()
    {
        SDL_Log ("Mutex unlocked\n");
        mtx.unlock();
    }
};

class document {
public:
    document(std::string link) : url(link)
    {

    }

    std::string getUrl() const
    {
        return url;
    }

private:
    const std::string url;
};

guard lock(const std::string& name)
{
    return guard(g_mtx);
}

void process(const document& doc)
{
    auto l = lock(doc.getUrl()); //locked
    SDL_Log ("event");
    std::this_thread::sleep_for(std::chrono::seconds(3));	//procced
} // unlocking


void testMutex()
{
    document d1("http://foo");
    document d2("http://bar");
    std::thread t1(process, d1);
    std::thread t2(process, d2);
    t1.join();
    t2.join();
}
