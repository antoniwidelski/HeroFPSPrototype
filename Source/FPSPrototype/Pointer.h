#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pointer.generated.h"

UCLASS()
class FPSPROTOTYPE_API APointer : public AActor
{
	GENERATED_BODY()
	
public:	
	APointer();

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

};
