#ifndef MOD
#define MOD
#include <string>

class Mod
{
protected:
	//PRIMARY RIFLE
	int Drain;
	std::string Polarity;

	double MaxAmmoCapacity;
	double MagazineCapacity;
	double ReloadSpeed;
	double AttackRate;
	double MultiShot;

	double CritChance;
	double CritMultiplier;
	double FactionMultiplier;

	double StatusDuration;
	double StatusChance;

	double Damage; 
	double Impact; 
	double Slash; 
	double Puncture; 

	double Heat; 
	double Cold;
	double Electricity;
	double Toxin;

	//MELEE EXCLUSIVE
	double ChannelEfficiency;
	double ChannelDamage;


public:
	Mod(int Drain, std::string Polarity, double MaxAmmoCapacity, double MagazineCapacity, double ReloadSpeed, double AttackRate,
		double MultiShot, double CritChance, double CritMultiplier, double FactionMultiplier,
		double StatusDuration, double StatusChance,
		double Damage, double Impact, double Slash, double Puncture,
		double Heat, double Cold, double Electricity, double Toxin);
	~Mod();
};

#endif