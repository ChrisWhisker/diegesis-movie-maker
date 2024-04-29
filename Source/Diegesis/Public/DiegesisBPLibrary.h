// Copyright Chris Worcester All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "DiegesisBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
class ULevelSequencePlayer;

UCLASS()
class UDiegesisBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

private:
	UPROPERTY()
	ULevelSequencePlayer* SequencePlayer;

	bool bIsPlaying;

	bool bIsLooping;

public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set sequence player", Keywords = "play stop"), Category = "Setup")
	void SetSequencePlayer(ULevelSequencePlayer* NewSequencePlayer);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Is Looping", Keywords = "play stop"), Category = "Settings")
	void SetIsLooping(const bool bNewLooping);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Play movie", Keywords = "pause stop"), Category = "Playback")
	void PlayMovie();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pause movie", Keywords = "play stop"), Category = "Playback")
	void PauseMovie();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Play movie", Keywords = "play pause"), Category = "Playback")
	void StopMovie();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get current frame", Keywords = ""), Category = "Playback")
	int GetCurrentFrame(bool& bOutSuccess);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get current time", Keywords = ""), Category = "Playback")
	float GetCurrentTime(bool& bOutSuccess);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set current frame", Keywords = ""), Category = "Playback")
	void SetCurrentFrame(const int Frame);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set current time", Keywords = ""), Category = "Playback")
	void SetCurrentTime(const float Time);
};
