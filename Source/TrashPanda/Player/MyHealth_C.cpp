// All Rights Reserved for Students Graduating TFS Summer 2017

#include "TrashPanda.h"
#include "MyHealth_C.h"


int32   AMyHealth_C::AddHealth(int32 h)
{
	return 0;	//add health into the player call it from the player
}

 void  AMyHealth_C:: Use()
{
	AddHealth(health);
}