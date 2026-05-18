#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/PointLightComponent.h"
#include "DronePawn.generated.h"

class ADroneHUD;

UCLASS()
class DRONE_PACK_API ADronePawn : public APawn
{
	GENERATED_BODY()

public:
	ADronePawn();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(
		class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Mesh")
	class USkeletalMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Mesh")
	class USceneComponent* FL_PropellerRoot;
	UPROPERTY(VisibleAnywhere, Category = "Drone|Mesh")
	class USceneComponent* FL_PropellerPivot;
	UPROPERTY(VisibleAnywhere, Category = "Drone|Mesh")
	class USkeletalMeshComponent* FL_PropellerMesh;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Mesh")
	class USceneComponent* FR_PropellerRoot;
	UPROPERTY(VisibleAnywhere, Category = "Drone|Mesh")
	class USceneComponent* FR_PropellerPivot;
	UPROPERTY(VisibleAnywhere, Category = "Drone|Mesh")
	class USkeletalMeshComponent* FR_PropellerMesh;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Mesh")
	class USceneComponent* BL_PropellerRoot;
	UPROPERTY(VisibleAnywhere, Category = "Drone|Mesh")
	class USceneComponent* BL_PropellerPivot;
	UPROPERTY(VisibleAnywhere, Category = "Drone|Mesh")
	class USkeletalMeshComponent* BL_PropellerMesh;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Mesh")
	class USceneComponent* BR_PropellerRoot;
	UPROPERTY(VisibleAnywhere, Category = "Drone|Mesh")
	class USceneComponent* BR_PropellerPivot;
	UPROPERTY(VisibleAnywhere, Category = "Drone|Mesh")
	class USkeletalMeshComponent* BR_PropellerMesh;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Physics")
	class UStaticMeshComponent* PhysicsBody;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Collision")
	USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Camera")
	class UCameraComponent* ThirdPersonCamera;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Camera")
	class UCameraComponent* FPVCamera;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Camera")
	class USceneComponent* GimbalRoot;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Camera")
	class USceneComponent* GimbalYaw;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Camera")
	class USceneComponent* GimbalPitch;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Camera")
	class UCameraComponent* GimbalCamera;

	UPROPERTY(VisibleAnywhere, Category = "Drone|PiP")
	USceneCaptureComponent2D* PiPCapture;

	UPROPERTY(EditAnywhere, Category = "Drone|PiP")
	UTextureRenderTarget2D* PiPRenderTarget;

	UPROPERTY(EditAnywhere, Category = "Drone|PiP")
	float PiPCaptureHeight = 300.f;

	UPROPERTY(EditAnywhere, Category = "Drone|PiP")
	float PiPCaptureDistance = 250.f;

	// -----------------------------------------------------------------------
	// Lights
	// -----------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = "Drone|Lights")
	UPointLightComponent* Light_FL;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Lights")
	UPointLightComponent* Light_FR;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Lights")
	UPointLightComponent* Light_BL;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Lights")
	UPointLightComponent* Light_BR;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Lights")
	UPointLightComponent* Light_Front;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Lights")
	UPointLightComponent* Light_Body;

	UPROPERTY(EditAnywhere, Category = "Drone|Lights")
	float LightBlinkSpeed = 1.5f;

	UPROPERTY(EditAnywhere, Category = "Drone|Lights")
	float LightIntensity = 8000.f;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Lights")
	bool bArmLightsEnabled = true;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Lights")
	bool bBodyLightsEnabled = true;

	// -----------------------------------------------------------------------
	// Gimbal
	// -----------------------------------------------------------------------
	UPROPERTY(EditAnywhere, Category = "Drone|Gimbal")
	float GimbalSmoothSpeed = 10.f;

	UPROPERTY(EditAnywhere, Category = "Drone|Gimbal")
	float GimbalPitchAngle = -30.f;

	UPROPERTY(EditAnywhere, Category = "Drone|Gimbal")
	float GimbalYawAngle = 0.f;

	UPROPERTY(EditAnywhere, Category = "Drone|Gimbal")
	float GimbalRotateSpeed = 60.f;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Gimbal")
	bool bGimbalActive = false;

	// -----------------------------------------------------------------------
	// PID
	// -----------------------------------------------------------------------
	UPROPERTY(EditAnywhere, Category = "Drone|PID")
	float Alt_Kp = 15.f;

	UPROPERTY(EditAnywhere, Category = "Drone|PID")
	float Alt_Ki = 0.05f;

	UPROPERTY(EditAnywhere, Category = "Drone|PID")
	float Alt_Kd = 5.f;

	// -----------------------------------------------------------------------
	// Physics Feel
	// -----------------------------------------------------------------------
	UPROPERTY(EditAnywhere, Category = "Drone|Physics")
	float Mass = 1.5f;

	UPROPERTY(EditAnywhere, Category = "Drone|Physics")
	float MaxRotorThrust = 2400.f;

	UPROPERTY(EditAnywhere, Category = "Drone|Physics")
	float MaxRotorSpeed = 3000.f;

	UPROPERTY(EditAnywhere, Category = "Drone|Feel")
	float ThrottleSpeed = 800.f;

	UPROPERTY(EditAnywhere, Category = "Drone|Feel")
	float PitchSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = "Drone|Feel")
	float RollSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = "Drone|Feel")
	float YawSpeed = 120.f;

	UPROPERTY(EditAnywhere, Category = "Drone|Feel")
	float MaxTiltAngle = 45.f;

	UPROPERTY(EditAnywhere, Category = "Drone|Propellers")
	float PropellerSmoothSpeed = 5.f;

	// -----------------------------------------------------------------------
	// Trail
	// -----------------------------------------------------------------------
	UPROPERTY(EditAnywhere, Category = "Drone|Trail")
	float PathPointDistance = 50.f;

	UPROPERTY(EditAnywhere, Category = "Drone|Trail")
	int32 MaxPathPoints = 500;

	UPROPERTY(EditAnywhere, Category = "Drone|Trail")
	float TrailLineThickness = 3.f;

	UPROPERTY(EditAnywhere, Category = "Drone|Trail")
	bool bShowTrail = true;

	// -----------------------------------------------------------------------
	// Flight Modes
	// -----------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = "Drone|Mode")
	bool bLoiterMode = false;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Mode")
	bool bRTLMode = false;

	UPROPERTY(EditAnywhere, Category = "Drone|Mode")
	float RTLSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category = "Drone|Mode")
	float RTLAcceptRadius = 150.f;

	// -----------------------------------------------------------------------
	// Waypoints
	// -----------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = "Drone|Waypoint")
	bool bWaypointMode = false;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Waypoint")
	int32 CurrentWaypointIndex = 0;

	UPROPERTY(EditAnywhere, Category = "Drone|Waypoint")
	float WaypointAcceptRadius = 200.f;

	UPROPERTY(EditAnywhere, Category = "Drone|Waypoint")
	float WaypointSpeed = 500.f;

	UPROPERTY(EditAnywhere, Category = "Drone|Waypoint")
	float WaypointAltitude = 500.f;

	TArray<FVector> Waypoints;

	// -----------------------------------------------------------------------
	// Motors
	// -----------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = "Drone|Motors")
	float Motor_FL = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Motors")
	float Motor_FR = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Motors")
	float Motor_BL = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Motors")
	float Motor_BR = 0.f;

	// -----------------------------------------------------------------------
	// Flight State
	// -----------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = "Drone|Flight")
	float CurrentAltitude = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Input")
	float Input_Throttle = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Input")
	float Input_Pitch = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Input")
	float Input_Roll = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Input")
	float Input_Yaw = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Input")
	bool bJoystickMode = false;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Input")
	bool bBraking = false;

	bool bFPVMode = false;

	UPROPERTY()
	ADroneHUD* DroneHUD;

	// -----------------------------------------------------------------------
	// Collision
	// -----------------------------------------------------------------------
	UPROPERTY(EditAnywhere, Category = "Drone|Collision")
	float CrashSpeedThreshold = 500.f;

	UPROPERTY(VisibleAnywhere, Category = "Drone|Collision")
	bool bCrashed = false;

	UPROPERTY(EditAnywhere, Category = "Drone|Collision")
	float BounceForce = 0.3f;

	UPROPERTY(EditAnywhere, Category = "Drone|Collision")
	float SphereRadius = 80.f;

