#pragma once
#ifndef _MONOTON_HPP_
#define _MONOTON_HPP_

template<typename ITER, typename PRED>
bool monoton(ITER begin, ITER end, PRED pred)
{
    if (begin == end) // empty
        return true;
    ITER fol = begin++; // set first
    while (begin != end)
    {
        if (!pred(*begin, *fol))
            return false;
        fol = begin++; // step
    }
    return true; // end
}

#endif // _MONOTON_HPP_