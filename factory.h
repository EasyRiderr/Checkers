/*
 * factory.h
 * The factory allowing to quick create objects.
 *
 * @author Yoan DUMAS
 * @versionn 1.0
 * @date 19/12/2013
 */


#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <map>


template <class Object,class Key=std::string>
class Factory
{

public:

    /**
     * Records object to quick construct.
     */
    static void record(Key inKey, Object* inObject);


    /**
     * Returns the wished object.
     * @return The wished object.
     */
    Object* create(const Key & inKey);




private:

    /**
     * The map containing all recorded objects.
     */
    static std::map<Key,Object*> map_s;
};

#include "factory.ipp"

#endif // FACTORY_H
