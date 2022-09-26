#pragma once

#include "libH.h"

class Steward
{
public:
    explicit Steward(size_t maxPhilosophers)
        : maxPhilosophers_(maxPhilosophers)
        , busyChopsticks_(maxPhilosophers)
    {
    }

    using Chopsticks = std::pair<size_t, size_t>;

    Chopsticks getChopsticks(size_t philosopher)
    {
        assert(philosopher < maxPhilosophers_);
        const auto chopsticks = getChopstickNumbers(philosopher);

        std::unique_lock<std::mutex> lock(mutex_);

        while (busyChopsticks_[chopsticks.first] == true
            || busyChopsticks_[chopsticks.second] == true)
        {
            chopsticksAreBack_.wait(lock);
        }

        cout << "getChopsticks [" << 
            busyChopsticks_.size() << 
            "][" << chopsticks.first << "][" << 
                    chopsticks.second << "]" << endl;

        busyChopsticks_[chopsticks.first] = true;
        busyChopsticks_[chopsticks.second] = true;

        return chopsticks;
    }

    void returnChopsticks(Chopsticks chopsticks)
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);                       
            
            //cout << "returnChopsticks [" << busyChopsticks_.size() << "][" << chopsticks.first << "] " << endl;

            busyChopsticks_[chopsticks.first] = false;
            busyChopsticks_[chopsticks.second] = false;
        }

        chopsticksAreBack_.notify_all();
    }

private:
    const size_t maxPhilosophers_;

    std::vector<bool> busyChopsticks_;

    std::mutex mutex_;
    std::condition_variable chopsticksAreBack_;

    Chopsticks getChopstickNumbers(size_t philosopher)
    {
        // | P0 | P1 | P2 |
        // 0    1    2    3
        return std::make_pair(philosopher, philosopher + 1);
    }
};

void ex99()
{
    const size_t maxPhilosophers = 300;

    Steward steward(maxPhilosophers);

    std::vector<std::thread> philosophers;
    for (size_t i = 0; i < maxPhilosophers; ++i)
    {
        philosophers.emplace_back(
            [i, &steward]()
            {
                const auto chopsticks = steward.getChopsticks(i);
                // eat
                steward.returnChopsticks(chopsticks);
            });
    }

    for (auto& t : philosophers)
    {
        t.join();
    }


}
