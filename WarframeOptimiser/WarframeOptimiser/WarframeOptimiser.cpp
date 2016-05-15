#include "stdafx.h"
//Class Objects
#include "Structs.h"
#include "Weapon.h"
#include "MeleeWeapon.h"




#include <iostream>
#include <string>
//For File Reading
#include <fstream>
//For Ciel function
#include <cmath>
//For Clock
#include <ctime>



using namespace std;

int permfactorial(int n, int Start);

void InitialiseTarget(int CurrentTarget);
void InitialiseArmour();
void InitialiseHealth();
void InitialiseShields();
void InitialiseWeapon();

//double CalculateDamage(int * ElementsArray, int Elementsize);
//int *GetElements(int *Array, int size);
void SetMods(int * Array, int ArraySize);
void ResetMods();


//NOT USING ATM
//void ReadFile();
//void generate(int n, int * A, int print);

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// FOR PERMUTATION CALCULATION
void generatepermutations(int *AnsArray, int  numToChoose, int * InputArray, int InputArraylength,int start);
bool check(int * InputArray, int index, int  * AnsArray, int Check);
void PrintArray(int ArrayLength, int *Array, char n);
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

////// STRUCTS////////////////////

struct Weapons
{

	string Type;

	double Impact = 0;
	double Puncture = 0;
	double Slash = 0;

	double Heat = 0;
	double Toxin = 0;
	double Cold = 0;
	double Electricity = 0;

	double Corrosive = 0;
	double Radiation = 0;
	double Viral = 0;
	double Blast = 0;
	double Gas = 0;
	double Magnetic = 0;

	double ReloadSpeed = 0;  // = Weapon Reload Time / (1+Total Mod Reload Bonus)
	double Magazine = 0;
	double CritChance = 0;
	double CritMultiplier = 0;

	double StatusChance = 0;
	double FireRate = 0; // CHECK OUT CHARGE TIMES ON WIKI

	//
	double AttackSpeed = 0;
	double ChannelingCost = 5;
	double ChannelingDamage = 1.5;
};
Weapons CurrentWeapon;

int LoadOut[8] = { 0,0,0,0,0,0,0,0 };
int SaveDrain = 0;
double BestTime = 10000;
Weapon * CurrentWeapons;
//############################ MAIN ###############################
int main()
{
	CurrentWeapon.Type = "ESword";


	double EbladePhysical = (250 * (1.3)) / 3;
	Weapon *EBlade = new MeleeWeapon("ESword", "Exalted Blade", EbladePhysical, EbladePhysical, EbladePhysical,
		0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0.15, 2, 0.10,
		2.93, 0, 0.50);
	CurrentWeapons = EBlade;

	CurrentEnemy.CurrentLevel = 90;
	int CurrentTarget = 5;

	//Set data to Structs
	InitialiseArmour();
	InitialiseHealth();
	InitialiseShields();
	//InitialiseWeapon();


	InitialiseTarget(CurrentTarget);
	
	
	//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	//Pass stuff to permutation stuff ------- Largest Test [20][6] takes 43.299 seconds, 2.8 million calcs.
	//int InputArray[22] = { 0,3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 17, 14, 15, 16, 13, 18, 19, 20, 23, 24, 25 }; // Currently All
	//int InputArray[20] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 17, 14, 15, 16, 13, 18, 19, 20, 23, 24};
	//int InputArray[13] = { 0,4, 9, 10, 11, 12, 13, 20, 21, 22 ,23, 26,28 };
	//int InputArray[5] = { 24,19,13,15,20};
	int InputArray[10] = { 1,4, 9, 10, 11, 13, 20, 21, 26, 28 };
	//int InputArray[4] = { 1,2,3,4 };
	int AnsArray[8];

	int LengthInputArray = sizeof(InputArray) / sizeof(int);
	int LengthAnsArray = sizeof(AnsArray) / sizeof(int);
	
	cout << LengthInputArray << " " << LengthAnsArray << endl;
	int numofperms = permfactorial(LengthInputArray,LengthInputArray-LengthAnsArray); // FIX FOR BIG NUMBERS
	cout << numofperms << endl;

	/*
	//FOR SINGLE TESING
	SetMods(InputArray, LengthInputArray);
	//double TimeToKill = CalculateDamage(GetElements(InputArray, LengthInputArray),LengthInputArray);// makes it run approx 4.6x slower 
	double TimeToKill = CurrentWeapons->CalculateDamage(CurrentWeapons->GetElements(InputArray, LengthInputArray), LengthInputArray);
	//cout<< TimeToKill << endl;
	ResetMods();
	*/
	
	
	// Begin Perumtation
	

	//call for recursive Perumtation function.
	cout << "27907200 takes 43 seconds" << endl;
	cout << "Continue? (Y/N): " << endl;
	char a;
	cin >> a;
	//a = 'y';
	if (a == 'Y' || a == 'y') {
		cout << "Start Permutation with " << numofperms << " permutations." << endl;

		clock_t time; // to be used to calculate time taken
		time = clock();

		//generate(LengthInputArray, InputArray, LengthAnsArray);
		generatepermutations(AnsArray, LengthAnsArray, InputArray, LengthInputArray, 0);

		double elapsedtime = clock() - time; // Calculate time taken

		std::cout << "End Permutation, Time Taken: " << std::endl;
		std::cout << "Clocks taken: " << elapsedtime << " Pc Clocks Per Second: " << CLOCKS_PER_SEC << " Time Taken : " << elapsedtime / CLOCKS_PER_SEC << std::endl;
		//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		cout << " Best Time: " << BestTime << " Array of Loadout: { ";
		PrintArray(sizeof(LoadOut) / sizeof(int), LoadOut, 'o');
		cout << "} Enter In This Order. Drain: " << SaveDrain;
	}
	
	else
	{
		cout << "Too Bad" << endl;
	}
	
	getchar();
	getchar();
	
	

	return 0;
}
/*
	{finds the number of permutations given the size of the data and
	the difference between the data's size and how many are chosen.}
*/
int permfactorial(int Size, int Difference) 
{
	int product = Difference +1;
	for (int i = product+1; i <= Size; i++)
	{
		product *= i;
	}
	return product;
}

