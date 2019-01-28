
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#pragma GCC diagnostic pop

int main() {
    // stdout_logger_st, stderr_logger_mt, stderr_logger_st  
    auto console = spdlog::stderr_color_mt("console");

    console->set_level(spdlog::level::alert);
    
    console->emerg("Welcome to spdlog!");
    console->alert("Welcome to spdlog!");
    console->critical("Welcome to spdlog!");
    console->error("Welcome to spdlog!");
    console->error("Welcome to spdlog!");
    console->warn("Welcome to spdlog!");
    console->notice("Welcome to spdlog!");
    console->info("Welcome {}!", "Maxi");
    console->info("Welcome to spdlog!");
    console->debug("Welcome to spdlog!");
    console->trace("Welcome to spdlog!");
}
