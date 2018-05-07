// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Create a camera and a visible object
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	_our_visible_component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.

	OurCamera->AttachTo(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	_our_visible_component->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float current_scale = _our_visible_component->GetComponentScale().X;
	if (_b_growing)
	{
		current_scale += DeltaTime;
	}
	else
	{
		current_scale -= (DeltaTime * 0.5f);
	}

	current_scale = FMath::Clamp(current_scale, 1.0f, 2.0f);
	_our_visible_component->SetWorldScale3D(FVector(current_scale));

	if (!_current_velocity.IsZero())
	{
		FVector new_location = GetActorLocation() + (_current_velocity * DeltaTime);
		SetActorLocation(new_location);
	}

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	InputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);
}

void AMyPawn::Move_XAxis(float axis)
{
	_current_velocity.X = FMath::Clamp(axis, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::Move_YAxis(float axis)
{
	_current_velocity.Y = FMath::Clamp(axis, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::StartGrowing()
{
	_b_growing = true;
}

void AMyPawn::StopGrowing()
{
	_b_growing = false;
}

