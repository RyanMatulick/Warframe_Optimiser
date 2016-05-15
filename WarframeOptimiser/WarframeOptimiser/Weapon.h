#ifndef WEAPON_H
#define WEAPON_H

#include <string>
class Weapon
{
protected:
	std::string Type;
	std::string Name;
	double Impact;
	double Puncture;
	double Slash;

	double Heat;
	double Toxin;
	double Cold;
	double Electricity;

	double Corrosive;
	double Radiation;
	double Viral;
	double Blast;
	double Gas;
	double Magnetic;


	double CritChance;
	double CritMultiplier;
	double Attackrate;
	double StatusChance;



public:
	Weapon(std::string Type, std::string Name, double Impact, double Puncture, double Slash,
		double Heat, double Toxin, double Cold, double Electricity,
		double Corrosive, double Radiation, double Viral, double Blast, double Gas, double Magnetic,
		double CritChance, double CritMultiplier, double StatusChance, double Attackrate); // initialises a Weapon Object 

	
	double CalculateDamage(int * ElementsArray, int Elementsize);
	virtual int * GetElements(int *Array, int size);
	virtual double TimeToKill(double RealHealth, double RealShields, double HealthDamage, double ShieldsDamage);
	
	~Weapon();


};

#endif