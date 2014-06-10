#ifndef SAMPLE_HPP
#define SAMPLE_HPP

#include <fstream>
#include <queue>
#include <string>
#include <assert.h>
#include <iterator>

namespace navigation {

/**
 * @brief sample
 *
 * store a sample and give the suggested direction.
 */
class sample
{
public:
    /**
     * @brief default ctor
     */
    sample( const std::string& raw)
    {
        assert(!raw.empty());

        std::string temp;
        std::string::const_iterator input = raw.cbegin();

        //! left sensor
        while(*input != '|')
            temp.push_back(*input++);
        left = std::stoi(temp);

        //! mid sensor
        ++input;
        temp.clear();
        while(*input != '|')
            temp.push_back(*input++);
        mid  = std::stoi(temp);

        //! right sensor
        ++input;
        temp.clear();
        while(*input != '|')
            temp.push_back(*input++);
        right = std::stoi(temp);
    }

    /**
     * @brief guide
     *
     * return the suggested direction
     *      1   :   left
     *      2   :   mid
     *      3   :   right
     */
    int result() const
    {
        if(left>mid && left>right)
            return 1;
        else if(mid > right || far_away())
            return 2;
        else
            return 3;
    }

    /**
     * @brief far_away
     */
    bool far_away() const
    {
        return left > 100 && mid > 100 && right > 100;
    }

private:
    float left;
    float mid;
    float right;
};

}//namespace
#endif // SAMPLE_HPP
