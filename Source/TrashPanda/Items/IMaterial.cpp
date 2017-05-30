// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "IMaterial.h"

#define print(text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Red,text)

AIMaterial::AIMaterial()
{

}

void AIMaterial::BeginPlay()
{
	Super::BeginPlay();

	MaterialList.Add(TEXT("Lawnmower Blade"));
	MaterialList.Add(TEXT("Newspaper"));
	MaterialList.Add(TEXT("Duct Tape"));
	MaterialList.Add(TEXT("Stick"));
	MaterialList.Add(TEXT("Tin Can"));
	MaterialList.Add(TEXT("Rock"));
	MaterialList.Add(TEXT("Nails"));
	MaterialList.Add(TEXT("Bolts"));
	MaterialList.Add(TEXT("Glue"));
	MaterialList.Add(TEXT("Cloth Scraps"));
	MaterialList.Add(TEXT("Boxing Glove"));
	MaterialList.Add(TEXT("Razor Blade"));
	MaterialList.Add(TEXT("Glass Shard"));
	MaterialList.Add(TEXT("Chicken Bone"));

	itemName = MaterialList[MatType.GetValue()];
}



bool AIMaterial::Consume(int32 toUSE)
{
	if (toUSE >= quantity)
	{
		return true;
	}
	else
	{
		print("Not Enough Materials");
		return false;
	}
}

