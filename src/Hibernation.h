#pragma once

#include "pch.h"

/*
 * Hibernations
 * ============
 * 
 * A hibernation is a class which is responsible for persisting
 * and loading an object. Furthermore, it can hold resources (or
 * references to resources) which are responsible for those processes,
 * e.g. a file handle, a connection handle, ...
 * 
 * Whenever you want to store or load an object, you can implement a
 * concrete hibernation and derive either from `SingleObjectHibernation`,
 * `IdentifiableObjectHibernation` or `CollectionHibernation`.
 */

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

///// Concrete implementations -- TODO separate module /////

template
    <typename ObjectType>
class RegistryValueHibernation
    : public IdentifiableObjectHibernation<const wchar_t*, ObjectType>
{
private:
    HKEY hKey;
    const wchar_t* subKey;
    DWORD regKeyType;
    DWORD regKeyFlags;
    DWORD bufferSize;

public:
    RegistryValueHibernation(
        HKEY hKey,
        const wchar_t* subKey,
        DWORD regKeyType,
        DWORD regKeyFlags,
        DWORD bufferSize
    )
    {
        this->hKey = hKey;
        this->subKey = subKey;
        this->regKeyType = regKeyType;
        this->regKeyFlags = regKeyFlags;
        this->bufferSize = bufferSize;
    }
    ObjectType load(const wchar_t* id)
    {
        ObjectType object;

        RegGetValue(this->hKey,
                    this->subKey,
                    id,
                    this->regKeyFlags,
                    NULL,
                    (PVOID)&object,
                    &this->bufferSize);

        return object;
    }

    const wchar_t* store(ObjectType object)
    {
        UNREFERENCED_PARAMETER(object);

        throw std::exception(
            "storing a registry value without a key does not make sense");
    }

    const wchar_t* store(const wchar_t* id, ObjectType object)
    {
        RegSetKeyValue(this->hKey,
                       this->subKey,
                       id,
                       this->regKeyType,
                       (LPVOID)&object,
                       this->bufferSize);

        return id;
    }
};