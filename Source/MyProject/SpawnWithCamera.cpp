// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnWithCamera.h"


// Sets default values
ASpawnWithCamera::ASpawnWithCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	_our_camera_spring_arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	_our_camera_spring_arm->AttachTo(RootComponent);
	_our_camera_spring_arm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f
		, 0.0f, 0.0f));
	_our_camera_spring_arm->TargetArmLength = 400.0f;
	_our_camera_spring_arm->bEnableCameraLag = true;
	_our_camera_spring_arm->CameraLagSpeed = 3.0f;

	_our_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	_our_camera->AttachTo(_our_camera_spring_arm, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ASpawnWithCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_b_zooming_in)
	{
		_zoom_factor += DeltaTime * 0.5f;
	}
	else
	{
		_zoom_factor -= DeltaTime / 0.25f;
	}

	_zoom_factor = FMath::Clamp<float>(_zoom_factor, 0.0f, 1.0f);
	_our_camera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, _zoom_factor);
	_our_camera_spring_arm->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, _zoom_factor);

	FRotator new_rot = _our_camera_spring_arm->GetComponentRotation();
	new_rot.Pitch = FMath::Clamp(new_rot.Pitch + _camera_input.Y, -80.0f, -15.0f);
	_our_camera_spring_arm->SetWorldRotation(new_rot);

	if (!_move_input.IsZero())
	{
		_move_input = _move_input.GetSafeNormal() * 100.0f;
		FVector new_location = GetActorLocation();
		new_location += GetActorForwardVector() * _move_input.X * DeltaTime;
		new_location += GetActorRightVector() * _move_input.Y * DeltaTime;
		SetActorLocation(new_location);
	}

}

// Called to bind functionality to input
void ASpawnWithCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ASpawnWithCamera::ZoomIn);
	InputComponent->BindAction("ZoomIn", IE_Released, this, &ASpawnWithCamera::ZoomOut);

	InputComponent->BindAxis("MoveForward", this, &ASpawnWithCamera::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ASpawnWithCamera::MoveRight);
	InputComponent->BindAxis("CameraPitch", this, &ASpawnWithCamera::PitchCamera);
	InputComponent->BindAxis("CameraYaw", this, &ASpawnWithCamera::YawCamera);

}

void ASpawnWithCamera::MoveForward(float axis_value)
{
	_move_input.X = FMath::Clamp<float>(axis_value, -1.0f, 1.0f);
}
void ASpawnWithCamera::MoveRight(float axis_value)
{
	_move_input.Y = FMath::Clamp<float>(axis_value, -1.0f, 1.0f);
}
void ASpawnWithCamera::PitchCamera(float axis_value)
{
	_camera_input.Y = axis_value;
}
void ASpawnWithCamera::YawCamera(float axis_value)
{
	_camera_input.X = axis_value;
}
void ASpawnWithCamera::ZoomIn()
{
	_b_zooming_in = true;
}
void ASpawnWithCamera::ZoomOut()
{
	_b_zooming_in = false;
}