#pragma once

#include "Hibernation/Hibernations.h"
#include "Config.h"

class ConfigHibernation
    : public SingleObjectHibernation<Config>
{
public:
    ConfigHibernation();
    Config load();
    void store(Config config);
    
private:
    std::unique_ptr<::RegistryValueHibernation<DWORD>> dwordHibernation;
};