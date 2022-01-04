#pragma once

/*
 * "Single objects" are objects which only exist once per application.
 * This mostly applies to objects which are only loaded once at application
 * start, such as an application's configuration, for example.
 */
template <typename ObjectType>
class SingleObjectHibernation
{
    virtual ObjectType load() = 0;
    virtual void store(ObjectType object) = 0;
};