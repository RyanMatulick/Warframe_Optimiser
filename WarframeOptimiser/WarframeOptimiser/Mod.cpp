#include "stdafx.h"
#include "Mod.h"
#include <string>

Mod::Mod(int iDrain, std::string iPolarity, double iMaxAmmoCapacity, double iMagazineCapacity, double iReloadSpeed, double iAttackRate,
	double iMultiShot, double iCritChance, double iCritMultiplier, double iFactionMultiplier,
	double iStatusDuration, double iStatusChance,
	double iDamage, double iImpact, double iSlash, double iPuncture,
	double iHeat, double iCold, double iElectricity, double iToxin)
{
	int Drain = iDrain;
	std::string Polarity = iPolarity;
							
	double MaxAmmoCapacity = 1 + iMaxAmmoCapacity;
	double MagazineCapacity = 1 + iMagazineCapacity;
	double ReloadSpeed = 1 + iReloadSpeed;
	double AttackRate = 1 + iAttackRate;
	double MultiShot = 1 + iMultiShot;
	
	double CritChance = 1 + iCritChance;
	double CritMultiplier = 1 + iCritMultiplier;
	double FactionMultiplier = 1 + iFactionMultiplier;
	
	double StatusDuration = 1 + iStatusDuration;
	double StatusChance = 1 + iStatusChance;
	
	double Damage = 1 + iDamage;
	double Impact = 1 + iImpact;
	double Slash = 1 + iSlash;
	double Puncture = 1 + iPuncture;
	
	double Heat = 0 + iHeat;
	double Cold = 0 + iCold;
	double Electricity = 0 + iElectricity;
	double Toxin = 0 + iToxin;
}


Mod::~Mod()
{
}
