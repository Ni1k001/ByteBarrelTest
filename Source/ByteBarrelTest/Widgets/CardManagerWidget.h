// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "Engine/DataTable.h"

#include "CardManagerWidget.generated.h"

/**
 * 
 */

UCLASS()
class BYTEBARRELTEST_API UCardManagerWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
		bool bFirstListSelected = false;

	UPROPERTY()
		TArray<int32> SelectedIndexes;

	UPROPERTY()
		bool MoveCards;
	
public:
	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<UUserWidget> ListEntryClass;
	
	UPROPERTY(meta = (BindWidget))
		class UScrollBox* List1;

	UPROPERTY(meta = (BindWidget))
		class UScrollBox* List2;

	UPROPERTY(meta = (BindWidget))
		class USelectorWidget* Selector;
	
	UPROPERTY(meta = (BindWidget))
		class UButton* ButtonMoveSelected;

	UPROPERTY(meta = (BindWidget))
		class UButton* ButtonSelectFirstL1;

	UPROPERTY(meta = (BindWidget))
		class UButton* ButtonSelectFirstL2;

	UPROPERTY(meta = (BindWidget))
		class UButton* ButtonSelectLastL1;

	UPROPERTY(meta = (BindWidget))
		class UButton* ButtonSelectLastL2;

	UPROPERTY(meta = (BindWidget))
		class UButton* ButtonSortL1;

	UPROPERTY(meta = (BindWidget))
		class UButton* ButtonSortL2;

	UPROPERTY(meta = (BindWidget))
		class UButton* ButtonAddNew;

	UPROPERTY(meta = (BindWidget))
		class UButton* ButtonReorderL1;

	UPROPERTY(meta = (BindWidget))
		class UButton* ButtonReorderL2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		const UDataTable* CharactersDataTable;

	virtual void NativeConstruct() override;

private:
	/*				BINDINGS				*/
	UFUNCTION()
		void OnButtonMoveSelectedClicked();

	UFUNCTION()
		void OnButtonSelectFirstL1Clicked();

	UFUNCTION()
		void OnButtonSelectFirstL2Clicked();

	UFUNCTION()
		void OnButtonSelectLastL1Clicked();

	UFUNCTION()
		void OnButtonSelectLastL2Clicked();

	UFUNCTION()
		void OnButtonSortL1Clicked();

	UFUNCTION()
		void OnButtonSortL2Clicked();

	UFUNCTION()
		void OnButtonReorderL1Clicked();

	UFUNCTION()
		void OnButtonReorderL2Clicked();

	UFUNCTION()
		void OnCardSelectionChanged(class UCardWidget* Card, bool bIsSelected);

	UFUNCTION()
		void OnAcceptPressed(int32 InIndex);

	UFUNCTION()
		void OnCancelPressed();

	/*				BASE FUNCTIONS				*/
	
	UFUNCTION()
		void MoveSelectedCards(bool bIsFirstList, int32 InIndex = -1);

	UFUNCTION()
		void SelectFirstCard(bool bIsFirstList);

	UFUNCTION()
		void SelectLastCard(bool bIsFirstList);

	UFUNCTION()
		void SortCards(bool bIsFirstList);

	UFUNCTION()
		void AddNewCard();

	UFUNCTION()
		void ReorderCards(bool bIsFirstList, int32 InIndex);
};