void InitialiseTarget(int CurrentTarget)
{

	/*
	Alloy
	Ferrite
	No rmour


	Flesh
	Cloned Flesh
	Infested
	Infested Flesh
	Machinery
	Robotic
	Fossilized
	Infested Sinew


	Standard
	Proto
	No Shields
	*/
	switch (CurrentTarget)
	{
	case 1: // Stalker
		TargetArmourType = Alloy;
		TargetHealthType = Flesh;
		TargetShieldsType = Proto;

		CurrentEnemy.BaseHealth = 100;
		CurrentEnemy.BaseArmour = 225;
		CurrentEnemy.BaseShields = 200;
		CurrentEnemy.BaseLevel = 30;

		CurrentEnemy.Faction = "Stalker";
		break;

	case 2: // Grineer Trooper
		TargetArmourType = Ferrite;
		TargetHealthType = ClonedFlesh;
		TargetShieldsType = NoShields;

		CurrentEnemy.BaseHealth = 120;
		CurrentEnemy.BaseArmour = 150;
		CurrentEnemy.BaseShields = 0;
		CurrentEnemy.BaseLevel = 1;

		CurrentEnemy.Faction = "Grineer";
		break;

	case 3: // Grineer Lancer
		TargetArmourType = Ferrite;
		TargetHealthType = ClonedFlesh;
		TargetShieldsType = NoShields;

		CurrentEnemy.BaseHealth = 100;
		CurrentEnemy.BaseArmour = 100;
		CurrentEnemy.BaseShields = 0;
		CurrentEnemy.BaseLevel = 1;

		CurrentEnemy.Faction = "Grineer";
		break;

	case 4: // Grineer Ballista
		TargetArmourType = Ferrite;
		TargetHealthType = ClonedFlesh;
		TargetShieldsType = NoShields;

		CurrentEnemy.BaseHealth = 100;
		CurrentEnemy.BaseArmour = 100;
		CurrentEnemy.BaseShields = 0;
		CurrentEnemy.BaseLevel = 1;

		CurrentEnemy.Faction = "Grineer";
		break;

	case 5: // Corpus Crewman
		TargetArmourType = NoArmour;
		TargetHealthType = Flesh;
		TargetShieldsType = Standard;

		CurrentEnemy.BaseHealth = 60;
		CurrentEnemy.BaseArmour = 0;
		CurrentEnemy.BaseShields = 150;
		CurrentEnemy.BaseLevel = 1;

		CurrentEnemy.Faction = "Corpus";

		break;
	case 6: // Corrupted Grineer Heavy Gunner
		TargetArmourType = Ferrite;
		TargetHealthType = ClonedFlesh;
		TargetShieldsType = NoShields;

		CurrentEnemy.BaseHealth = 700;
		CurrentEnemy.BaseArmour = 500;
		CurrentEnemy.BaseShields = 0;
		CurrentEnemy.BaseLevel = 8;

		CurrentEnemy.Faction = "Orokin";
		break;
	}
	CurrentEnemy.CurrentArmour = CurrentEnemy.BaseArmour*(1 + (pow(CurrentEnemy.CurrentLevel - CurrentEnemy.BaseLevel, 1.75) / 200));
	CurrentEnemy.CurrentHealth = CurrentEnemy.BaseHealth*(1 + 0.015*(pow(CurrentEnemy.CurrentLevel - CurrentEnemy.BaseLevel, 2)));
	CurrentEnemy.CurrentShields = CurrentEnemy.BaseShields*(1 + 0.0075*(pow(CurrentEnemy.CurrentLevel - CurrentEnemy.BaseLevel, 2)));
}
void InitialiseArmour()
{
	Alloy.Puncture = 0.15;
	Alloy.Cold = 0.25;
	Alloy.Radiation = 0.75;

	Alloy.Slash = -0.50;
	Alloy.Electricity = -0.50;
	Alloy.Magnetic = -0.50;

	Ferrite.Toxin = 0.25;
	Ferrite.Puncture = 0.50;
	Ferrite.Corrosive = 0.75;

	Ferrite.Slash = -0.15;
	Ferrite.Blast = -0.25;
}
void InitialiseHealth()
{
	Flesh.Slash = 0.25;
	Flesh.Toxin = 0.5;
	Flesh.Viral = 0.5;

	Flesh.Impact = -0.25;
	Flesh.Gas = -0.25;

	ClonedFlesh.Slash = 0.25;
	ClonedFlesh.Heat = 0.25;
	ClonedFlesh.Viral = 0.75;

	ClonedFlesh.Impact = -0.25;
	ClonedFlesh.Gas = -0.50;

}
void InitialiseShields()
{
	Standard.Impact = 0.50;
	Standard.Cold = 0.50;
	Standard.Magnetic = 0.75;

	Standard.Puncture = -0.20;
	Standard.Radiation = -0.25;

	Proto.Impact = 0.15;
	Proto.Toxin = 0.25;
	Proto.Magnetic = 0.75;

	Proto.Puncture = -0.5;
	Proto.Heat = -0.5;
	Proto.Corrosive = -0.5;
}

