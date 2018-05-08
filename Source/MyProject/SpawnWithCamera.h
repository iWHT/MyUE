// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Pawn.h"
#include "SpawnWithCamera.generated.h"

UCLASS()
class MYPROJECT_API ASpawnWithCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpawnWithCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* _our_camera_spring_arm;
	UCameraComponent* _our_camera;
	
	FVector2D _move_input;
	FVector2D _camera_input;
	float _zoom_factor;
	bool _b_zooming_in;

	void MoveForward(float axis_value);
	void MoveRight(float axis_value);
	void PitchCamera(float axis_value);
	void YawCamera(float axis_value);
	void ZoomIn();
	void ZoomOut();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	
};
