// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "VehilceAdvancedGameMode.h"
#include "VehilceAdvancedPawn.h"
#include "VehilceAdvancedHud.h"

AVehilceAdvancedGameMode::AVehilceAdvancedGameMode()
{
	DefaultPawnClass = AVehilceAdvancedPawn::StaticClass();
	HUDClass = AVehilceAdvancedHud::StaticClass();
}
