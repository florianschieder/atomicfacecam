#include "Hibernation.h"

#include "pch.h"

ConfigHibernation::ConfigHibernation()
{
    this->dwordHibernation =
        std::make_unique<RegistryValueHibernation<DWORD>>(
            HKEY_CURRENT_USER,
            L"SOFTWARE\\AtomicFaceCam\\",
            REG_DWORD, RRF_RT_DWORD);
}

Config ConfigHibernation::load()
{
    Config config = { 0 };

    // TODO Registry factory
    config.moveAmount = (unsigned short)
        this->dwordHibernation->load(L"CameraArrowKeyStep");
    config.resolution.height = (unsigned short)
        this->dwordHibernation->load(L"CameraHeight");
    config.resolution.width = (unsigned short)
        this->dwordHibernation->load(L"CameraWidth");
    config.fpsRate = (unsigned char)
        this->dwordHibernation->load(L"CameraFPSRate");

    return config;
}

void ConfigHibernation::store(Config config)
{
    this->dwordHibernation->store(L"CameraArrowKeyStep",
        config.moveAmount);
    this->dwordHibernation->store(L"CameraHeight",
        config.resolution.height);
    this->dwordHibernation->store(L"CameraWidth",
        config.resolution.width);
    this->dwordHibernation->store(L"CameraFPSRate",
        config.fpsRate);
}