void InitialiseWeapon()
{
	int Weapon = 0;
	switch (Weapon)
	{
	case 1: //Braton
		CurrentWeapon.Impact = 6.6;
		CurrentWeapon.Puncture = 6.6;
		CurrentWeapon.Slash = 6.8;

		CurrentWeapon.ReloadSpeed = 2;
		CurrentWeapon.Magazine = 45;
		CurrentWeapon.FireRate = 8.75;

		CurrentWeapon.CritChance = 0.10;
		CurrentWeapon.CritMultiplier = 1.5;
		CurrentWeapon.StatusChance = 0.05;
		
		CurrentWeapon.Type = "Rifle";
		break;
	case 2: // Soma
		CurrentWeapon.Impact = 1;
		CurrentWeapon.Puncture = 4;
		CurrentWeapon.Slash = 5;

		CurrentWeapon.ReloadSpeed = 3;
		CurrentWeapon.Magazine = 100;
		CurrentWeapon.FireRate = 15;

		CurrentWeapon.CritChance = .30;
		CurrentWeapon.CritMultiplier = 3;
		CurrentWeapon.StatusChance = 0.07;

		CurrentWeapon.Type = "Rifle";
		break;

	case 3: // Exalted Blade
		CurrentWeapon.Slash = (250 * (1.3)) /3; // (250 * Power strength) /3
		CurrentWeapon.Impact = (250 * (1.3)) /3;
		CurrentWeapon.Puncture = (250 * (1.3)) /3;

		CurrentWeapon.CritChance = 0.15;
		CurrentWeapon.CritMultiplier = 2.00;
		CurrentWeapon.StatusChance = 0.10;
		CurrentWeapon.AttackSpeed = 2.93;// total 4 hit combo = 1.364s
		CurrentWeapon.Type = "ESword";
		break;
	case 4: // Boltace
		CurrentWeapon.Slash = 8.5;
		CurrentWeapon.Impact = 8.5;
		CurrentWeapon.Puncture = 68;

		CurrentWeapon.CritChance = 0.05;
		CurrentWeapon.CritMultiplier = 1.5;
		CurrentWeapon.StatusChance = 0.25;
		CurrentWeapon.AttackSpeed = 2.827;// total 4 hit combo =  1.415s
		CurrentWeapon.Type = "ESword";


		break;
	default: 
		break;
	}
}

