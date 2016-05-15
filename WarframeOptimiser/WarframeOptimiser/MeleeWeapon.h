#ifndef MELEEWEAPON
#define MELEEWEAPON
#include <string>
#include "Weapon.h"
class MeleeWeapon : public Weapon
{
	private:
		double ChannelingCost;
		double ChannelingDamage;
	public:
		MeleeWeapon(std::string iType, std::string iName, double iImpact, double iPuncture, double iSlash,
			double iHeat, double iToxin, double iCold, double iElectricity,
			double iCorrosive, double iRadiation, double iViral, double iBlast, double iGas, double iMagnetic,
			double iCritChance, double iCritMultiplier, double iStatusChance,
			double iAttackrate, double ChannelingCost, double ChannelingDamage);
		~MeleeWeapon();
	
		//Functions
		int * GetElements(int *Array, int size);
		double TimeToKill(double RealHealth, double RealShields, double HealthDamage, double ShieldsDamage);
};

#endif MELEEWEAPON

