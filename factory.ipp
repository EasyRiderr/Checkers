/*
* factory.ipp
* The factory allowing to quick create objects.
*
* @author Yoan DUMAS
* @versionn 1.0
* @date 19/12/2013
*/


template <class Object,class Key> std::map<Key,Object*>
Factory<Object,Key>::map_s = std::map<Key,Object*>();


template <class Object,class Key>
void Factory<Object,Key>::record(Key inKey, Object* inObject)
{
    if(map_s.find(inKey) == map_s.end()) {
        map_s[inKey] = inObject;
    }
}

template <class Object,class Key>
Object* Factory<Object,Key>::create(const Key & inKey)
{
    Object* tmp = NULL;
    typename std::map<Key, Object*>::iterator it = map_s.find(inKey);

    if(it != map_s.end()) {
        tmp = ((*it).second)->Clone();
    }

    return tmp;
}