void SetMods(int * Array,int ArraySize)
{

	if (CurrentWeapon.Type == "Rifle")
	{
		for (int i = 0; i < ArraySize; i++)
		{
			switch (Array[i]) // primary Rifle
			{
			case 0: break;								  // No Mod
			case 1:	Mod.Damage += 1.65;				break;// Serration
			case 2:	Mod.Slash += 0.30;				break;// Sawtooth Clip
			case 3:	Mod.Puncture += 0.30;			break;// Piercing Hit
			case 4:	Mod.Impact += 0.30;				break;// Rupture
			case 5: Mod.Heat += 0.90;				break;// Hell Fire	
			case 6: Mod.Cold += 0.90;				break;// Cryo Rounds
			case 7: Mod.Toxin += 0;					break;
			case 8: Mod.Electricity += 0;			break;

			case 9: Mod.ReloadSpeed += 0.30;		break;// Fast Hands
			case 10: Mod.CritChance += 1.50;		break;// Point Strike
			case 11: Mod.CritMultiplier += 1.20;	break;// Vital Sense
			case 12: Mod.MagazineCapacity += 0.30;	break;// Magazine Warp
			case 13: Mod.AttackRate += 0.60;			break;// Speed Trigger
			
			default:
				break;
			}
		}
	}
	else if (CurrentWeapon.Type == "ESword")
	{
		for (int i = 0; i < ArraySize; i++) // MY MODS
		{
			switch (Array[i]) // Energy Sword
			{
			case 0: break;
			//PHYSICAL
			case 1:	Mod.Damage += 1.20; Mod.Drain += 9;				break;// Pressure Point
			case 2: Mod.Damage += 1.00; Mod.AttackRate -= 0.20; Mod.Drain += 7; break;// Spoiled Strike

			case 3: Mod.Slash += 0.90; Mod.Drain += 7;		break;//Jagged Edge
			case 4: Mod.Puncture += 0.90; Mod.Drain += 7;		break;//Sundering Strike
			case 5: Mod.Impact += 0.90;	Mod.Drain += 7;		break;// Heavy Trauma

			case 6: Mod.Slash += 1.20;	Mod.Drain += 11;		break;// Buzz Kill
			case 7: Mod.Puncture += 1.20;	Mod.Drain += 11;		break;// Auger Strike
			case 8: Mod.Impact += 1.20;		Mod.Drain += 11;	break;// Collision Force

			case 9: Mod.Slash += 0.60; Mod.Puncture += 0.80; Mod.Drain += 9; break;// Rending Strike
																				  //ELEMENTAL
			case 10: Mod.Heat += 0.90;	Mod.Drain += 11;			break;// Molten Impact
			case 11: Mod.Cold += 0.90;	Mod.Drain += 11;			break;// North Wind
			case 12: Mod.Toxin += 0.90;	Mod.Drain += 11;			break;// Fever Strike
			case 13: Mod.Electricity += 0.90; Mod.Drain += 11;		break;// Shocking Touch

			case 14: Mod.Heat += 0.60; Mod.StatusChance += 0.60; Mod.Drain += 7; break; // Volcanic Edge
			case 15: Mod.Cold += 0.60; Mod.StatusChance += 0.60; Mod.Drain += 7; break; // Vicious Frost
			case 16: Mod.Toxin += 0.60; Mod.StatusChance += 0.60; Mod.Drain += 7; break; // Virulent Scourge
			case 17: Mod.Electricity += 0.60; Mod.StatusChance += 0.60; Mod.Drain += 7; break; // Voltaic Strike

			case 18: Mod.Electricity += 0.60; Mod.ChannelEfficiency += 0.40; break; Mod.Drain += 9;// Focus Energy

			case 19: Mod.CritChance += 0.60; Mod.Drain += 9;			break;// True Steel
			case 20: Mod.CritMultiplier += 0.90; Mod.Drain += 9;	break;// Organ Shatter

			case 21: Mod.StatusChance += 0.15; Mod.Drain += 7;				break;// Melee Prowess
			case 22: Mod.StatusDuration += 1.10; Mod.Drain += 16; break;// Lasting Sting

			case 23: Mod.AttackRate += 0.30; Mod.Drain += 9;		break;// Fury
			case 24: Mod.AttackRate += 0.75;	Mod.Drain += 9;		break;// Berserker

			case 25: if (CurrentEnemy.Faction == "Corupus") { Mod.FactionMultiplier += 0.30; Mod.Drain += 9; } break; // Smite Corpus
			case 26: if (CurrentEnemy.Faction == "Grineer") { Mod.FactionMultiplier += 0.30; Mod.Drain += 9; } break; // Smite Grineer
			case 27: if (CurrentEnemy.Faction == "Infested") { Mod.FactionMultiplier += 0.30; Mod.Drain += 9; } break; // Smite Infested

			case 28: Mod.Impact += 1.65; break; Mod.Drain += 12;// Primed Heavy Trauma
			case 29: Mod.AttackRate += 0.55; break; // Primed Fury

			default:
				break;
			}
		}


		/*
		for (int i = 0; i < ArraySize; i++)
		{
			switch (Array[i]) // Energy Sword
			{
			case 0: break;// No Mod

			//PHYSICAL
			case 1:	Mod.Damage += 1.20; Mod.Drain += 9;				break;// Pressure Point
			case 2: Mod.Damage += 1.00; Mod.AttackSpeed -= 0.20; Mod.Drain += 7; break;// Spoiled Strike

			case 3: Mod.Slash += 0.90; Mod.Drain += 7;		break;//Jagged Edge
			case 4: Mod.Puncture += 0.90; Mod.Drain += 7;		break;//Sundering Strike
			case 5: Mod.Impact += 0.90;	Mod.Drain += 7;		break;// Heavy Trauma

			case 6: Mod.Slash += 1.20;	Mod.Drain += 11;		break;// Buzz Kill
			case 7: Mod.Puncture += 1.20;	Mod.Drain += 11;		break;// Auger Strike
			case 8: Mod.Impact += 1.20;		Mod.Drain += 11;	break;// Collision Force

			case 9: Mod.Slash += 0.60; Mod.Puncture += 0.80; Mod.Drain += 9; break;// Rending Strike

			//ELEMENTAL
			case 10: Mod.Heat += 0.90;	Mod.Drain += 11;			break;// Molten Impact
			case 11: Mod.Cold += 0.90;	Mod.Drain += 11;			break;// North Wind
			case 12: Mod.Toxin += 0.90;	Mod.Drain += 11;			break;// Fever Strike
			case 13: Mod.Electricity += 0.90; Mod.Drain += 11;		break;// Shocking Touch

			case 14: Mod.Heat += 0.60; Mod.StatusChance += 0.60; Mod.Drain += 7; break; // Volcanic Edge
			case 15: Mod.Cold += 0.60; Mod.StatusChance += 0.60; Mod.Drain += 7; break; // Vicious Frost
			case 16: Mod.Toxin += 0.60; Mod.StatusChance += 0.60; Mod.Drain += 7; break; // Virulent Scourge
			case 17: Mod.Electricity += 0.60; Mod.StatusChance += 0.60; Mod.Drain += 7; break; // Voltaic Strike

			case 18: Mod.Electricity += 0.60; Mod.ChannelEfficiency += 0.40; break; Mod.Drain += 9;// Focus Energy

			case 19: Mod.CritChance += 0.60; Mod.Drain += 9;			break;// True Steel
			case 20: Mod.CritMultiplier += 0.90; Mod.Drain += 9;	break;// Organ Shatter

			case 21: Mod.StatusChance += 0.15; Mod.Drain += 7;				break;// Melee Prowess
			case 22: Mod.StatusDuration += 1.10; Mod.Drain += 16; break;// Lasting Sting

			case 23: Mod.AttackSpeed += 0.30; Mod.Drain += 9;		break;// Fury
			case 24: Mod.AttackSpeed += 0.75;	Mod.Drain += 9;		break;// Berserker

			case 25: if (CurrentEnemy.Faction == "Corupus") { Mod.FactionMultiplier += 0.30; Mod.Drain += 9; } break; // Smite Corpus
			case 26: if (CurrentEnemy.Faction == "Grineer") { Mod.FactionMultiplier += 0.30; Mod.Drain += 9; } break; // Smite Grineer
			case 27: if (CurrentEnemy.Faction == "Infested") { Mod.FactionMultiplier += 0.30; Mod.Drain += 9; } break; // Smite Infested

			//PRIMED
			case 28: Mod.Impact += 1.65; break; Mod.Drain += 12;// Primed Heavy Trauma
			case 29: Mod.AttackSpeed += 0.55; break; // Primed Fury



			/*HAVN'T DAMAGE CALCULATED THIS STUFF
			case 30: Mod.ChannelDamage += 1.2;		break;// Killing Blow
			case 31: Mod.ChannelEfficiency += 0.60; Mod.Drain += 7; break; // Reflex Coil
			case 32: Mod.ChannelDamage += 1.00; Mod.ChannelEfficiency -= 0.40; break;// Corrupt Charge

			// WHILE CHANNELING
			case 33: Mod.AttackSpeed += 0.20; Mod.ChannelEfficiency -= 0.80;	break; // Quickening
			case 34: Mod.CritChance += 0.40; Mod.ChannelEfficiency -= 0.60; break;//True Punishment
			case 35: Mod.StatusChance += 0.60; Mod.ChannelEfficiency -= 0.40; break;// Enduring Strike

			

				//WEIRD STUFF
			case 36: Mod.StatusChance += 0.45; break;//Weeping Wounds
			case 37: Mod.CritChance += 1.65; break;//Blood Rush
			Shattering Impact - DOES STUFF


			// WEAPON AUGMENTS
			case 38: Mod.StatusChance += 1.00; break;// Gleaming Blight:	+ 1 Blight Dark -- Daggers
			case 39: Mod.Toxin += 1.00; break;//	Toxic Blight:			+ 1 Blight		-- Mire
			case 40: Mod.Damage += 1.00; break;//	Justice Blades:			+ 1 Justice		-- Dual Cleavers
			case 41: Mod.Damage += 1.00; break;//	Bright Purity:			+ 1 Purity		-- Skana
			case 42: Mod.Damage += 1.00; break;//	Blade of Truth:			+ 1 Truth		-- Jaw Sword
			


			// CONCLAVE EXCLUSIVE - Look at others later
				// only one of the Convertion mods at a time
			// Counterweight	: Convert 20% Physical Damage to IMPACT
			// Serrated Edges	: Convert 20% Physical Damage to PUNCTURE
			// Sharpened Blade	: Convert 20% Physical Damage to Slash


			default:
				break;
			//}
		//}*/
	}
}

