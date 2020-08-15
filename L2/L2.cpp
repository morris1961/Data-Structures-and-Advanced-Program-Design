#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
using namespace std;

class Entity
{
protected:
  string id;
  bool isOn; 
  bool isSer; // means nothing if isOn == false
  double lon;
  double lat;
public: 
  Entity(string id, bool isOn, bool isSer, double lon, double lat);
  virtual void print();
};

Entity::Entity(string id, bool isOn, bool isSer, double lon, double lat)
  : id(id), isOn(isOn), isSer(isSer), lon(lon), lat(lat)
{
}

void Entity::print()
{
  cout << this->id << ": " << this->isOn << " " << this->isSer
       << " (" << this->lon << ", " << this->lat << ")" << endl;
}

class Car : public Entity
{
private:
public:
	Car(string id, bool isOn, bool isSer, double lon, double lat);
	void print();
};

Car::Car(string id, bool isOn, bool isSer, double lon, double lat)
: Entity(id, isOn, isSer, lon, lat)
{
}

void Car::print()
{
	cout << this->id;
	if(this->isOn)
	{
		if(this->isSer)
			cout << ": in-service";
		else
			cout << ": empty";
		cout << " (" << this->lon << ", " << this->lat << ")" << endl;
	}
	else
		cout << ": offline";
		
}

class Passenger : public Entity
{
private:
public:
	Passenger(string id, bool isOn, bool isSer, double lon, double lat);
	void print();
};

Passenger::Passenger(string id, bool isOn, bool isSer, double lon, double lat)
: Entity(id, isOn, isSer, lon, lat)
{
}

void Passenger::print()
{
	cout << this->id;
	if(this->isOn)
	{
		if(this->isSer)
			cout << ": in-service";
		else
			cout << ": waiting";
		cout << " (" << this->lon << ", " << this->lat << ")" << endl;
	}
	else
		cout << ": offline";		
}

template <typename type>
class EntityArray
{
protected:
	vector<type> entities;
public:
  EntityArray();
  // EntityArray(const EntityArray& ca);  // not needed
  // operator=(const EntityArray& ca); // in this problem
  ~EntityArray();
  void add(string id, bool isOn, bool isSer, double lon, double lat);
  void print() noexcept;
};


template <typename type>
EntityArray<type>::EntityArray()
{

}

template <typename type>
EntityArray<type>::~EntityArray()
{

}

template <typename type>
void EntityArray<type>::add(string id, bool isOn, bool isSer, double lon, double lat)
{
	type t(id, isOn, isSer, lon, lat);
	entities.push_back(t);
}

template <typename type>
void EntityArray<type>::print() noexcept
{
	for(int i = 0; i < this->entities.size(); i++)
	{
		this->entities[i].print();
	}
}

//class CarArray : public EntityArray
//{
//public:
//  void add(string id, bool isOn, bool isSer, double lon, double lat);
//};
//
//void CarArray::add(string id, bool isOn, bool isSer, double lon, double lat)
//{
//	entityPtr[cnt] = new Car(id, isOn, isSer, lon, lat);
//	cnt++;
//}
//
//class PassengerArray : public EntityArray
//{
//public:
//  void add(string id, bool isOn, bool isSer, double lon, double lat);
//};
//
//void PassengerArray::add(string id, bool isOn, bool isSer, double lon, double lat)
//{
//	entityPtr[cnt] = new Passenger(id, isOn, isSer, lon, lat);
//	cnt++;
//}


int main()
{
  EntityArray<Car> ca;
  ca.add("5HE-313", true, true, 0, 0);  // 5HE-313: 1 1 (0, 0)
  ca.add("LPA-039", true, false, 1, 1); // LPA-039: 1 0 (1, 1)
  ca.print();
  
  EntityArray<Passenger> pa;
  pa.add("B90705023", true, true, 0, 0);  // B90705023: 1 1 (0, 0)
  pa.add("R94725008", true, false, 1, 1); // R94725008: 1 0 (1, 1)
  pa.print();
  
  return 0;
}
