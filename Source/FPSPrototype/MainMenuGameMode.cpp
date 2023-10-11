#include "MainMenuGameMode.h"
#include "Kismet/GameplayStatics.h"


void AMainMenuGameMode::BeginPlay()
{
    UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
}


