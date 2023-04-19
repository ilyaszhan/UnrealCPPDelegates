// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinningChair.h"

// Sets default values
ASpinningChair::ASpinningChair()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Scene
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComponent;
	
	// Chair
	ChairMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ChairMeshObject(TEXT("/Game/Meshes/Chair/SM_Toilet.SM_Toilet"));

	if(ChairMeshObject.Object)
	{
		ChairMesh->SetStaticMesh(ChairMeshObject.Object);
	}

	ChairMesh->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void ASpinningChair::ChangeSpinSpeed(float AddSpeed)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Change speed to " + FString::FromInt(AddSpeed)));
	SpinSpeed += AddSpeed;
}

// Called when the game starts or when spawned
void ASpinningChair::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ASpinningChairSpeedChanger> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ActorItr->SpeedChange.AddDynamic(this, &ASpinningChair::ChangeSpinSpeed);
	}
}

// Called every frame
void ASpinningChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ChairMesh->AddLocalRotation(FRotator(0.0f, SpinSpeed, 0.0f));
}

