/*
 * prototype.h
 * Permit to be sure that all class in the factory can be cloned.
 *
 * @author Yoan DUMAS
 * @versionn 1.0
 * @date 19/12/2013
 */


#ifndef PROTOTYPE_H
#define PROTOTYPE_H


template <class T>
class Prototype
{

public:

    virtual ~Prototype(){}

    virtual T* Clone() const =0 ;

};

#endif // PROTOTYPE_H
