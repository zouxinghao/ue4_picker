// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "BatteryCollectorCharacter.generated.h"

UCLASS(config=Game)
class ABatteryCollectorCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Collection Sphere */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollectionSphere;
public:
	ABatteryCollectorCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;


	/**
	*BlueprintPure:只能查看，不能更改函数里面的值
	*BlueprintCallable:可以对函数里面的值进行修改
	*/

	/** Accessor function for initial power**/
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetInitialPower();

	/** Accessor function for current power**/
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetCurrentPower();

	/** Update the character's power**/
	UFUNCTION(BlueprintCallable, Category = "Power")
		void UpdateCurrentPower(float ChangePower);
	

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	//当按下关键字，且物体在CollectionSphere范围内时，被调用
	UFUNCTION(BlueprintCallable,Category="Pickup")
	void  CollectPickup();
	//人物初始的能量值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	float Initialpower;

	//速度的变化率
	UPROPERTY(Editanywhere,BlueprintReadWrite,Category="Speed",meta=(Blueprintprotected="true"))
	float SpeedFactory;

	//初始速度
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Speed", meta = (BlueprintProtected="true"))
	float BaseSpeed;

	//速度改变产生的效果
	UFUNCTION(BlueprintImplementableEvent, Category = "Speed")//应该就是可以被兰提重写，你不用提供函数体，可以直接调用
		void PowerChangeEffect();

	
private:
	UPROPERTY(Visibleanywhere, Category = "Power")
		float CharacterPower;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/**Return CollectionSphere Subobject **/
	FORCEINLINE class USphereComponent* GetSphereCamera() const { return CollectionSphere; }

};

