// Copyright Epic Games, Inc. All Rights Reserved.

#include "DiegesisBPLibrary.h"
#include "Diegesis.h"
#include "LevelSequencePlayer.h"
#include "MovieSceneSequencePlayer.h"

UDiegesisBPLibrary::UDiegesisBPLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsPlaying = false;
	bIsLooping = false;
	SequencePlayer = nullptr;
}

void UDiegesisBPLibrary::SetSequencePlayer(ULevelSequencePlayer* NewSequencePlayer)
{
	SequencePlayer = NewSequencePlayer;
}

void UDiegesisBPLibrary::SetIsLooping(const bool bNewLooping)
{
	bIsLooping = bNewLooping;
}

void UDiegesisBPLibrary::PlayMovie()
{
	if (!SequencePlayer)
	{
		UE_LOG(LogTemp, Error, TEXT("Must set sequence player before playing movie."));
		return;
	}

	if (bIsLooping)
	{
		SequencePlayer->PlayLooping();
	}
	else
	{
		SequencePlayer->Play();
	}
	bIsPlaying = true;
}

void UDiegesisBPLibrary::PauseMovie()
{
	if (!SequencePlayer)
	{
		UE_LOG(LogTemp, Error, TEXT("Must set sequence player before pausing movie."));
		return;
	}

	SequencePlayer->Pause();
	bIsPlaying = false;
}

void UDiegesisBPLibrary::StopMovie()
{
	if (!SequencePlayer)
	{
		UE_LOG(LogTemp, Error, TEXT("Must set sequence player before stopping movie."));
		return;
	}

	SequencePlayer->Stop();
	bIsPlaying = false;
}

int UDiegesisBPLibrary::GetCurrentFrame(bool& bOutSuccess)
{
	if (!SequencePlayer)
	{
		bOutSuccess = false;
		UE_LOG(LogTemp, Error, TEXT("Must set sequence player before getting current frame."));
		return 0;
	}

	const int32 Frame = SequencePlayer->GetCurrentTime().Time.FrameNumber.Value;
	bOutSuccess = true;
	return Frame;
}

float UDiegesisBPLibrary::GetCurrentTime(bool& bOutSuccess)
{
	if (!SequencePlayer)
	{
		bOutSuccess = false;
		UE_LOG(LogTemp, Error, TEXT("Must set sequence player before getting current time."));
		return 0;
	}

	const double Seconds = SequencePlayer->GetCurrentTime().AsSeconds();
	bOutSuccess = true;
	return Seconds;
}

void UDiegesisBPLibrary::SetCurrentFrame(const int Frame)
{
	if (!SequencePlayer)
	{
		UE_LOG(LogTemp, Error, TEXT("Must set sequence player before setting current frame."));
		return;
	}

	FMovieSceneSequencePlaybackParams PlaybackParams;
	PlaybackParams.Frame = FFrameNumber(Frame);
	PlaybackParams.PositionType = EMovieScenePositionType::Frame;
	PlaybackParams.UpdateMethod = EUpdatePositionMethod::Scrub;

	SequencePlayer->SetPlaybackPosition(PlaybackParams);
}

void UDiegesisBPLibrary::SetCurrentTime(const float Time)
{
	if (!SequencePlayer)
	{
		UE_LOG(LogTemp, Error, TEXT("Must set sequence player before setting current time."));
		return;
	}

	FMovieSceneSequencePlaybackParams PlaybackParams;
	PlaybackParams.Time = Time;
	PlaybackParams.PositionType = EMovieScenePositionType::Time;
	PlaybackParams.UpdateMethod = EUpdatePositionMethod::Scrub;

	SequencePlayer->SetPlaybackPosition(PlaybackParams);
}
