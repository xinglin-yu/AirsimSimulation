// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VehilceAdvancedHud.generated.h"

UCLASS(config = Game)
class AVehilceAdvancedHud : public AHUD
{
	GENERATED_BODY()

public:
	AVehilceAdvancedHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface

};
