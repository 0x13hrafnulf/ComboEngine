#include "LogManager.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace Combo
{
    std::shared_ptr<spdlog::logger> LogManager::s_ComboLogManager;
    std::shared_ptr<spdlog::logger> LogManager::s_ClientLogManager;
    

    void LogManager::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_ComboLogManager = spdlog::stdout_color_mt("COMBO");
        s_ComboLogManager->set_level(spdlog::level::trace);

        s_ClientLogManager = spdlog::stdout_color_mt("Application");
        s_ClientLogManager->set_level(spdlog::level::trace);
    }


}