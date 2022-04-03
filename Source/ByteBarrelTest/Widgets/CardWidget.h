// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "ByteBarrelTest/Structs/CharacterData.h"
#include "Components/TextBlock.h"

#include "CardWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSelectionChange, UCardWidget*, Card, bool, bIsSelected);

UCLASS()
class BYTEBARRELTEST_API UCardWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlockFirstName;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlockLastName;

	UPROPERTY(meta = (BindWidget))
		class UImage* ImagePortrait;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UBorder* Background;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
		FDataTableRowHandle CharacterDataHandle;

	UPROPERTY()
		bool bIsInFirstList;
	
	UPROPERTY(BlueprintReadOnly, Category = "Config")
		bool bIsSelected;

	UPROPERTY(BlueprintAssignable)
		FSelectionChange OnSelectionChanged;

	virtual void InitData();

	UFUNCTION()
		FEventReply OnCardPressed(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	UFUNCTION()
		void ChangeSelection();

	UFUNCTION(BlueprintImplementableEvent)
		void OnCardSelected(bool bInSelected);

	UFUNCTION()
		void ClearSelection();
};