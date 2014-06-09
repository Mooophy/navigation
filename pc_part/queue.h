#ifndef QUEUE_H
#define QUEUE_H

#include "sample.hpp"
#include <deque>
#include <algorithm>

namespace navigation
{
/**
 * @brief The Queue class
 */
class Queue
{
public:

    /**
     * @brief default ctor
     */
    Queue(std::size_t sz):
        data(),size(sz)
    {}

    /**
     * @brief operator <<
     */
    void operator<<(float sample)
    {
        data.push_back(sample);
        if(data.size()>size)
            data.pop_front();
    }

    /**
     * @brief return suggested direction
     */
    std::size_t suggest()const
    {
        return std::round(average());
    }

private:
    std::deque<float> data;
    std::size_t size;

    /**
     * @brief return the average value
     */
    float average()const
    {
        float sum = 0;
        for(const auto& direction : data)
            sum += direction;

        return sum/size;
    }
};
}//namespace

#endif // QUEUE_H
