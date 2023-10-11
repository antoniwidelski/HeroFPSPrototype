#include "Pointer.h"
#include "Components/StaticMeshComponent.h"

APointer::APointer()
{
	//Components setup
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}