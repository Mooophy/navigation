#ifndef DATA_HPP
#define DATA_HPP

#include <deque>
#include <string>
#include <assert.h>

namespace navigation{


class data
{
public:
    using Deque     = std::deque<int>;
    using SizeType  = std::size_t;

    /**
     * @brief default ctor
     */
    data(SizeType sz):
        left(),mid(),right(),size(sz)
    {}

    /**
     * @brief insert
     *
     * @param raw sample
     */
    void insert(const std::string& raw)
    {
        assert(!raw.empty());
        std::string temp;
        std::string::const_iterator input = raw.cbegin();

        //! left sensor
        while(*input != '|')
            temp.push_back(*input++);
        left.push_back(std::stoi(temp));

        //! mid sensor
        ++input;
        temp.clear();
        while(*input != '|')
            temp.push_back(*input++);
        mid.push_back(std::stoi(temp));

        //! right sensor
        ++input;
        temp.clear();
        while(*input != '|')
            temp.push_back(*input++);
        right.push_back(std::stoi(temp));

        //! pop when full
        if(left.size() >= size)
        {
            left.pop_front();
            mid.pop_front();
            right.pop_front();
        }
    }

    /**
     * @brief suggest
     */
    SizeType suggest() const
    {
        bool l = detected(left,60,3);
        bool m = detected(mid,60,3);
        bool r = detected(right,60,3);

        SizeType state = l<<8 | m<<4 | r<<0;
        SizeType ret = 0;

        switch (state)
        {
        case 0x101:     //  both left and right detected, go back.
            ret = 4;    break;

        case 0x100:     //  left is detected, go right
            ret = 3;    break;

        case 0x001:     //  right is detected, go left
            ret = 1;    break;

        default:        //  keep going
            ret = 2;    break;
        }

    return ret;
    }

private:
    Deque left;
    Deque mid;
    Deque right;
    SizeType size;

    /**
     * @brief average
     */
    int average(const Deque& d) const
    {
        SizeType sum = 0;
        for (auto sample : d)
            sum += sample;

        return sum/d.size();
    }

    /**
     * @brief variance
     */
    int variance(const Deque& d) const
    {
        SizeType avrg = average(d);
        SizeType varn = 0;
        for(auto sample : d)
            varn += (sample - avrg) * (sample - avrg);

        return varn;
    }

    /**
     * @brief level
     * @param variance
     * @return
     */
    int level(int variance) const
    {
        int level = 0;
        while(variance > 0)
        {
            variance /= 2 ;
            ++level;
        }

        return level;
    }
    /**
     * @brief detected
     * @param d
     * @param avg_limit
     * @param lvl_limit
     * @return
     *
     * check if any obstacle is near and steady.
     */
    bool detected(const Deque& d, int avg_limit, int lvl_limit) const
    {
        int lvl = level(variance(d));

        return average(d) > avg_limit && lvl > lvl_limit;
    }
};

}//namspace

#endif // DATA_HPP
