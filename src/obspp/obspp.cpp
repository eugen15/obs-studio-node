#include "obspp.hpp"

namespace obs {

bool startup(std::string locale, std::string path)
{
    if (obs_initialized())
        throw std::logic_error("obs is already initialized");

    return obs_startup(locale.c_str(), path.c_str(), nullptr);
}

bool startup(std::string locale)
{
    return obs_startup(locale.c_str(), nullptr, nullptr);
}

void shutdown()
{
    obs_shutdown();
}

status_type status()
{
    return static_cast<obs::status_type>(!obs_initialized());
}

uint32_t version()
{
    return obs_get_version();
}

std::string locale()
{
    return obs_get_locale();
}

void locale(std::string locale)
{
    obs_set_locale(locale.c_str());
}

/* OBS namespace functionality */

void log_handler(log_handler_t handler)
{
}

log_handler_t log_handler()
{
    return nullptr;
}

}