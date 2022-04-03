// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "CharacterData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	FText FirstName;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	FText LastName;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	UTexture2D* Image;
};