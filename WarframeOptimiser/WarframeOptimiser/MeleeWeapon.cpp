#include "stdafx.h"
#include "Weapon.h"
#include "MeleeWeapon.h"
#include "Structs.h"
#include <string>

MeleeWeapon::MeleeWeapon(std::string iType, std::string iName, double iImpact, double iPuncture, double iSlash,
	double iHeat, double iToxin, double iCold, double iElectricity,
	double iCorrosive, double iRadiation, double iViral, double iBlast, double iGas, double iMagnetic,
	double iCritChance, double iCritMultiplier, double iStatusChance,
	double iAttackrate, double iChannelingCost, double iChannelingDamage)
	: Weapon(iType, iName, iImpact, iPuncture, iSlash,
	iHeat, iToxin, iCold, iElectricity,
	iCorrosive, iRadiation, iViral, iBlast, iGas, iMagnetic,
	iCritChance, iCritMultiplier, iStatusChance, iAttackrate)
{
	ChannelingCost = iChannelingCost;
	ChannelingDamage = iChannelingDamage;
}


int * MeleeWeapon::GetElements(int *Array, int size) // Only for melee weapons
{
	static int ReturnArray[8];
	int CheckArray[4] = { 0,0,0,0 };
	for (int i = 0; i < size; i++)
	{
		if ((Array[i] == 10 || Array[i] == 14) && CheckArray[0] == 0)
		{
			*(ReturnArray + i) = 1; // Heat
			CheckArray[0]++;
		}
		else if ((Array[i] == 11 || Array[i] == 15) && CheckArray[2] == 0)
		{
			ReturnArray[i] = 2; // Cold
			CheckArray[1]++;
		}
		else if ((Array[i] == 12 || Array[i] == 16) && CheckArray[2] == 0)
		{
			ReturnArray[i] = 3; // Toxin
			CheckArray[2]++;
		}
		else if ((Array[i] == 13 || Array[i] == 17 || Array[i] == 18) && CheckArray[3] == 0)
		{
			ReturnArray[i] = 4; // Electricity
			CheckArray[3]++;
		}
		else ReturnArray[i] = 0;
	}
	return ReturnArray;
}

double MeleeWeapon::TimeToKill(double RealHealth, double RealShields, double HealthDamage, double ShieldsDamage)
{
	double Score = RealHealth / HealthDamage + RealShields / ShieldsDamage;
	double CalcTimeToKill = Score / (Attackrate*Mod.AttackRate);
	return CalcTimeToKill;
}

MeleeWeapon::~MeleeWeapon()
{
}
