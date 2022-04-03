// Fill out your copyright notice in the Description page of Project Settings.


#include "ByteBarrelTest/Widgets/CardWidget.h"

#include "ByteBarrelTest/Structs/CharacterData.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UCardWidget::InitData()
{
	Background->OnMouseButtonDownEvent.BindDynamic(this, &UCardWidget::OnCardPressed);
	
	if (CharacterDataHandle.DataTable != nullptr && CharacterDataHandle.RowName != NAME_None)
	{
		const FCharacterData* CharacterData = CharacterDataHandle.GetRow<FCharacterData>(*CharacterDataHandle.RowName.ToString());

		if (CharacterData->FirstName.IsEmpty())
		{
			UE_LOG(LogTemp, Warning, TEXT("%s - First Name is Empty"), *CharacterDataHandle.RowName.ToString());
			TextBlockFirstName->SetText(FText::FromString(TEXT("EMPTY!!!")));
		}
		else
			TextBlockFirstName->SetText(CharacterData->FirstName);
		
		if (CharacterData->LastName.IsEmpty())
		{
			UE_LOG(LogTemp, Warning, TEXT("%s - Last Name is Empty"), *CharacterDataHandle.RowName.ToString());
			TextBlockLastName->SetText(FText::FromString(TEXT("EMPTY!!!")));
		}
		else
			TextBlockLastName->SetText(CharacterData->LastName);

		if (CharacterData->Image == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s - Portrait is NULL"));
		}
		else
			ImagePortrait->SetBrushFromTexture(CharacterData->Image);
	}
	else
	{
			UE_LOG(LogTemp, Warning, TEXT("Invalid DataTable"));
			TextBlockFirstName->SetText(FText::FromString(TEXT("INVALID!!!")));
			TextBlockLastName->SetText(FText::FromString(TEXT("INVALID!!!")));
	}
}

FEventReply UCardWidget::OnCardPressed(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	ChangeSelection();
	return FEventReply(true);
}

void UCardWidget::ChangeSelection()
{
	bIsSelected = !bIsSelected;
	OnCardSelected(bIsSelected);
	
	if (OnSelectionChanged.IsBound())
		OnSelectionChanged.Broadcast(this, bIsSelected);
}


void UCardWidget::ClearSelection()
{
	bIsSelected = false;
	OnCardSelected(bIsSelected);
}