#pragma once

#include <string>

using namespace std;

struct Address
{
    string country;
    string city;
    string street;
    double latitude;
    double longitude;
};

enum TrafficLightsState
{
    RED,
    YELLOW,
    GREEN
};

class TrafficLight
{
private:
    Address address;

public:
    TrafficLight(const Address& address);

    TrafficLightsState GetCurrentState() const;

    void GetInfo() const;
};
