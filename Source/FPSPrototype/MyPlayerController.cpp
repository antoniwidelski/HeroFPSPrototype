// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"


void AMyPlayerController::BeginPlay()
{
    //Setting up widgets and removing cursor
	Super::BeginPlay();

    HUD = CreateWidget(this, HUDClass);
    if(HUD!=nullptr)
    {
        HUD->AddToViewport();
    }

    CWidget = CreateWidget(this, CWidgetClass);
    
    SetShowMouseCursor(false);
}

void AMyPlayerController::ShowCWidget(bool IsVisible)
{
    //Showing mine detonation "C" widget
    if(CWidget!=nullptr)
    {
        if(IsVisible)
        {
            CWidget->AddToViewport();
        }
        else
        {
            CWidget->RemoveFromParent();
        }
    }
}

void AMyPlayerController::Die()
{
    //Hiding UI after Player's death
    if(HUD!=nullptr)
    {
        if(HUD->IsInViewport())
        {
            HUD->RemoveFromParent();
        }
        
    }
    if(CWidget!=nullptr)
    {
        if(CWidget->IsInViewport())
        {
            CWidget->RemoveFromParent();
        }
    }
}
