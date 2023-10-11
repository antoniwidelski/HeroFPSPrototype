#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InvisibleWall.generated.h"

UCLASS()
class FPSPROTOTYPE_API AInvisibleWall : public AActor
{
	GENERATED_BODY()
	
public:	
	AInvisibleWall();

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Box;

protected:
	virtual void BeginPlay() override;

public:	
	class UPrimitiveComponent* GetBox();
};
