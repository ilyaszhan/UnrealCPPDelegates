// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EngineUtils.h"
#include "../../CPPDelegatesCharacter.h"
#include "Components/BoxComponent.h"
#include "SpinningChairSpeedChanger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpeedChange, float, speed);

UCLASS()
class CPPDELEGATES_API ASpinningChairSpeedChanger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpinningChairSpeedChanger();
	
	UPROPERTY()
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	class UBoxComponent* Collider;
		
	UPROPERTY(EditAnywhere)
	UMaterial* MinusMaterial;
			
	UPROPERTY(EditAnywhere)
	UMaterial* PlusMaterial;
		
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PlaneComponent;

	UPROPERTY(BlueprintAssignable, Category="EventDispatchers")
	FOnSpeedChange SpeedChange;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	float Speed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
