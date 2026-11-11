#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <windows.h>
#include <nlohmann/json.hpp>

#include "TrafficLight.h"

using namespace std;
using json = nlohmann::json;

// Функция чтения адреса светофора из JSON-файла
Address ReadAddressFromFile(const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        throw runtime_error("Cannot open file: " + filename);
    }

    json data;
    file >> data;

    Address address;

    address.country = data.at("country").get<string>();
    address.city = data.at("city").get<string>();
    address.street = data.at("street").get<string>();
    address.latitude = data.at("latitude").get<double>();
    address.longitude = data.at("longitude").get<double>();

    return address;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    try
    {
        // Чтение данных из трех JSON-файлов
        Address address1 = ReadAddressFromFile("TrafficLight1.json");
        Address address2 = ReadAddressFromFile("TrafficLight2.json");
        Address address3 = ReadAddressFromFile("TrafficLight3.json");

        TrafficLight light1(address1);
        TrafficLight light2(address2);
        TrafficLight light3(address3);

        vector<TrafficLight> trafficLights =
        {
            light1,
            light2,
            light3
        };

        // Мониторинг светофоров
        while (true)
        {
            system("cls");

            cout << "TRAFFIC LIGHT MONITORING" << endl;
            cout << "========================" << endl;

            for (size_t i = 0; i < trafficLights.size(); i++)
            {
                cout << "\nTraffic Light #" << i + 1 << endl;
                trafficLights[i].GetInfo();
            }

            this_thread::sleep_for(chrono::seconds(23));
        }
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}