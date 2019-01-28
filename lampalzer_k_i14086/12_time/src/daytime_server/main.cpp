
#include <iostream>
#include <asio.hpp>
#include "clipp.h"
#include <chrono>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <netinet/in.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#pragma GCC diagnostic pop

using namespace std;
using namespace asio::ip;
using namespace clipp;

uint32_t getDateTime()
{
    chrono::duration d = chrono::system_clock::now().time_since_epoch();
    uint32_t seconds = chrono::duration_cast<chrono::seconds>(d).count();
    seconds += 2208988800;
    return ntohl(seconds);
}

int main(int argc, char *argv[])
{
    short unsigned int port;
    bool help = false;

    auto cli = (required("-p").doc("server port") & value("port", port),
                option("-h", "--help").doc("help").set(help));
    if (!parse(argc, argv, cli) || help)
    {
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

    while (true)
    {
        acceptor.accept(sock);
        tcp::iostream strm{std::move(sock)};

        if (strm)
        {
            uint32_t data = getDateTime();
            strm.write(reinterpret_cast<char *>(&data), sizeof(data));
            strm.close();
        }
        else
        {
            console->error(strm.error().message());
        }
    }
}