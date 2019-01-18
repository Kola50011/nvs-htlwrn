
#include <iostream>
#include <asio.hpp>
#include "clipp.h"
#include <chrono>
#include <string>
#include <cstdlib>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#pragma GCC diagnostic pop

using namespace std;
using namespace asio::ip;
using namespace clipp;

string getDateTime() {
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
    std::string str(buffer);

    return str;
}

int main(int argc, char *argv[])
{
    short unsigned int port;
    bool help = false;

    auto cli = (required("-p").doc("server port") & value("port", port),
                option("-h", "--help").doc("help").set(help));
    if (!parse(argc, argv, cli) || help) {
        cout << make_man_page(cli, argv[0]);
        exit(0);
    }

    auto console = spdlog::stderr_color_mt("console");
    console->set_level(spdlog::level::err);

    asio::io_context ctx;
    tcp::endpoint ep{tcp::v4(), port};
    tcp::acceptor acceptor{ctx, ep};
    acceptor.listen();
    tcp::socket sock{ctx};

    while (true) {
        acceptor.accept(sock);
        tcp::iostream strm{std::move(sock)};

        string data;
        strm >> data;
        strm << getDateTime();
        strm.close();
    }

}