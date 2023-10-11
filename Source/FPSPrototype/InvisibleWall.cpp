#include "InvisibleWall.h"
#include "Components/BoxComponent.h"

//InvisibleWall is basically wall that is invisible

AInvisibleWall::AInvisibleWall()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
}

void AInvisibleWall::BeginPlay()
{
	Super::BeginPlay();
	
	Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

class UPrimitiveComponent* AInvisibleWall::GetBox()
{
	return Box;
}

