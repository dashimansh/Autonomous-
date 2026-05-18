#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/TextureRenderTarget2D.h"
#include "DroneHUD.generated.h"

UCLASS()
class DRONE_PACK_API ADroneHUD : public AHUD
{
	GENERATED_BODY()

public:
	ADroneHUD();
	virtual void DrawHUD() override;

	void UpdateData(
		float InMotor_FL, float InMotor_FR,
		float InMotor_BL, float InMotor_BR,
		float InAltitude,
		float InThrottle, float InPitch,
		float InRoll, float InYaw,
		bool bInFPVMode,
		bool bInJoystickMode,
		bool bInBraking,
		float InPosX, float InPosY, float InPosZ,
		bool bInLoiterMode,
		bool bInRTLMode);

	void UpdateMinimapData(
		FVector InPos,
		FRotator InRot,
		float InGimbalYaw,
		bool bInGimbalOn);

	void SetPiPRenderTarget(UTextureRenderTarget2D* RT)
	{
		PiPTarget = RT;
	}

	// Master toggle (H)
	UPROPERTY(VisibleAnywhere, Category = "HUD")
	bool bHUDVisible = true;

	// Individual panel toggles
	UPROPERTY(VisibleAnywhere, Category = "HUD|Panels")
	bool bMotorPanelVisible = true;

	UPROPERTY(VisibleAnywhere, Category = "HUD|Panels")
	bool bFlightPanelVisible = true;

	UPROPERTY(VisibleAnywhere, Category = "HUD|Panels")
	bool bModePanelVisible = true;

	UPROPERTY(VisibleAnywhere, Category = "HUD|Panels")
	bool bInputPanelVisible = true;

	UPROPERTY(VisibleAnywhere, Category = "HUD|Panels")
	bool bMinimapVisible = true;

	UPROPERTY(VisibleAnywhere, Category = "HUD|Panels")
	bool bPiPVisible = true;

	UPROPERTY(EditAnywhere, Category = "HUD|Minimap")
	float MinimapSize = 200.f;

	UPROPERTY(EditAnywhere, Category = "HUD|Minimap")
	float MinimapRange = 5000.f;

	UPROPERTY(EditAnywhere, Category = "HUD|PiP")
	float PiPWidth = 250.f;

	UPROPERTY(EditAnywhere, Category = "HUD|PiP")
	float PiPHeight = 180.f;

	void ToggleHUD();
	void ToggleMotorPanel();
	void ToggleFlightPanel();
	void ToggleModePanel();
	void ToggleInputPanel();
	void ToggleMinimap();
	void TogglePiP();

private:
	float Motor_FL = 0.f, Motor_FR = 0.f;
	float Motor_BL = 0.f, Motor_BR = 0.f;
	float Altitude = 0.f;
	float Throttle = 0.f, Pitch = 0.f;
	float Roll = 0.f, Yaw = 0.f;
	float PosX = 0.f, PosY = 0.f, PosZ = 0.f;
	bool bFPVMode = false;
	bool bJoystickMode = false;
	bool bBraking = false;
	bool bLoiterMode = false;
	bool bRTLMode = false;

	FVector  DroneWorldPos = FVector::ZeroVector;
	FRotator DroneWorldRot = FRotator::ZeroRotator;
	float    GimbalWorldYaw = 0.f;
	bool     bGimbalOn = false;

	UPROPERTY()
	UTextureRenderTarget2D* PiPTarget = nullptr;

	void DrawMotorPanel();
	void DrawFlightData();
	void DrawInputPanel();
	void DrawModePanel();
	void DrawMinimap();
	void DrawPiP();
	void DrawMinimapArrow(float CX, float CY, float Angle,
		float Size, FLinearColor Color);
	void DrawMotorBar(float X, float Y, float W, float H,
		float Value, const FString& Label);
	void DrawInputBar(float X, float Y, float W,
		float Value, const FString& Label);

	FLinearColor ColorGreen = FLinearColor(0.f, 1.f, 0.5f, 1.f);
	FLinearColor ColorRed = FLinearColor(1.f, 0.2f, 0.2f, 1.f);
	FLinearColor ColorAmber = FLinearColor(1.f, 0.7f, 0.f, 1.f);
	FLinearColor ColorWhite = FLinearColor(1.f, 1.f, 1.f, 1.f);
	FLinearColor ColorCyan = FLinearColor(0.f, 1.f, 1.f, 1.f);
	FLinearColor ColorOrange = FLinearColor(1.f, 0.5f, 0.f, 1.f);
	FLinearColor ColorDark = FLinearColor(0.05f, 0.05f, 0.05f, 0.85f);
	FLinearColor ColorGray = FLinearColor(0.5f, 0.5f, 0.5f, 1.f);
};