
#include <iostream>
#include <asio.hpp>
#include "clipp.h"
#include <cstdint>
#include <netinet/in.h>

#include "timeutils.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#pragma GCC diagnostic pop

using namespace std;
using namespace asio::ip;
using namespace clipp;

int main(int argc, char *argv[])
{
    string port = "1113";
    bool help = false;

    auto cli = (option("-p").doc("server port") & value("port", port),
                option("-h", "--help").doc("help").set(help));
    if (!parse(argc, argv, cli) || help)
    {
        cout << make_man_page(cli, argv[0]);
        exit(0);
    }

    auto console = spdlog::stderr_color_mt("console");
    console->set_level(spdlog::level::err);

    tcp::iostream strm{"localhost", port};
    strm.expires_after(5s);

    if (strm)
    {
        uint32_t data;
        strm.read(reinterpret_cast<char *>(&data), sizeof(data));
        cout << data << endl;
        data = ntohl(data);
        data -= 2208988800;
        
        if (strm)
        {
            chrono::time_point<chrono::system_clock> now{chrono::seconds{data}};
            cout << now << endl;
        }
        else
        {
            console->error(strm.error().message());
        }
        strm.close();
    }
    else
    {
        console->error("Error - Could not connect to server!");
    }
}
