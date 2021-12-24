#pragma once

#include "IdentifiableObjectHibernation.h"

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
        DWORD regKeyFlags
    )
    {
        UNREFERENCED_PARAMETER(bufferSize);
        this->hKey = hKey;
        this->subKey = subKey;
        this->regKeyType = regKeyType;
        this->regKeyFlags = regKeyFlags;
        this->bufferSize = sizeof(ObjectType);
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