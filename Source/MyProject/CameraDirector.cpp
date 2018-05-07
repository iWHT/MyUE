// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const float time_2_camera_changes = 2.0f;
	const float smooth_blend_time = 0.75f;
	_time_to_next_camera_change -= DeltaTime;

	if (_time_to_next_camera_change <= 0.0f)
	{
		_time_to_next_camera_change += time_2_camera_changes;

		APlayerController* our_player_controller = UGameplayStatics::GetPlayerController(this, 0);
		if (our_player_controller)
		{
			if (our_player_controller->GetViewTarget() != _camera_one
				&& _camera_one != nullptr)
			{
				our_player_controller->SetViewTargetWithBlend(_camera_one, smooth_blend_time);
			}
			else if (our_player_controller->GetViewTarget() != _camera_two
				&& _camera_two != nullptr)
			{
				our_player_controller->SetViewTargetWithBlend(_camera_two, smooth_blend_time);
			}
		}

	}


}

