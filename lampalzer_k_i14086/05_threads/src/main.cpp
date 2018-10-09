
#include <iostream>
#include <thread>
#include <string>
#include <random>
#include <unistd.h>
#include <iomanip>
#include  <sstream>

using namespace std;

class Car
{
  private:
    string name;
    double totalTime;
  public:
    Car(string _name);
    ~Car();
    void operator()();
    double getTime();
};

Car::Car(string _name)
{
    name = _name;
}

Car::~Car()
{
}

void Car::operator()()
{
    ostringstream buf;
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{1, 2};

    int i = 0;
    while (i < 10)
    {
        double time = dis(gen);
        totalTime += time;
        usleep(time * 1000 * 1000);
        i++;
        buf << i << " " << name << " " << setprecision(3) << time << "s" << endl;
        cout << buf.str() << flush;
        buf.str(""); 
    }
}

double Car::getTime() {
    return totalTime;
}

int main()
{
    Car car1("car1");
    Car car2("car2");

    thread t1{&Car::operator(), ref(car1)};
    thread t2{&Car::operator(), ref(car2)};

    t1.join();
    t2.join();

    cout << car1.getTime() << endl;
    cout << car2.getTime() << endl;
}
