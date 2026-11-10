#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <windows.h>

using namespace std;
using namespace std::chrono_literals;

enum TrafficLightsState
{
    RED,
    YELLOW,
    GREEN
};

struct Address
{
    string country;
    string city;
    string street;
    double latitude;
    double longitude;
};

class TrafficLight
{
private:

    Address address;

public:

    TrafficLight(Address addr)
    {
        address = addr;
    }

    TrafficLightsState GetCurrentState()
    {
        auto now = chrono::system_clock::now();

        auto now_sec =
            chrono::floor<chrono::seconds>(
                now
            ).time_since_epoch();

        int seconds = (now_sec % 60).count();

        if (seconds >= 0 && seconds <= 5)
        {
            return TrafficLightsState::YELLOW;
        }
        else if (seconds >= 6 && seconds <= 29)
        {
            return TrafficLightsState::GREEN;
        }
        else
        {
            return TrafficLightsState::RED;
        }
    }

    void GetInfo()
    {
        cout << "\n";
        cout << "====================================\n";
        cout << "          TRAFFIC LIGHT\n";
        cout << "====================================\n";

        cout << "Country: " << address.country << endl;
        cout << "City: " << address.city << endl;
        cout << "Street: " << address.street << endl;

        cout << "Coordinates: "
            << address.latitude << ", "
            << address.longitude << endl;

        cout << "Current state: ";

        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

        switch (GetCurrentState())
        {
        case TrafficLightsState::RED:

            SetConsoleTextAttribute(
                console,
                FOREGROUND_RED | FOREGROUND_INTENSITY
            );

            cout << "RED";
            break;

        case TrafficLightsState::YELLOW:

            SetConsoleTextAttribute(
                console,
                FOREGROUND_RED |
                FOREGROUND_GREEN |
                FOREGROUND_INTENSITY
            );

            cout << "YELLOW";
            break;

        case TrafficLightsState::GREEN:

            SetConsoleTextAttribute(
                console,
                FOREGROUND_GREEN | FOREGROUND_INTENSITY
            );

            cout << "GREEN";
            break;
        }

        SetConsoleTextAttribute(
            console,
            FOREGROUND_RED |
            FOREGROUND_GREEN |
            FOREGROUND_BLUE
        );

        cout << endl;

        cout << "====================================\n";
    }
};

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Address address1 =
    {
        "Russia",
        "Moscow",
        "Festivalnaya Street",
        55.8570,
        37.4760
    };

    TrafficLight trafficLight(address1);

    while (true)
    {
        trafficLight.GetInfo();

        this_thread::sleep_for(23000ms);
    }

    return 0;
}