private:
	struct FPIDState
	{
		float Integral = 0.f;
		float PrevError = 0.f;
		void Reset() { Integral = 0.f; PrevError = 0.f; }
	};

	FPIDState PID_Alt;
	float ComputePID(FPIDState& State, float Kp, float Ki, float Kd,
		float Error, float DeltaTime);

	FVector DroneVelocity = FVector::ZeroVector;
	float CurrentPitch = 0.f;
	float CurrentRoll = 0.f;
	float TargetAltitude = 0.f;
	float Target_Throttle = 0.f;
	float Target_Pitch = 0.f;
	float Target_Roll = 0.f;
	float Target_Yaw = 0.f;
	float SmoothMotor_FL = 0.f;
	float SmoothMotor_FR = 0.f;
	float SmoothMotor_BL = 0.f;
	float SmoothMotor_BR = 0.f;
	float CurrentGimbalPitch = -30.f;
	float CurrentGimbalYaw = 0.f;

	float LightBlinkTimer = 0.f;
	bool  bLightsOn = true;
	float BodyPulseTimer = 0.f;
	float FrontStrobeTimer = 0.f;

	TArray<FVector> FlightPath;
	FVector LastRecordedPos = FVector::ZeroVector;

	TArray<FVector> RTLPath;
	int32 CurrentRTLIndex = 0;
	bool  bRTLFollowingPath = false;
	bool  bRTLHovering = false;

	FVector LoiterPosition = FVector::ZeroVector;
	FVector HomePosition = FVector::ZeroVector;

	FTimerHandle BrakeTimerHandle;
	FTimerHandle CrashTimerHandle;

	float PropAngle_FL = 0.f;
	float PropAngle_FR = 0.f;
	float PropAngle_BL = 0.f;
	float PropAngle_BR = 0.f;

	void ApplyManualFlight(float DeltaTime);
	void ApplyLoiterFlight(float DeltaTime);
	void ApplyRTLFlight(float DeltaTime);
	void ApplyWaypointFlight(float DeltaTime);
	void UpdateMotorValues();
	void SpinPropellers(float DeltaTime);
	void UpdateGimbal(float DeltaTime);
	void UpdateLights(float DeltaTime);
	void UpdateHUD();
	void UpdateCameras();
	void RecordFlightPath();
	void DrawFlightTrail();
	void ClearFlightPath();
	void DrawWaypoints();
	void ResetBrake();
	void ResetCrash();
	void HandleCollision(const FHitResult& Hit, FVector ImpactNormal);
	bool GetGroundHeight(FVector Position, float& OutGroundZ);
	void CheckGroundCollision(FVector& NewPos);

	UFUNCTION()
	void OnDroneHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);

	void OnThrottleUp(float Value);
	void OnThrottleDown(float Value);
	void OnPitch(float Value);
	void OnRoll(float Value);
	void OnYawLeft();
	void OnYawLeftReleased();
	void OnYawRight();
	void OnYawRightReleased();
	void OnKeyThrottleUp(float Value);
	void OnKeyThrottleDown(float Value);
	void OnKeyPitch(float Value);
	void OnKeyRoll(float Value);
	void OnKeyYawLeft();
	void OnKeyYawLeftReleased();
	void OnKeyYawRight();
	void OnKeyYawRightReleased();
	void OnToggleCamera();
	void OnToggleInputMode();
	void OnToggleGimbal();
	void OnToggleHUD();
	void OnToggleMinimap();
	void OnToggleArmLights();
	void OnToggleBodyLights();
	void OnToggleMotorPanel();
	void OnToggleFlightPanel();
	void OnToggleModePanel();
	void OnToggleInputPanel();
	void OnGimbalPitchUp(float Value);
	void OnGimbalPitchDown(float Value);
	void OnGimbalYawLeft(float Value);
	void OnGimbalYawRight(float Value);
	void OnBrake();
	void OnClearTrail();
	void OnLoiterToggle();
	void OnRTLToggle();
	void OnAddWaypoint();
	void OnStartWaypoint();
	void OnClearWaypoints();
};