void ResetMods()
{
	//PRIMARY RIFLE
	Mod.Drain = 0;
	Mod.Polarity;

	Mod.MaxAmmoCapacity = 1;
	Mod.MagazineCapacity = 1; // done
	Mod.ReloadSpeed = 1; // done
	Mod.AttackRate = 1; // done
	Mod.MultiShot = 1;//////////////////
	
	Mod.CritChance = 1; // done
	Mod.CritMultiplier = 1; // done
	Mod.FactionMultiplier = 1;//////////////////
	
	Mod.StatusDuration = 1;/////////////////
	Mod.StatusChance = 1;///////////////////
	
	Mod.Damage = 1; // done
	Mod.Impact = 1; // done
	Mod.Slash = 1; // done
	Mod.Puncture = 1; // done
	
	Mod.Heat = 0; // done
	Mod.Cold = 0;// done
	Mod.Electricity = 0;// done
	Mod.Toxin = 0;// done
	
		 //MELEE EXCLUSIVE
	Mod.ChannelEfficiency = 1;
	Mod.ChannelDamage = 1;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%% ALL PERMUTATION CALC FUNCTIONS %%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


double TimeToKill;

void generatepermutations(int *AnsArray, int Ansize, int * InputArray, int inputsize, int start) // RECURSION WORKS
{
	for (int j = 0; j < inputsize; j++)
	{
		if ((check(InputArray, j, AnsArray, start) == true))
		{
			AnsArray[start] = InputArray[j];
			if (start == (Ansize - 1))
			{
				SetMods(AnsArray, Ansize); //makes calculation approx 7.68x Slower
				if (Mod.Drain <= 60 && Mod.Drain >= Ansize * 7) // makes calculation approx 1.25x Slower
				{

					//TimeToKill = CalculateDamage(GetElements(AnsArray, Ansize), Ansize);
					TimeToKill = CurrentWeapons->CalculateDamage(CurrentWeapons->GetElements(AnsArray, Ansize), Ansize);

					if (TimeToKill <= BestTime)
					{
						for (int i = 0; i < Ansize; i++)
						{
							LoadOut[i] = AnsArray[i];
							SaveDrain = Mod.Drain;
						}
						BestTime = TimeToKill;
					}
				}
				ResetMods(); // makes calculation approx 1.28x Slower
			}
			else 
			{	
				generatepermutations(AnsArray, Ansize, InputArray, inputsize, start + 1);	
			}
		}
	}
}

bool check(int * InputArray, int index, int  * AnsArray, int start)
{
	for (int i = start - 1; i >= 0; i--)
	{
		if (AnsArray[i] == InputArray[index] && InputArray[index] != 0)
		{
			return false;
		}
	}
	return true;
}

void PrintArray(int ArrayLength, int *Array,char n)
{
	for (int i = 0; i < ArrayLength; i++)
	{
		std::cout << Array[i] << " ";
		if (((i + 1) % ArrayLength == 0) && n == 'n')
		{
			std::cout << std::endl;
		}
	}
}

/*
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%% CALCULATE DAMAGE AND KILLS %%%%%%%%%%%%%%%%%%%%%%%%%%%%% Check this is in all classes before removing
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
double CalculateDamage(int * ElementsArray,int Elementsize) // NEED TO DO CHANNELING AND RANGE
{

	//WILL GET VALUES FROM MODS OR SOMETHING
	int HealthDebuffs = 1;
	int ArmourDebuffs = 1;
	int ShieldsDebuffs = 1;

	///////////////////////////////TO BE PUT IN SOME FORM OF INITIALISATION ///////////////////////////

	//Calculate target specific ARMOUR values
	double RealArmour = CurrentEnemy.CurrentArmour;
	//cout << "Real Armour: " << RealArmour << endl;
	//Calculate target specific HEALTH values
	double RealHealth = CurrentEnemy.CurrentHealth;
	//cout << "Real Health: " << RealHealth << endl;
	//Calculate target specific SHIELDS values
	double RealShields = CurrentEnemy.CurrentShields;
	//cout << "Real Shields: " << RealShields << endl;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// WORK OUT ELEMENTS /////////////////////////////////////////////////////////////////////////////////////////////////////
	//PrintArray(Elementsize, ElementsArray,'o');
	static int FirstElement = 0;
	static int SecondElement = 0;
	static int GotFirst = 0;

	bool CombElement[6] = { 0,0, 0, 0, 0, 0 };
	// Find Element Combinations
	for (int i = 0; i < Elementsize; i++)
	{
		
		if ((ElementsArray[i] == 1 || ElementsArray[i] == 2 || ElementsArray[i] == 3 || ElementsArray[i] == 4)&& GotFirst == 0)
		{
			//cout << "In First: ";
			FirstElement = ElementsArray[i];
			GotFirst=1;
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
	double Heat = (CurrentWeapon.Heat + (CurrentWeapon.Slash + CurrentWeapon.Impact + CurrentWeapon.Puncture + CurrentWeapon.Heat) * Mod.Heat);
	double Cold = (CurrentWeapon.Cold + (CurrentWeapon.Slash + CurrentWeapon.Impact + CurrentWeapon.Puncture + CurrentWeapon.Cold) * Mod.Cold);
	double Toxin = (CurrentWeapon.Toxin + (CurrentWeapon.Slash + CurrentWeapon.Impact + CurrentWeapon.Puncture + CurrentWeapon.Toxin) * Mod.Toxin);
	double Electricity = (CurrentWeapon.Electricity + (CurrentWeapon.Slash + CurrentWeapon.Impact + CurrentWeapon.Puncture + CurrentWeapon.Electricity)	* Mod.Electricity);

	double Blast = (Heat + Cold);
	double Gas = (Heat + Toxin);
	double Radiation = (Heat + Electricity);
	double Viral = (Cold + Toxin);
	double Magnetic = (Cold + Electricity);
	double Corrosive = (Electricity + Toxin);
	// SHIELD ELEMENTS
	double ShieldsHeat = Heat*(1 + TargetShieldsType.Heat);
	double ShieldsCold = Cold*(1 + TargetShieldsType.Cold);
	double ShieldsElectricity = Electricity*(1 + TargetShieldsType.Electricity);
	double ShieldsToxin = Toxin*(1 + TargetShieldsType.Toxin);

	double ShieldsBlast = 0;
	double ShieldsGas = 0;
	double ShieldsRadiation = 0;
	double ShieldsViral = 0;
	double ShieldsMagnetic = 0;
	double ShieldsCorrosive = 0;

	// HEALTH ELEMENTS  -- OPTIMISE ARMOUR
	double HealthHeat = Heat*(1 + TargetHealthType.Heat)*(1+TargetArmourType.Heat) / (1 + (RealArmour*(1 - TargetArmourType.Heat)) / 300);
	double HealthCold = Cold*(1 + TargetHealthType.Cold)*(1 + TargetArmourType.Cold) / (1 + (RealArmour*(1 - TargetArmourType.Cold)) / 300);
	double HealthElectricity = Electricity*(1 + TargetHealthType.Electricity)*(1 + TargetArmourType.Electricity) / (1 + (RealArmour*(1 - TargetArmourType.Electricity)) / 300);
	double HealthToxin = Toxin*(1 + TargetHealthType.Toxin)*(1 + TargetArmourType.Toxin) / (1 + (RealArmour*(1 - TargetArmourType.Toxin)) / 300);

	double HealthBlast = 0;
	double HealthGas = 0;
	double HealthRadiation = 0;
	double HealthViral = 0;
	double HealthMagnetic = 0;
	double HealthCorrosive = 0;

	if (CombElement[0] == true)//Blast
	{
		HealthBlast = Blast*(1 + TargetHealthType.Blast)*(1 + TargetArmourType.Blast) / (1 + (RealArmour*(1 - TargetArmourType.Blast)) / 300);
		ShieldsBlast = Blast*(1 + TargetShieldsType.Blast);

		ShieldsHeat = 0;
		ShieldsCold = 0;

		HealthHeat = 0;
		HealthCold = 0;
	}
	if (CombElement[1] == true)//Gas
	{
		HealthGas = Gas*(1 + TargetHealthType.Gas)*(1 + TargetArmourType.Gas) / (1 + (RealArmour*(1 - TargetArmourType.Gas)) / 300);
		ShieldsGas = Gas*(1 + TargetShieldsType.Gas);
		ShieldsHeat = 0;
		ShieldsToxin = 0;

		HealthHeat = 0;
		HealthToxin = 0;
	}
	if (CombElement[2] == true)//Radiation
	{
		HealthRadiation = Radiation*(1 + TargetHealthType.Radiation)*(1 + TargetArmourType.Radiation) / (1 + (RealArmour*(1 - TargetArmourType.Radiation)) / 300);
		ShieldsRadiation = Radiation*(1 + TargetShieldsType.Radiation);
		
		ShieldsHeat = 0;
		ShieldsElectricity = 0;

		HealthHeat = 0;
		HealthElectricity = 0;
	}
	if (CombElement[3] == true)//Viral
	{
		HealthViral = Viral*(1 + TargetHealthType.Viral)*(1 + TargetArmourType.Viral) / (1 + (RealArmour*(1 - TargetArmourType.Viral)) / 300);
		ShieldsViral = Viral*(1 + TargetShieldsType.Viral);

		ShieldsCold = 0;
		ShieldsToxin = 0;

		HealthCold = 0;
		HealthToxin = 0;
	}
	if (CombElement[4] == true)//Magnetic
	{
		HealthMagnetic = Magnetic*(1 + TargetHealthType.Magnetic)*(1 + TargetArmourType.Magnetic) / (1 + (RealArmour*(1 - TargetArmourType.Magnetic)) / 300);
		ShieldsMagnetic = Magnetic*(1 + TargetShieldsType.Magnetic);

		ShieldsCold = 0;
		ShieldsElectricity = 0;

		HealthCold = 0;
		HealthElectricity = 0;
	}
	if (CombElement[5] == true)//Corrosive
	{
		HealthCorrosive = Corrosive*(1 + TargetHealthType.Corrosive)*(1 + TargetArmourType.Corrosive) / (1 + (RealArmour*(1 - TargetArmourType.Corrosive)) / 300);
		ShieldsCorrosive = Corrosive*(1 + TargetShieldsType.Corrosive);

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

	/////////////////////////////////////////////////////////////////////////////////////////////////////


	// CRIT CALCULATIONS /////////////////////////////////////////////////////////////////////////////////
	//Extra Modifiers
	double HeadShotRate = 0.4;
	double CritChance = CurrentWeapon.CritChance*Mod.CritChance;
	double CritMultiplier = CurrentWeapon.CritMultiplier*Mod.CritMultiplier;
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
		CritModifier = (1 + HeadShotRate) * (1 + CritChance*(CritMultiplier*(3 - 2 / (1 + HeadShotRate)) - 1));

		//cout << "\nCritModifier Check: " << CritModifier2 << " Equation:" << CritModifier << " My Try: " << RyanModifier << endl;
		//cout << "CritModifier 1: " << CritModifier << endl;

	}
	else if (CritChance > 1)
	{
		// SIMPLE ADDITION OF PARTS
		//double RedHeadCrit = (CritChance-1)*(2 * CritMultiplier - 1)*HeadShotRate*HeadShotMult * 2;
		//double HeadCrit = CritMultiplier*HeadShotRate * 2 * HeadShotMult;
		//double RedCrit = (CritChance-1)*(2 * CritMultiplier - 1)*(1 - HeadShotRate);
		//double Crit = CritMultiplier*(1 - HeadShotRate);

		//double CritModifier3 = RedHeadCrit + HeadCrit + RedCrit + Crit;

		// SIMPLIFIED FORMULA if HeadShotMult = 2
		CritModifier = (3 * HeadShotRate + 1)*((CritChance - 1)*(2 * CritMultiplier - 1) + CritMultiplier);
		//Wiki Formula is Incorrect
		//double WikiRedCrit = (1 + 3 * HeadShotRate) *(1 + CritChance *(CritMultiplier - 1));


		//cout << "\nCritModifier Check: " << CritModifier3 << " Equation 2: " << CritModifier << endl;
		//cout << " Equation 2: " << CritModifier << endl;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//Base Physical 
	double Slash = CurrentWeapon.Slash*Mod.Slash;
	double Impact = CurrentWeapon.Impact*Mod.Impact;
	double Puncture = CurrentWeapon.Puncture*Mod.Puncture;
	// SHIELDS ---------------------
	double ShieldDamageModifier = (CritModifier*Mod.FactionMultiplier*Mod.Damage);
	//Calculate Target specific Received DAMAGE values
	double ShieldsSlash = Slash*(1 + TargetShieldsType.Slash);
	double ShieldsImpact = Impact*(1 + TargetShieldsType.Impact);
	double ShieldsPuncture = Puncture*(1 + TargetShieldsType.Puncture);

	
	//DAMAGE TO SHIELDS
	double ShieldBaseDamage = (ShieldsSlash + ShieldsImpact + ShieldsPuncture + ShieldElemental);
	double ShieldsDamage = ShieldBaseDamage*ShieldDamageModifier;
	
	//cout << "\nImpact: " << ShieldImpact*Mod.Damage/ (1 + TargetShieldsType.Impact) << " Puncutre: " << ShieldPuncture*Mod.Damage/ (1 + TargetShieldsType.Puncture) << " Slash: " << ShieldSlash*Mod.Damage/ (1 + TargetShieldsType.Slash) << " Heat: " << ShieldsHeat*Mod.Damage/ (1 + TargetShieldsType.Heat) << "\nTotal Shield Damage without Crit: " << ShieldDamage/CritModifier << " Total Shield Damage: " << ShieldDamage << endl;



	//HEALTH -----------------------
	double HealthDamageModifier = (CritModifier*Mod.FactionMultiplier*Mod.Damage);
	//Calculate Target specific Received DAMAGE values
	double HealthSlash = Slash*(1 + TargetHealthType.Slash)*(1 + TargetArmourType.Slash) / (1 + (RealArmour*(1 - TargetArmourType.Slash)) / 300);
	double HealthImpact = Impact*(1 + TargetHealthType.Impact)*(1 + TargetArmourType.Impact) / (1 + (RealArmour*(1 - TargetArmourType.Impact)) / 300);
	double HealthPuncture = Puncture*(1 + TargetHealthType.Puncture)*(1 + TargetArmourType.Puncture) / (1 + (RealArmour*(1 - TargetArmourType.Puncture)) / 300);
	
	
	//DAMAGE TO HEALTH
	double HealthBaseDamage = (HealthSlash + HealthImpact + HealthPuncture + HealthElemental);
	//cout << "\nBase Damage: " << HealthBaseDamage << " Modifier: " << HealthDamageModifier << endl;
	double HealthDamage = HealthBaseDamage*HealthDamageModifier;
	
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

	double CalcTimeToKill = -1;
	double Score = 0;
	
	if (CurrentWeapon.Type == "ESword")
	{
		//cout << "Carry Over : " << CarryOver << " ShieldHits: " << ShieldHits << " HealthHits: " << HealthHits << " Calculated Hits: " << CalculatedHits << endl;
		//CalcTimeToKill = CalculatedHits / (CurrentWeapon.AttackSpeed*Mod.AttackSpeed); Actual Time
		Score = RealHealth / HealthDamage + RealShields / ShieldsDamage;
		CalcTimeToKill = Score/ (CurrentWeapon.AttackSpeed*Mod.AttackRate); // Test value
		
	}
	else
	{
		
		//cout << "Carry Over : " << CarryOver << " ShieldShots: " << ShieldHits << " HealthShots: " << HealthHits << " Calculated Rounds Fired: " << CalculatedHits << endl;

		double NumReload = (CalculatedHits / (CurrentWeapon.Magazine*Mod.MagazineCapacity));
		if (NumReload == trunc(NumReload))
		{
			NumReload = trunc(NumReload) - 1;
		}


		CalcTimeToKill = (CalculatedHits / (CurrentWeapon.FireRate*Mod.AttackRate)) + trunc(NumReload)*(CurrentWeapon.ReloadSpeed / Mod.ReloadSpeed);
		//cout << "Time to shoot Bullets: " << (CalculatedHits / (CurrentWeapon.FireRate*Mod.FireRate)) << "Times to Reload: " << trunc(NumReload) << endl;

		
	}
	//cout << Mod.Damage << " " << Mod.Slash << " " << Mod.Puncture << " " << Mod.Impact << " " << Mod.AttackSpeed << " " << Mod.CritChance << " " << Mod.CritMultiplier << " " << Mod.Heat << " " << Mod.Cold << " " << Mod.Electricity << "\t\t";
	//cout << Mod.Damage << endl;
	//cout << CalcTimeToKill << endl;
	return CalcTimeToKill;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% OTHER FUNCTIONS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void ReadFile()
{
	string line;
	ifstream myfile("RifleMods.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{	
			if (line != "") { cout << line << '\n'; }
		}
		myfile.close();
	}

	else cout << "Unable to open file";



}


// c++ implementation of Heap's Algorithm  -- can't use for anything greater than 10 MODS in pool
void generate(int n, int * A, int Get)//A : Input Array , n: size of Input array, Get: number of mods to choose from input
{
	if (n == 1)
	{
		// print out answer
		//PrintArray(Get, A,'n');

		SetMods(A, Get);
		if (Mod.Drain <= 60)
		{
			TimeToKill = CalculateDamage(GetElements(A, Get), Get);// makes it run approx 4.6x slower 
			if (TimeToKill <= BestTime)
			{
				for (int i = 0; i < Get; i++)
				{
					LoadOut[i] = A[i];
					SaveDrain = Mod.Drain;
				}
				BestTime = TimeToKill;
			}

			//cout << " k: ";
			//PrintArray(Ansize, AnsArray,'n');
		}
		ResetMods();






	}
	else
	{
		for (int i = 0; i < (n - 1); i ++)
		{
			generate(n - 1, A, Get);
			if (n % 2 == 0)
			{	//swap(A[i], A[n - 1]);
				int temp = A[i];
				A[i] = A[n - 1];
				A[n - 1] = temp;
			}
			else
			{	//swap(A[0], A[n - 1]);
				int temp = A[0];
				A[0] = A[n - 1];
				A[n - 1] = temp;
			}
		}
		generate(n - 1, A, Get);
	}
}

int * GetElements(int *Array, int size) // Only for melee weapons // check is in all classes before removing
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
*/