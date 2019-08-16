#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

//Engine macros
#define COMBO_TRACE_LOG(...) ::LogManager::GetComboLogManager()->trace(__VA_ARGS__)
#define COMBO_INFO_LOG(...)  ::LogManager::GetComboLogManager()->info(__VA_ARGS__)
#define COMBO_WARN_LOG(...)  ::LogManager::GetComboLogManager()->warn(__VA_ARGS__)
#define COMBO_ERROR_LOG(...) ::LogManager::GetComboLogManager()->error(__VA_ARGS__)
#define COMBO_FATAL_LOG(...) ::LogManager::GetComboLogManager()->critical(__VA_ARGS__)

//Client macros
#define CLIENT_TRACE_LOG(...) ::LogManager::GetClientLogManager()->trace(__VA_ARGS__)
#define CLIENT_INFO_LOG(...)  ::LogManager::GetClientLogManager()->info(__VA_ARGS__)
#define CLIENT_WARN_LOG(...)  ::LogManager::GetClientLogManager()->warn(__VA_ARGS__)
#define CLIENT_ERROR_LOG(...) ::LogManager::GetClientLogManager()->error(__VA_ARGS__)
#define CLIENT_FATAL_LOG(...) ::LogManager::GetClientLogManager()->critical(__VA_ARGS__)


namespace Combo {
class LogManager
{
    public:


    static void Init();
    
    static std::shared_ptr<spdlog::logger>& GetComboLogManager() { return s_ComboLogManager; }
    static std::shared_ptr<spdlog::logger>& GetClientLogManager() { return s_ClientLogManager; }

    private:

    static std::shared_ptr<spdlog::logger> s_ComboLogManager;
    static std::shared_ptr<spdlog::logger> s_ClientLogManager;

};

}
