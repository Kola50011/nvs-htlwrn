
#include <iostream>
#include <thread>
#include <clock.h>
#include <string>
#include "timeSlave.h"
#include "timeMaster.h"
#include "pipe.h"
#include "clipp.h"

using namespace clipp;
using namespace std;

int main(int argc, char *argv[])
{
    bool help = false;
    bool monoton = false;
    bool delay = false;
    int delay1{};
    int delay2{};
    bool rate = false;
    int rateM{1000};
    int rate1{1000};
    int rate2{1000};

    auto cli = (option("-h", "--help").set(help).doc("show this help"),
                option("-m").set(monoton).doc("monoton (kein Zurückstellen der Uhren)"),
                option("-d").set(delay).doc("Verzögerungen in ms (d.h. Latenz der Verbindung zu jeweiligen Slave)") & value("delay1", delay1) & value("delay2", delay2),
                option("-r").set(rate).doc("Abweichungen vom Sekundentakt in ms (der jeweiligen Uhr, d.h. Ungenauigkeit)") & value("rateM", rateM) & value("rate1", rate1) & value("rate2", rate2));

    if (!parse(argc, argv, cli) || help)
    {
        cout << make_man_page(cli, argv[0]);
        exit(0);
    }

    TimeSlave ts1("slave1", 0, 0, 1);
    TimeSlave ts2("slave2", 0, 0, 5);
    TimeMaster tm("master", 0, 0, 10);

    ts1.setTimeMonoton(monoton);
    ts2.setTimeMonoton(monoton);
    tm.setTimeMonoton(monoton);
    
    ts1.getChannel()->setLatency(delay1);
    ts2.getChannel()->setLatency(delay2);

    ts1.setClockSpeed(rate1);
    ts2.setClockSpeed(rate2);
    tm.setClockSpeed(rateM);
    
    tm.setChannel(1, ts1.getChannel());
    tm.setChannel(2, ts2.getChannel());

    thread t1{&TimeSlave::start, ref(ts1)};
    thread t2{&TimeSlave::start, ref(ts2)};
    thread m1{&TimeMaster::start, ref(tm)};

    t1.join();
    t2.join();
    m1.join();
}
