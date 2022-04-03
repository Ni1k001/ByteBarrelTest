// Fill out your copyright notice in the Description page of Project Settings.


#include "ByteBarrelTest/Widgets/SelectorWidget.h"

#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"

void USelectorWidget::NativeConstruct()
{
	ButtonAccept->OnClicked.AddDynamic(this, &USelectorWidget::OnButtonAcceptClicked);
	ButtonCancel->OnClicked.AddDynamic(this, &USelectorWidget::OnButtonCancelClicked);
	SliderIndex->OnValueChanged.AddDynamic(this, &USelectorWidget::OnSliderValueChanged);
}

void USelectorWidget::PrepareSlider(int32 InMaxNum)
{
	MaxNum = InMaxNum;

	SliderIndex->SetStepSize(1.f / float(MaxNum));
	SliderIndex->SetValue(1.f);

	TextBlockIndex->SetText(FText::FromString(FString::FromInt(MaxNum)));
}

void USelectorWidget::OnButtonAcceptClicked()
{
	if (OnAcceptPressed.IsBound())
		OnAcceptPressed.Broadcast(FMath::RoundToInt(SliderIndex->GetValue() * MaxNum));
}

void USelectorWidget::OnButtonCancelClicked()
{
	if (OnCancelPressed.IsBound())
		OnCancelPressed.Broadcast();
}

void USelectorWidget::OnSliderValueChanged(float Value)
{
	TextBlockIndex->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Value * MaxNum))));
}
