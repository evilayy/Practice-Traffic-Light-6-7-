#include "TrafficLight.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

TrafficLight::TrafficLight(const Address& address)
{
    this->address = address;
}

// Получение текущего состояния светофора
TrafficLightsState TrafficLight::GetCurrentState() const
{
    auto now = system_clock::now();

    auto seconds = duration_cast<std::chrono::seconds>(
        now.time_since_epoch()
    ).count();

    int currentSecond = seconds % 60;

    if (currentSecond >= 0 && currentSecond <= 5)
    {
        return YELLOW;
    }
    else if (currentSecond >= 6 && currentSecond <= 29)
    {
        return GREEN;
    }
    else
    {
        return RED;
    }
}

void TrafficLight::GetInfo() const
{
    cout << "Country: " << address.country << endl;
    cout << "City: " << address.city << endl;
    cout << "Street: " << address.street << endl;

    cout << "Coordinates: "
        << address.latitude << ", "
        << address.longitude << endl;

    cout << "Current state: ";

    switch (GetCurrentState())
    {
    case RED:
        cout << "RED" << endl;
        break;

    case YELLOW:
        cout << "YELLOW" << endl;
        break;

    case GREEN:
        cout << "GREEN" << endl;
        break;
    }

    cout << "------------------------" << endl;
}