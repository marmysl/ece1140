#pragma once

#include <vector>

namespace MK1Util
{
    // Generic method that performs binary search based on a field of an object
    // arr: pointer to a vector of type T
    // val: field value to search for, of type U
    // pred: function that takes type T and returns the value of the desired field
    // returns: index of found object, or -1 if not found
    template <typename T, typename U>
    int binSearchOnField( std::vector<T> *arr, U val, U (*pred)(T) )
    {
        // binary search vector for obj w/ specified field
        int len = arr->size();
        if( len == 0 ) return -1;

        int right = len;
        int left = 0;
        int idx;

        while( right >= left )
        {
            idx = (left + right) / 2;

            T atIdx = arr->at(idx);

            if( pred(atIdx) < val )
            {
                // need to move right
                left = idx + 1;
            }
            else if( pred(atIdx) > val )
            {
                // need to move left
                right = idx - 1;
            }
            else return idx; // perfect
        }

        return -1;
    }
}
