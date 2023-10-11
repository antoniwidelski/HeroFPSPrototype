// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROTOTYPE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> CWidgetClass;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void CooldownEvent(int Ability);

	UUserWidget* HUD;
	UUserWidget* CWidget;

	void ShowCWidget(bool IsVisible);

	void Die();
};
