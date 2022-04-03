// Fill out your copyright notice in the Description page of Project Settings.


#include "ByteBarrelTest/Widgets/CardManagerWidget.h"

#include <d3d12sdklayers.h>

#include "SelectorWidget.h"
#include "ByteBarrelTest/Structs/CharacterData.h"

#include "ByteBarrelTest/Widgets/CardWidget.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"

void UCardManagerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	ButtonMoveSelected->OnClicked.AddDynamic(this, &UCardManagerWidget::OnButtonMoveSelectedClicked);
	ButtonSelectFirstL1->OnClicked.AddDynamic(this, &UCardManagerWidget::OnButtonSelectFirstL1Clicked);
	ButtonSelectFirstL2->OnClicked.AddDynamic(this, &UCardManagerWidget::OnButtonSelectFirstL2Clicked);
	ButtonSelectLastL1->OnClicked.AddDynamic(this, &UCardManagerWidget::OnButtonSelectLastL1Clicked);
	ButtonSelectLastL2->OnClicked.AddDynamic(this, &UCardManagerWidget::OnButtonSelectLastL2Clicked);
	ButtonSortL1->OnClicked.AddDynamic(this, &UCardManagerWidget::OnButtonSortL1Clicked);
	ButtonSortL2->OnClicked.AddDynamic(this, &UCardManagerWidget::OnButtonSortL2Clicked);
	ButtonAddNew->OnClicked.AddDynamic(this, &UCardManagerWidget::AddNewCard);
	ButtonReorderL1->OnClicked.AddDynamic(this, &UCardManagerWidget::OnButtonReorderL1Clicked);
	ButtonReorderL2->OnClicked.AddDynamic(this, &UCardManagerWidget::OnButtonReorderL2Clicked);

	Selector->OnAcceptPressed.AddDynamic(this, &UCardManagerWidget::OnAcceptPressed);
	Selector->OnCancelPressed.AddDynamic(this, &UCardManagerWidget::OnCancelPressed);
	Selector->SetVisibility(ESlateVisibility::Hidden);
}

/**
 * 
 */

void UCardManagerWidget::OnButtonMoveSelectedClicked()
{
	if (SelectedIndexes.Num() > 0)
	{
		if (bFirstListSelected)
		{
			if (List2->GetChildrenCount() > 0)
			{
				Selector->PrepareSlider(List2->GetChildrenCount());
				Selector->SetVisibility(ESlateVisibility::Visible);
				MoveCards = true;
			}
			else
				MoveSelectedCards(bFirstListSelected, 0);
		}
		else
		{
			if (List1->GetChildrenCount() > 0)
			{
				Selector->PrepareSlider(List1->GetChildrenCount());
				Selector->SetVisibility(ESlateVisibility::Visible);
				MoveCards = true;
			}
			else
				MoveSelectedCards(bFirstListSelected, 0);
		}
	}
}

void UCardManagerWidget::OnButtonSelectFirstL1Clicked()
{
	SelectFirstCard(true);
}

void UCardManagerWidget::OnButtonSelectFirstL2Clicked()
{
	SelectFirstCard(false);
}

void UCardManagerWidget::OnButtonSelectLastL1Clicked()
{
	SelectLastCard(true);
}

void UCardManagerWidget::OnButtonSelectLastL2Clicked()
{
	SelectLastCard(false);
}

void UCardManagerWidget::OnButtonSortL1Clicked()
{
	SortCards(true);
}

void UCardManagerWidget::OnButtonSortL2Clicked()
{
	SortCards(false);
}

