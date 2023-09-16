#include <iostream>
#include "database.cpp"
#include <random>
#include <iomanip>
#include <string>
#include <vector>

struct Country : Data
{
    int population{-1};
    std::string name {"none"};
};

void print(const Country& country){
    std::cout <<std::setw(5 )<< country.name << " |total population: " << country.population << std::endl;
}

int selectInt(){
    Country country;
    return country.population;
}
int main(){
    size_t dbSize = 2;

    auto *_dataBase = new Database<Country>("CountryDB",dbSize);

    for (int i = 0; i<dbSize;i++){
        Country inputCountry;

        std::cout << "Country name:"; std::cin >> inputCountry.name;
        std::cout << "Population:"; std::cin >> inputCountry.population;
        _dataBase -> Add(i, inputCountry);
        std::cout << "Node added\n";
    }

    for (const Country& item : _dataBase -> GetAll())
        print(item);

    print(_dataBase->Get(_dataBase->FindNearest((std::string )"gg", [](Country country){return country.name;})));
    return 0;
}