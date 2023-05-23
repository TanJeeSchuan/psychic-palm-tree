#include <stdlib.h>
#include<stdio.h>

#define PATHLENGTH 257

#pragma warning(disable: 4996)

#pragma region structs

struct country
{
	char tag[4];
	double discipline, morale, tactics, infCombat, cavCombat, artCombat, infDamage, cavDamage, artDamage;
};
struct general
{
	char name[31];
	int fire, shock, manuver, siege, traitID;
};
struct troop
{
	char type[4];
	int atkfire, deffire, atkshock, defshock, atkmorale, defmorale;
};
struct countryDetails
{
	struct country country;
	struct general general;
	struct troop infantry, cavalry, artillery;
};

struct terrain
{
	char terrainType[31];
	int diceroll, river, straits, ampLanding, fort;
};

struct battle
{
	struct countryDetails atkCountry, defCountry;
	struct terrain terrain;
};

#pragma endregion

int initialise_battle(struct battle *battle ,char *atkPath, char *defPath, char *terrainPath);

void main()
{
	struct battle battle;

	if (initialise_battle(&battle, "dataFiles\\atkCountry.txt", "dataFiles\\defCountry.txt", "dataFiles\\terrain.txt") == -1)
	{
		printf("Unable to initailise battle");
		return -1;
	}
	printf("test");
}

int initialise_battle(struct battle* battle, char *atkPath, char *defPath, char *terrainPath)
{
#pragma region Attacking Country
	FILE* fp = fopen(atkPath, "r");
	if (fp == NULL)
	{
		printf("Cannot open file");
		return -1 ;
	}
	if (fscanf(fp, "%*[^\n]\n%*[^\n]\n%*[^\n]\n") != 0)
		return -1;
	if (fscanf(fp, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", &battle->atkCountry.country.tag, &battle->atkCountry.country.discipline, &battle->atkCountry.country.morale, &battle->atkCountry.country.tactics, &battle->atkCountry.country.infCombat, &battle->atkCountry.country.cavCombat, &battle->atkCountry.country.artCombat, &battle->atkCountry.country.infDamage, &battle->atkCountry.country.cavDamage, &battle->atkCountry.country.artDamage) == 0 )
		return -1;
	if (fscanf(fp, "\"%[^\"]\" %d %d %d %d %d", &battle->atkCountry.general.name, &battle->atkCountry.general.fire, &battle->atkCountry.general.shock, &battle->atkCountry.general.manuver, &battle->atkCountry.general.siege, &battle->atkCountry.general.traitID) == 0)
		return -1;
	if (fscanf(fp, "%s %d %d %d %d %d %d", &battle->atkCountry.infantry.type, &battle->atkCountry.infantry.atkfire, &battle->atkCountry.infantry.deffire, &battle->atkCountry.infantry.atkshock, &battle->atkCountry.infantry.defshock, &battle->atkCountry.infantry.atkmorale, &battle->atkCountry.infantry.defmorale) == 0 )
		return -1;
	if (fscanf(fp, "%s %d %d %d %d %d %d", &battle->atkCountry.cavalry.type, &battle->atkCountry.cavalry.atkfire, &battle->atkCountry.cavalry.deffire, &battle->atkCountry.cavalry.atkshock, &battle->atkCountry.cavalry.defshock, &battle->atkCountry.cavalry.atkmorale, &battle->atkCountry.cavalry.defmorale) == 0 )
		return -1;
	if (fscanf(fp, "%s %d %d %d %d %d %d", &battle->atkCountry.artillery.type, &battle->atkCountry.artillery.atkfire, &battle->atkCountry.artillery.deffire, &battle->atkCountry.artillery.atkshock, &battle->atkCountry.artillery.defshock, &battle->atkCountry.artillery.atkmorale, &battle->atkCountry.artillery.defmorale) == 0 )
		return -1;

	fclose(fp);
#pragma endregion

#pragma region Defending Country
	fp = fopen(defPath, "r");
	if (fp == NULL)
	{
		printf("Cannot open file");
		return -1;
	}
	if (fscanf(fp, "%*[^\n]\n%*[^\n]\n%*[^\n]\n") != 0)
		return -1;
	if (fscanf(fp, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", &battle->defCountry.country.tag, &battle->defCountry.country.discipline, &battle->defCountry.country.morale, &battle->defCountry.country.tactics, &battle->defCountry.country.infCombat, &battle->defCountry.country.cavCombat, &battle->defCountry.country.artCombat, &battle->defCountry.country.infDamage, &battle->defCountry.country.cavDamage, &battle->defCountry.country.artDamage) == 0)
		return -1;
	if (fscanf(fp, "\"%[^\"]\" %d %d %d %d %d", &battle->defCountry.general.name, &battle->defCountry.general.fire, &battle->defCountry.general.shock, &battle->defCountry.general.manuver, &battle->defCountry.general.siege, &battle->defCountry.general.traitID) == 0)
		return -1;
	if (fscanf(fp, "%s %d %d %d %d %d %d", &battle->defCountry.infantry.type, &battle->defCountry.infantry.atkfire, &battle->defCountry.infantry.deffire, &battle->defCountry.infantry.atkshock, &battle->defCountry.infantry.defshock, &battle->defCountry.infantry.atkmorale, &battle->defCountry.infantry.defmorale) == 0)
		return -1;
	if (fscanf(fp, "%s %d %d %d %d %d %d", &battle->defCountry.cavalry.type, &battle->defCountry.cavalry.atkfire, &battle->defCountry.cavalry.deffire, &battle->defCountry.cavalry.atkshock, &battle->defCountry.cavalry.defshock, &battle->defCountry.cavalry.atkmorale, &battle->defCountry.cavalry.defmorale) == 0)
		return -1;
	if (fscanf(fp, "%s %d %d %d %d %d %d", &battle->defCountry.artillery.type, &battle->defCountry.artillery.atkfire, &battle->defCountry.artillery.deffire, &battle->defCountry.artillery.atkshock, &battle->defCountry.artillery.defshock, &battle->defCountry.artillery.atkmorale, &battle->defCountry.artillery.defmorale) == 0)
		return -1;

	fclose(fp);
#pragma endregion

#pragma region Terrain
	fp = fopen(terrainPath, "r");
	if (fp == NULL)
	{
		printf("Cannot open file");
		return -1;
	}

	if (fscanf(fp, "%*[^\n]\n") != 0)
		return -1;
	if (fscanf(fp, "%s %d %d %d %d\n", &battle->terrain.terrainType,&battle->terrain.river, &battle->terrain.straits, &battle->terrain.ampLanding, &battle->terrain.fort) == 0)
		return -1;
	fclose(fp);
#pragma endregion
}