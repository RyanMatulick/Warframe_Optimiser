#ifndef STRUCTS
#define STRUCTS
#include <string>

struct SResistances
{
	double Slash;
	double Impact;
	double Puncture;

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

	char Type;
	double Amount;
};

extern SResistances Proto;
extern SResistances Standard;
extern SResistances NoShields;
extern SResistances Flesh;
extern SResistances ClonedFlesh;
extern SResistances Infested;
extern SResistances InfestedFlesh;
extern SResistances Machinery;
extern SResistances Robotic;
extern SResistances Fossilized;
extern SResistances InfestedSinew;
extern SResistances Alloy;
extern SResistances Ferrite;
extern SResistances NoArmour;

struct Enemy
{
	int BaseHealth;
	double  CurrentHealth;
	int BaseArmour;
	double CurrentArmour;
	int BaseShields;
	double  CurrentShields;
	int BaseLevel;
	int CurrentLevel;
	std::string Faction;

};
extern Enemy CurrentEnemy;

struct WeaponMod
{
	//PRIMARY RIFLE
	int Drain;
	std::string Polarity;

	double MaxAmmoCapacity = 1;
	double MagazineCapacity = 1; // done
	double ReloadSpeed = 1; // done
	double AttackRate = 1; // done
	double MultiShot = 1;//////////////////

	double CritChance = 1; // done
	double CritMultiplier = 1; // done
	double FactionMultiplier = 1;//////////////////

	double StatusDuration = 1;/////////////////
	double StatusChance = 1;///////////////////

	double Damage = 1; // done
	double Impact = 1; // done
	double Slash = 1; // done
	double Puncture = 1; // done

	double Heat = 0; // done
	double Cold = 0;// done
	double Electricity = 0;// done
	double Toxin = 0;// done

					 //MELEE EXCLUSIVE
	double ChannelEfficiency = 1;
	double ChannelDamage = 1;
};

extern WeaponMod Mod;

extern SResistances TargetArmourType;
extern SResistances TargetHealthType;
extern SResistances TargetShieldsType;



#endif