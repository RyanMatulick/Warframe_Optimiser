#include "stdafx.h"
#include <iostream>
#include "Weapon.h"
#include "Structs.h"

#include "MeleeWeapon.h"
//				Impact
Weapon::Weapon(std::string iType, std::string iName, double iImpact, double iPuncture, double iSlash,
	double iHeat, double iToxin, double iCold, double iElectricity,
	double iCorrosive, double iRadiation, double iViral, double iBlast, double iGas, double iMagnetic,
	double iCritChance, double iCritMultiplier, double iStatusChance, double iAttackrate)
{
	Type = iType;
	Name = iName;

	Impact = iImpact;
	Puncture = iPuncture;
	Slash = iSlash;
	
	Heat = iHeat;
	Toxin = iToxin;
	Cold = iCold;
	Electricity = iElectricity;
	
	Corrosive = iCorrosive;
	Radiation = iRadiation;
	Viral = iViral;
	Blast = iBlast;
	Gas = iGas;
	Magnetic = iMagnetic;
	
	CritChance = iCritChance;
	CritMultiplier = iCritMultiplier;
	Attackrate = iAttackrate;
	StatusChance = iStatusChance;

}

int * Weapon::GetElements(int *Array, int size)
{
	return 0;
}

using namespace std;

double Weapon::CalculateDamage(int * ElementsArray, int Elementsize)
{
	///////////////////////////////TO BE PUT IN SOME FORM OF INITIALISATION ///////////////////////////
	double RealArmour = CurrentEnemy.CurrentArmour;
	//cout << "Real Armour: " << RealArmour << endl;
	//Calculate target specific HEALTH values
	double RealHealth = CurrentEnemy.CurrentHealth;
	//cout << "Real Health: " << RealHealth << endl;
	//Calculate target specific SHIELDS values
	double RealShields = CurrentEnemy.CurrentShields;
	//cout << "Real Shields: " << RealShields << endl;

	// WORK OUT ELEMENTS /////////////////////////////////////////////////////////////////////////////////////////////////////
	//PrintArray(Elementsize, ElementsArray,'o');
	static int FirstElement = 0;
	static int SecondElement = 0;
	static int GotFirst = 0;

	bool CombElement[6] = { 0,0, 0, 0, 0, 0 };
	// Find Element Combinations
	for (int i = 0; i < Elementsize; i++)
	{

		if ((ElementsArray[i] == 1 || ElementsArray[i] == 2 || ElementsArray[i] == 3 || ElementsArray[i] == 4) && GotFirst == 0)
		{
			//cout << "In First: ";
			FirstElement = ElementsArray[i];
			GotFirst = 1;
		}
		else if ((ElementsArray[i] == 1 || ElementsArray[i] == 2 || ElementsArray[i] == 3 || ElementsArray[i] == 4))
		{
			//cout << "In Second: ";
			SecondElement = ElementsArray[i];
		}
		//std::cout << "\tElement " << i << ": " << ElementsArray[i] << " First Element: " << FirstElement << " Second Element: " << SecondElement << endl;
		if (FirstElement != 0 && SecondElement != 0)
		{
			if ((FirstElement == 1 && SecondElement == 2) || (FirstElement == 2 && SecondElement == 1))
			{
				CombElement[0] = true; //Blast

			}
			else if ((FirstElement == 1 && SecondElement == 3) || (FirstElement == 3 && SecondElement == 1))
			{
				CombElement[1] = true; //Gas
			}
			else if ((FirstElement == 1 && SecondElement == 4) || (FirstElement == 4 && SecondElement == 1))
			{
				CombElement[2] = true; //Radiation
			}
			else if ((FirstElement == 2 && SecondElement == 3) || (FirstElement == 3 && SecondElement == 2))
			{
				CombElement[3] = true; //Viral
			}
			else if ((FirstElement == 2 && SecondElement == 4) || (FirstElement == 4 && SecondElement == 2))
			{
				CombElement[4] = true; //Magnetic
			}
			else if ((FirstElement == 3 && SecondElement == 4) || (FirstElement == 4 && SecondElement == 3))
			{
				CombElement[5] = true; //Corrosive
			}
			FirstElement = 0;
			SecondElement = 0;
			GotFirst = 0;
		}
	}
	FirstElement = 0;
	SecondElement = 0;
	GotFirst = 0;
	//cout << "\t" << CombElement[0] << " " << CombElement[1] << " " << CombElement[2] << " " << CombElement[3] << " " << CombElement[4] << " " << CombElement[5] << "\t"<< endl;;


	// BASE ELEMENTS
	double tHeat = (Heat + (Slash + Impact + Puncture + Heat) * Mod.Heat);
	double tCold = (Cold + (Slash + Impact + Puncture + Cold) * Mod.Cold);
	double tToxin = (Toxin + (Slash + Impact + Puncture + Toxin) * Mod.Toxin);
	double tElectricity = (Electricity + (Slash + Impact + Puncture + Electricity) * Mod.Electricity);

	double tBlast = (tHeat + tCold);
	double tGas = (tHeat + tToxin);
	double tRadiation = (tHeat + tElectricity);
	double tViral = (tCold + tToxin);
	double tMagnetic = (tCold + tElectricity);
	double tCorrosive = (tElectricity + tToxin);
	// SHIELD ELEMENTS
	double ShieldsHeat = tHeat*(1 + TargetShieldsType.Heat);
	double ShieldsCold = tCold*(1 + TargetShieldsType.Cold);
	double ShieldsElectricity = tElectricity*(1 + TargetShieldsType.Electricity);
	double ShieldsToxin = tToxin*(1 + TargetShieldsType.Toxin);

	double ShieldsBlast = 0;
	double ShieldsGas = 0;
	double ShieldsRadiation = 0;
	double ShieldsViral = 0;
	double ShieldsMagnetic = 0;
	double ShieldsCorrosive = 0;

	// HEALTH ELEMENTS  -- OPTIMISE ARMOUR
	double HealthHeat = tHeat*(1 + TargetHealthType.Heat)*(1 + TargetArmourType.Heat) / (1 + (RealArmour*(1 - TargetArmourType.Heat)) / 300);
	double HealthCold = tCold*(1 + TargetHealthType.Cold)*(1 + TargetArmourType.Cold) / (1 + (RealArmour*(1 - TargetArmourType.Cold)) / 300);
	double HealthElectricity = tElectricity*(1 + TargetHealthType.Electricity)*(1 + TargetArmourType.Electricity) / (1 + (RealArmour*(1 - TargetArmourType.Electricity)) / 300);
	double HealthToxin = tToxin*(1 + TargetHealthType.Toxin)*(1 + TargetArmourType.Toxin) / (1 + (RealArmour*(1 - TargetArmourType.Toxin)) / 300);

	double HealthBlast = 0;
	double HealthGas = 0;
	double HealthRadiation = 0;
	double HealthViral = 0;
	double HealthMagnetic = 0;
	double HealthCorrosive = 0;

	if (CombElement[0] == true)//Blast
	{
		HealthBlast = tBlast*(1 + TargetHealthType.Blast)*(1 + TargetArmourType.Blast) / (1 + (RealArmour*(1 - TargetArmourType.Blast)) / 300);
		ShieldsBlast = tBlast*(1 + TargetShieldsType.Blast);

		ShieldsHeat = 0;
		ShieldsCold = 0;

		HealthHeat = 0;
		HealthCold = 0;
	}
	if (CombElement[1] == true)//Gas
	{
		HealthGas = tGas*(1 + TargetHealthType.Gas)*(1 + TargetArmourType.Gas) / (1 + (RealArmour*(1 - TargetArmourType.Gas)) / 300);
		ShieldsGas = tGas*(1 + TargetShieldsType.Gas);
		ShieldsHeat = 0;
		ShieldsToxin = 0;

		HealthHeat = 0;
		HealthToxin = 0;
	}
	if (CombElement[2] == true)//Radiation
	{
		HealthRadiation = tRadiation*(1 + TargetHealthType.Radiation)*(1 + TargetArmourType.Radiation) / (1 + (RealArmour*(1 - TargetArmourType.Radiation)) / 300);
		ShieldsRadiation = tRadiation*(1 + TargetShieldsType.Radiation);

		ShieldsHeat = 0;
		ShieldsElectricity = 0;

		HealthHeat = 0;
		HealthElectricity = 0;
	}
	if (CombElement[3] == true)//Viral
	{
		HealthViral = tViral*(1 + TargetHealthType.Viral)*(1 + TargetArmourType.Viral) / (1 + (RealArmour*(1 - TargetArmourType.Viral)) / 300);
		ShieldsViral = tViral*(1 + TargetShieldsType.Viral);

		ShieldsCold = 0;
		ShieldsToxin = 0;

		HealthCold = 0;
		HealthToxin = 0;
	}
	if (CombElement[4] == true)//Magnetic
	{
		HealthMagnetic = tMagnetic*(1 + TargetHealthType.Magnetic)*(1 + TargetArmourType.Magnetic) / (1 + (RealArmour*(1 - TargetArmourType.Magnetic)) / 300);
		ShieldsMagnetic = tMagnetic*(1 + TargetShieldsType.Magnetic);

		ShieldsCold = 0;
		ShieldsElectricity = 0;

		HealthCold = 0;
		HealthElectricity = 0;
	}
	if (CombElement[5] == true)//Corrosive
	{
		HealthCorrosive = tCorrosive*(1 + TargetHealthType.Corrosive)*(1 + TargetArmourType.Corrosive) / (1 + (RealArmour*(1 - TargetArmourType.Corrosive)) / 300);
		ShieldsCorrosive = tCorrosive*(1 + TargetShieldsType.Corrosive);

		ShieldsToxin = 0;
		ShieldsElectricity = 0;

		HealthToxin = 0;
		HealthElectricity = 0;
	}

	//cout << " HealthHeat: " << HealthHeat*Mod.Damage << " HealthCold: " << HealthCold*Mod.Damage << " HealthToxin: " << HealthToxin*Mod.Damage << " HealthElectricity: " << HealthElectricity*Mod.Damage << endl;
	//cout << " HealthBlast: " << HealthBlast*Mod.Damage << " HealthCorrosive: " << HealthCorrosive*Mod.Damage << " HealthGas: " << HealthGas*Mod.Damage << " HealthMagnetic: " << HealthMagnetic*Mod.Damage << " HealthRadiation: " << HealthRadiation*Mod.Damage << " HealthViral: " << HealthViral*Mod.Damage << endl;
	//cout << " ShieldsHeat: " << ShieldsHeat*Mod.Damage << " ShieldsCold: " << ShieldsCold*Mod.Damage << " ShieldsToxin: " << ShieldsToxin*Mod.Damage << " ShieldsElectricity: " << ShieldsElectricity*Mod.Damage << endl;
	//cout << " ShieldsBlast: " << ShieldsBlast*Mod.Damage << " ShieldsCorrosive: " << ShieldsCorrosive*Mod.Damage << " ShieldsGas: " << ShieldsGas*Mod.Damage << " ShieldsMagnetic: " << ShieldsMagnetic*Mod.Damage << " ShieldsRadiation: " << ShieldsRadiation*Mod.Damage << " ShieldsViral: " << ShieldsViral*Mod.Damage << endl;



	double ShieldElemental = ShieldsHeat + ShieldsCold + ShieldsElectricity + ShieldsToxin + ShieldsBlast + ShieldsGas + ShieldsRadiation + ShieldsViral + ShieldsMagnetic + ShieldsCorrosive;

	double HealthElemental = HealthHeat + HealthCold + HealthElectricity + HealthToxin + HealthBlast + HealthGas + HealthRadiation + HealthViral + HealthMagnetic + HealthCorrosive;





	// CRIT CALCULATIONS /////////////////////////////////////////////////////////////////////////////////
	//Extra Modifiers
	double HeadShotRate = 0.4;
	double iCritChance = CritChance*Mod.CritChance;
	double iCritMultiplier = CritMultiplier*Mod.CritMultiplier;
	//double HeadShotMult = 2;
	double CritModifier;
	if (CritChance <= 1)
	{	//SIMPLE ADDITION OF PARTS
		//double HeadCrit = CritChance*CritMultiplier*HeadShotRate * 2 * HeadShotMult;
		//double HeadShot = (1 - CritChance)*HeadShotMult*HeadShotRate;
		//double Crit = CritChance*CritMultiplier*(1 - HeadShotRate);
		//double Hit = (1 - CritChance)*(1 - HeadShotRate);
		//double CritModifier2 = HeadCrit + HeadShot + Crit + Hit;

		// RYAN SIMPLIFIED FORMULA if HeadShotMult = 2
		//double RyanModifier = CritChance*CritMultiplier*(3*HeadShotRate +1) + (1-CritChance)*(HeadShotRate+1);

		// SIMPLIFIED FORMULA if HeadShotMult = 2
		CritModifier = (1 + HeadShotRate) * (1 + iCritChance*(iCritMultiplier*(3 - 2 / (1 + HeadShotRate)) - 1));

		//cout << "\nCritModifier Check: " << CritModifier2 << " Equation:" << CritModifier << " My Try: " << RyanModifier << endl;
		//cout << "CritModifier 1: " << CritModifier << endl;

	}
	else if (iCritChance > 1)
	{
		// SIMPLE ADDITION OF PARTS
		//double RedHeadCrit = (CritChance-1)*(2 * CritMultiplier - 1)*HeadShotRate*HeadShotMult * 2;
		//double HeadCrit = CritMultiplier*HeadShotRate * 2 * HeadShotMult;
		//double RedCrit = (CritChance-1)*(2 * CritMultiplier - 1)*(1 - HeadShotRate);
		//double Crit = CritMultiplier*(1 - HeadShotRate);

		//double CritModifier3 = RedHeadCrit + HeadCrit + RedCrit + Crit;

		// SIMPLIFIED FORMULA if HeadShotMult = 2
		CritModifier = (3 * HeadShotRate + 1)*((iCritChance - 1)*(2 * iCritMultiplier - 1) + iCritMultiplier);
		//Wiki Formula is Incorrect
		//double WikiRedCrit = (1 + 3 * HeadShotRate) *(1 + CritChance *(CritMultiplier - 1));


		//cout << "\nCritModifier Check: " << CritModifier3 << " Equation 2: " << CritModifier << endl;
		//cout << " Equation 2: " << CritModifier << endl;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//Base Physical 
	double tSlash = Slash*Mod.Slash;
	double tImpact = Impact*Mod.Impact;
	double tPuncture = Puncture*Mod.Puncture;
	double DamageModifier = (CritModifier*Mod.FactionMultiplier*Mod.Damage);
	// SHIELDS ---------------------
	//Calculate Target specific Received DAMAGE values
	double ShieldsSlash = tSlash*(1 + TargetShieldsType.Slash);
	double ShieldsImpact = tImpact*(1 + TargetShieldsType.Impact);
	double ShieldsPuncture = tPuncture*(1 + TargetShieldsType.Puncture);

	//DAMAGE TO SHIELDS
	double ShieldBaseDamage = (ShieldsSlash + ShieldsImpact + ShieldsPuncture + ShieldElemental);
	double ShieldsDamage = ShieldBaseDamage*DamageModifier;

	//HEALTH -----------------------

	//Calculate Target specific Received DAMAGE values
	double HealthSlash = tSlash*(1 + TargetHealthType.Slash)*(1 + TargetArmourType.Slash) / (1 + (RealArmour*(1 - TargetArmourType.Slash)) / 300);
	double HealthImpact = tImpact*(1 + TargetHealthType.Impact)*(1 + TargetArmourType.Impact) / (1 + (RealArmour*(1 - TargetArmourType.Impact)) / 300);
	double HealthPuncture = tPuncture*(1 + TargetHealthType.Puncture)*(1 + TargetArmourType.Puncture) / (1 + (RealArmour*(1 - TargetArmourType.Puncture)) / 300);

	//DAMAGE TO HEALTH
	double HealthBaseDamage = (HealthSlash + HealthImpact + HealthPuncture + HealthElemental);
	//cout << "\nBase Damage: " << HealthBaseDamage << " Modifier: " << DamageModifier << endl;
	double HealthDamage = HealthBaseDamage*DamageModifier;

	//cout << "\n\n\n\n Impact: " << Impact*Mod.Damage << " Puncutre: " << Puncture*Mod.Damage << " Slash: " << Slash*Mod.Damage << endl;
	//cout << "\n HealthImpact: " << HealthImpact*Mod.Damage << " HealthPuncutre: " << HealthPuncture*Mod.Damage << " HealthSlash: " << HealthSlash*Mod.Damage << endl;
	//cout << "\n ShieldsImpact: " << ShieldsImpact*Mod.Damage << " ShieldsPuncutre: " << ShieldsPuncture*Mod.Damage << " ShieldsSlash: " << ShieldsSlash*Mod.Damage << endl;
	//cout << "\n Total Health Damage Without Crit:" << HealthDamage/CritModifier << " Total Health Damage: " << HealthDamage << endl;
	//cout << "Total Shields Damage Without Crit:" << ShieldsDamage / CritModifier << " Total Shields Damage: " << ShieldsDamage << "\n" << endl;



	////JUST FOR CHECKS///////////////////////////////////////
	//int RoundsFired = ApplyDamage(RealHealth, RealShields, HealthDamage, ShieldDamage, ShieldDamageModifier, HealthDamageModifier);
	//cout << "\nRounds Fired: " << RoundsFired << endl;
	//cout << "Magazine Capacity: " << CurrentWeapon.Magazine*Mod.MagazineCapacity << endl;
	//double TimeToKill = (RoundsFired / (CurrentWeapon.FireRate*Mod.FireRate)) + (trunc(RoundsFired / (CurrentWeapon.Magazine*Mod.MagazineCapacity)))*(CurrentWeapon.ReloadSpeed/Mod.ReloadSpeed);
	//cout << "Time to kill: " << TimeToKill << endl;
	////////////////////////////////////////////////////

	// Apply Damage Where Appropriate
	double dShieldHits = RealShields / ShieldsDamage;
	int ShieldHits = (int)ceil(dShieldHits);
	double CarryOver = ShieldsDamage*(dShieldHits - ShieldHits);
	int HealthHits = (int)ceil((RealHealth + CarryOver) / HealthDamage);
	int Numofenemies = 100;
	double CalculatedHits = Numofenemies*(ShieldHits + HealthHits);

	double CalcTimeToKill = TimeToKill(RealHealth, RealShields, HealthDamage, ShieldsDamage);

	//cout << Mod.Damage << " " << Mod.Slash << " " << Mod.Puncture << " " << Mod.Impact << " " << Mod.AttackRate << " " << Mod.CritChance << " " << Mod.CritMultiplier << " " << Mod.Heat << " " << Mod.Cold << " " << Mod.Electricity << "\t\t";
	//cout << CalcTimeToKill << endl;
	return CalcTimeToKill;
}

double Weapon::TimeToKill(double RealHealth, double RealShields, double HealthDamage, double ShieldsDamage)
{
	return 0;
}


Weapon::~Weapon()
{
}


