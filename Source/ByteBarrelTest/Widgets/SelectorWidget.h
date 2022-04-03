// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "SelectorWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAcceptDelegate, int32, InIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCancelDelegate);

UCLASS()
class BYTEBARRELTEST_API USelectorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
		class USlider* SliderIndex;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlockIndex;
	
	UPROPERTY(meta = (BindWidget))
		class UButton* ButtonAccept;

	UPROPERTY(meta = (BindWidget))
		class UButton* ButtonCancel;

	UPROPERTY()
		int32 MaxNum;
	
	UPROPERTY(BlueprintAssignable)
		FAcceptDelegate OnAcceptPressed;

	UPROPERTY(BlueprintAssignable)
		FCancelDelegate OnCancelPressed;
	
	virtual void NativeConstruct() override;

	UFUNCTION()
		void PrepareSlider(int32 InMaxNum);

	UFUNCTION()
		void OnButtonAcceptClicked();

	UFUNCTION()
		void OnButtonCancelClicked();

	UFUNCTION()
		void OnSliderValueChanged(float Value);
};