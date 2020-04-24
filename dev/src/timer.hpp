#ifndef TIMER_HPP
#define TIMER_HPP
#include "config.hpp"

#include <chrono>

class Timer
{
    private:
        using clock_t = std::chrono::high_resolution_clock;
        using second_t = std::chrono::duration<double, std::ratio<1> >;
        std::chrono::time_point<clock_t> m_begin;
    public:
        Timer() 
            : m_begin( clock_t::now() )
        { }

        double dur()
        {
            double ret{ std::chrono::duration_cast<second_t>(clock_t::now() - m_begin).count() };
            m_begin = clock_t::now();
            return ret;
        }
};

#endif // guard