void UCardManagerWidget::OnButtonReorderL1Clicked()
{
	if (SelectedIndexes.Num() > 0)
	{
		if (List1->GetChildrenCount() > 1)
		{
			Selector->PrepareSlider(List1->GetChildrenCount());
			Selector->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UCardManagerWidget::OnButtonReorderL2Clicked()
{
	if (SelectedIndexes.Num() > 0)
	{
		if (List2->GetChildrenCount() > 1)
		{
			Selector->PrepareSlider(List2->GetChildrenCount());
			Selector->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UCardManagerWidget::OnCardSelectionChanged(UCardWidget* Card, bool bIsSelected)
{
	if (bIsSelected)
	{
		if (SelectedIndexes.Num() > 0)
		{
			if (Card->bIsInFirstList && bFirstListSelected)
			{
				if (List1->HasChild(Card))
					SelectedIndexes.Add(List1->GetChildIndex(Card));
			}
			else if (!Card->bIsInFirstList && !bFirstListSelected)
			{
				if (List2->HasChild(Card))
					SelectedIndexes.Add(List2->GetChildIndex(Card));
			}
			else
			{
				for (int32 Index : SelectedIndexes)
				{
					UCardWidget* TempCard = nullptr;
					
					if (bFirstListSelected)
						TempCard = Cast<UCardWidget>(List1->GetChildAt(Index));
					else
						TempCard = Cast<UCardWidget>(List2->GetChildAt(Index));

					if (TempCard)
						TempCard->ClearSelection();
				}
				
				SelectedIndexes.Empty();

				bFirstListSelected = Card->bIsInFirstList;
				
				if (bFirstListSelected)
				{
					if (List1->HasChild(Card))
						SelectedIndexes.Add(List1->GetChildIndex(Card));
				}
				else
				{
					if (List2->HasChild(Card))
						SelectedIndexes.Add(List2->GetChildIndex(Card));
				}
			}
		}
		else
		{
			bFirstListSelected = Card->bIsInFirstList;
				
			if (bFirstListSelected)
			{
				if (List1->HasChild(Card))
					SelectedIndexes.Add(List1->GetChildIndex(Card));
			}
			else
			{
				if (List2->HasChild(Card))
					SelectedIndexes.Add(List2->GetChildIndex(Card));
			}
		}
	}
	else
	{
		if (Card->bIsInFirstList && bFirstListSelected)
		{
			if (List1->HasChild(Card))
				SelectedIndexes.Remove(List1->GetChildIndex(Card));
		}
		else
		{
			if (List2->HasChild(Card))
				SelectedIndexes.Remove(List2->GetChildIndex(Card));
		}
	}
}

void UCardManagerWidget::OnAcceptPressed(int32 InIndex)
{
	if (MoveCards)
		MoveSelectedCards(bFirstListSelected, InIndex);
	else
		ReorderCards(bFirstListSelected, InIndex);

	Selector->SetVisibility(ESlateVisibility::Hidden);
	MoveCards = false;
}

void UCardManagerWidget::OnCancelPressed()
{
	Selector->SetVisibility(ESlateVisibility::Hidden);
	MoveCards = false;
}

/**
 * 
 */

void UCardManagerWidget::MoveSelectedCards(bool bIsFirstList, int32 InIndex)
{
	if (SelectedIndexes.Num() > 1)
		SelectedIndexes.StableSort();

	if (bIsFirstList)
	{
		for (int32 i = SelectedIndexes.Num() - 1; i >= 0; i--)
		{
			Cast<UCardWidget>(List1->GetChildAt(SelectedIndexes[i]))->ClearSelection();
			List2->InsertChildAt(InIndex, List1->GetChildAt(SelectedIndexes[i]));
			Cast<UCardWidget>(List2->GetChildAt(InIndex))->bIsInFirstList = false;
		}

		TArray<UWidget*> Temp = List2->GetAllChildren();
		List2->ClearChildren();
		
		for (int32 i = 0; i < Temp.Num(); i++)
			List2->AddChild(Temp[i]);
	}
	else
	{
		for (int32 i = SelectedIndexes.Num() - 1; i >= 0; i--)
		{
			Cast<UCardWidget>(List2->GetChildAt(SelectedIndexes[i]))->ClearSelection();
			List1->InsertChildAt(InIndex, List2->GetChildAt(SelectedIndexes[i]));
			Cast<UCardWidget>(List1->GetChildAt(InIndex))->bIsInFirstList = true;
		}

		TArray<UWidget*> Temp = List2->GetAllChildren();
		List2->ClearChildren();
		
		for (int32 i = 0; i < Temp.Num(); i++)
			List2->AddChild(Temp[i]);
	}

	SelectedIndexes.Empty();
}

void UCardManagerWidget::SelectFirstCard(bool bIsFirstList)
{
	if (bIsFirstList)
	{
		if (List1->HasAnyChildren())
			Cast<UCardWidget>(List1->GetChildAt(0))->ChangeSelection();
	}
	else
	{
		if (List2->HasAnyChildren())
			Cast<UCardWidget>(List2->GetChildAt(0))->ChangeSelection();
	}
}

void UCardManagerWidget::SelectLastCard(bool bIsFirstList)
{
	if (bIsFirstList)
	{
		if (List1->HasAnyChildren())
			Cast<UCardWidget>(List1->GetChildAt(List1->GetChildrenCount() - 1))->ChangeSelection();
	}
	else
	{
		if (List2->HasAnyChildren())
			Cast<UCardWidget>(List2->GetChildAt(List2->GetChildrenCount() - 1))->ChangeSelection();
	}
}

void UCardManagerWidget::SortCards(bool bIsFirstList)
{
	if (bIsFirstList)
	{
		if (List1->GetChildrenCount() > 1)
		{
			TArray<UCardWidget*> List;
			
			for(UPanelSlot* ChildSlot : List1->GetSlots())
				List.Add(Cast<UCardWidget>(ChildSlot->Content));
			
			List.Sort([](const UCardWidget& A, const UCardWidget& B)
				{
					return A.TextBlockLastName->GetText().ToString() < B.TextBlockLastName->GetText().ToString();
				});
			
			for (int i = 0; i < List.Num(); i++)
			{
				List1->RemoveChild(List[i]);
				List1->InsertChildAt(i, List[i]);
			}
		}
	}
	else
	{
		if (List2->GetChildrenCount() > 1)
		{
			TArray<UCardWidget*> List;
			
			for(UPanelSlot* ChildSlot : List2->GetSlots())
				List.Add(Cast<UCardWidget>(ChildSlot->Content));
			
			List.Sort([](const UCardWidget& A, const UCardWidget& B)
				{
					return A.TextBlockLastName->GetText().ToString() < B.TextBlockLastName->GetText().ToString();
				});
			
			for (int i = 0; i < List.Num(); i++)
			{
				List2->RemoveChild(List[i]);
				List2->InsertChildAt(i, List[i]);
			}
		}
	}
}

void UCardManagerWidget::AddNewCard()
{
	if (ListEntryClass != nullptr)
	{
		UUserWidget* NewCard = CreateWidget(this, ListEntryClass);
		List1->AddChild(NewCard);

		if (GetParentNativeClass(NewCard->GetClass()) == UCardWidget::StaticClass())
		{
			Cast<UCardWidget>(NewCard)->bIsInFirstList = true;
			Cast<UCardWidget>(NewCard)->OnSelectionChanged.AddDynamic(this, &UCardManagerWidget::OnCardSelectionChanged);

			if (CharactersDataTable != nullptr)
			{
				Cast<UCardWidget>(NewCard)->CharacterDataHandle.DataTable = CharactersDataTable;
				Cast<UCardWidget>(NewCard)->CharacterDataHandle.RowName = (CharactersDataTable->GetRowNames())[FMath::RandRange(0, CharactersDataTable->GetRowNames().Num() - 1)];
			}

			Cast<UCardWidget>(NewCard)->InitData();
		}
	}
}

void UCardManagerWidget::ReorderCards(bool bIsFirstList, int32 InIndex)
{
	if (SelectedIndexes.Num() > 1)
		SelectedIndexes.StableSort();

	if (bIsFirstList)
	{
		TArray<UWidget*> Temp;
		for (int32 i = SelectedIndexes.Num() - 1; i >= 0; i--)
			Temp.Add(List1->GetChildAt(SelectedIndexes[i]));
		
		for (int32 i = 0; i < SelectedIndexes.Num(); i++)
		{
			List1->ShiftChild(InIndex, Temp[i]);
		}
		
		Temp = List1->GetAllChildren();
		List1->ClearChildren();
		
		for (int32 i = 0; i < Temp.Num(); i++)
			List1->AddChild(Temp[i]);
	}
	else
	{
		TArray<UWidget*> Temp;
		for (int32 i = SelectedIndexes.Num() - 1; i >= 0; i--)
			Temp.Add(List2->GetChildAt(SelectedIndexes[i]));
		
		for (int32 i = 0; i < SelectedIndexes.Num(); i++)
		{
			List2->ShiftChild(InIndex, Temp[i]);
		}
		
		Temp = List2->GetAllChildren();
		List2->ClearChildren();
		
		for (int32 i = 0; i < Temp.Num(); i++)
			List2->AddChild(Temp[i]);
	}

	SelectedIndexes.Empty();
}