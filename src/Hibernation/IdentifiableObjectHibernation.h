#pragma once

/*
 * "Identifiable objects" means that more than one instance of its class can
 * exist per application. Each instance is associated to an "identifier".
 *
 * For example, you want to serialize some object into a file. Thus,
 * `ObjectType` is the type of this object and is `Cookbook`, and the
 * `ObjectIdentifier` perhaps is something like `std::wstring` holding
 * the path to the file.
 *
 * `load()` is responsible for deserializing your file into a new object
 * instance and `store()` serializes your object into the file.
 *
 * There are two overloads of `store()` since there may be cases where your
 * hibernation implementation itself (or some piece of code called inside
 * the hibernation) determines the identifier. This applies to an
 * `AUTO_INCREMENT` field in a SQLite database or when your hibernation deals
 * with serializing temporary files, for example. Both overloads of `store()`
 * return the object identifier for uniformity and sanity reasons.
 *
 * You are not forced to implement each of those methods. It's fully
 * legitimate to implement a "read-only hibernation" or intentionally
 * just provide a functional implementation of just one `store()` overload.
 */
template <typename ObjectIdentifierType,
    typename ObjectType>
    class IdentifiableObjectHibernation
{
    virtual ObjectType load(ObjectIdentifierType id) = 0;

    virtual ObjectIdentifierType store(ObjectType object) = 0;
    virtual ObjectIdentifierType store(ObjectIdentifierType id,
        ObjectType object) = 0;
};