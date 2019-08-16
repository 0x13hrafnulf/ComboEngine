cmake_minimum_required(VERSION 3.3)

set (SPDLOG_SOURCES 
"spdlog/include/spdlog/spdlog.h"
"spdlog/include/spdlog/sinks/stdout_color_sinks.h"
"spdlog/icnlude/spdlog/fmt/ostr.h")

add_library(spdlog $(SPDLOG_SOURCES))