#include <iostream>
#include <fstream>
#include <windows.h>


class ICar {
public:
	virtual ~ICar() {}
	virtual int GetEngineVolume() const = 0;
};

class BmwX3 : public ICar {
public:
	int GetEngineVolume() const {
		return 3;
	}
};
class BmwX5 : public ICar {
public:
	int GetEngineVolume() const {
		return 4;
	}
};

void ShowCarInfo(std::shared_ptr<ICar> car) {
	std::cout << car->GetEngineVolume();
}
class ICarFactory {
public:
	virtual ~ICarFactory() {}
	virtual std::shared_ptr<ICar> CreateCar(int expectedEngineVolume) const = 0;
};
class BmwFactory : public ICarFactory {
public:
	std::shared_ptr<ICar> CreateCar(int expectedEngineVolume) const {
		if (expectedEngineVolume == 3) {
			return std::make_shared<BmwX3>();
		}
		else if (expectedEngineVolume == 4) {
			return std::make_shared<BmwX5>();
		}
		else {
			throw std::runtime_error("Can't produce the car with expected engine volume");
		}
	}
};
class AbstractCarFactory {
public:
	std::shared_ptr<ICarFactory> CreateFactory() {
		return std::make_shared<BmwFactory>();
	}
};
int main()
{
	AbstractCarFactory carFactory;
	std::shared_ptr<ICarFactory> specificCarFactory = carFactory.CreateFactory();
	std::shared_ptr<ICar> car = specificCarFactory->CreateCar(10);
	ShowCarInfo(car);
}
