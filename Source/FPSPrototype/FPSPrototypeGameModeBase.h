#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSPrototypeGameModeBase.generated.h"


UCLASS()
class FPSPROTOTYPE_API AFPSPrototypeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:	
	void CharacterKilled(ACharacter* Character);

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> WinScreenClass;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> LoseScreenClass;

	void GameHasEnded(bool Result);
	void RestartLevel();

	FTimerHandle TimerHandle;
	
	int NumberOfEnemies;
};
