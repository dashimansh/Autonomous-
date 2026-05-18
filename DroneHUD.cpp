#include "DroneHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"

ADroneHUD::ADroneHUD() {}

void ADroneHUD::UpdateData(
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
	bool bInRTLMode)
{
	Motor_FL = InMotor_FL;
	Motor_FR = InMotor_FR;
	Motor_BL = InMotor_BL;
	Motor_BR = InMotor_BR;
	Altitude = InAltitude;
	Throttle = InThrottle;
	Pitch = InPitch;
	Roll = InRoll;
	Yaw = InYaw;
	bFPVMode = bInFPVMode;
	bJoystickMode = bInJoystickMode;
	bBraking = bInBraking;
	PosX = InPosX;
	PosY = InPosY;
	PosZ = InPosZ;
	bLoiterMode = bInLoiterMode;
	bRTLMode = bInRTLMode;
}

void ADroneHUD::UpdateMinimapData(
	FVector InPos, FRotator InRot,
	float InGimbalYaw, bool bInGimbalOn)
{
	DroneWorldPos = InPos;
	DroneWorldRot = InRot;
	GimbalWorldYaw = InGimbalYaw;
	bGimbalOn = bInGimbalOn;
}

// ---------------------------------------------------------------------------
// Toggle functions
// ---------------------------------------------------------------------------

void ADroneHUD::ToggleHUD()
{
	bHUDVisible = !bHUDVisible;
	if (GEngine) GEngine->AddOnScreenDebugMessage(
		80, 2.f,
		bHUDVisible ? FColor::Green : FColor::Red,
		bHUDVisible
		? TEXT(">> HUD ON (H) <<")
		: TEXT(">> HUD OFF (H) <<"));
}

void ADroneHUD::ToggleMotorPanel()
{
	bMotorPanelVisible = !bMotorPanelVisible;
	if (GEngine) GEngine->AddOnScreenDebugMessage(
		81, 2.f,
		bMotorPanelVisible ? FColor::Green : FColor::Red,
		bMotorPanelVisible
		? TEXT(">> MOTOR THRUST ON (1) <<")
		: TEXT(">> MOTOR THRUST OFF (1) <<"));
}

void ADroneHUD::ToggleFlightPanel()
{
	bFlightPanelVisible = !bFlightPanelVisible;
	if (GEngine) GEngine->AddOnScreenDebugMessage(
		82, 2.f,
		bFlightPanelVisible ? FColor::Green : FColor::Red,
		bFlightPanelVisible
		? TEXT(">> FLIGHT DATA ON (2) <<")
		: TEXT(">> FLIGHT DATA OFF (2) <<"));
}

void ADroneHUD::ToggleModePanel()
{
	bModePanelVisible = !bModePanelVisible;
	if (GEngine) GEngine->AddOnScreenDebugMessage(
		83, 2.f,
		bModePanelVisible ? FColor::Green : FColor::Red,
		bModePanelVisible
		? TEXT(">> MODE PANEL ON (3) <<")
		: TEXT(">> MODE PANEL OFF (3) <<"));
}

void ADroneHUD::ToggleInputPanel()
{
	bInputPanelVisible = !bInputPanelVisible;
	if (GEngine) GEngine->AddOnScreenDebugMessage(
		84, 2.f,
		bInputPanelVisible ? FColor::Green : FColor::Red,
		bInputPanelVisible
		? TEXT(">> INPUT PANEL ON (4) <<")
		: TEXT(">> INPUT PANEL OFF (4) <<"));
}

void ADroneHUD::ToggleMinimap()
{
	bMinimapVisible = !bMinimapVisible;
	if (GEngine) GEngine->AddOnScreenDebugMessage(
		85, 2.f,
		bMinimapVisible ? FColor::Green : FColor::Red,
		bMinimapVisible
		? TEXT(">> MINIMAP ON (M) <<")
		: TEXT(">> MINIMAP OFF (M) <<"));
}

void ADroneHUD::TogglePiP()
{
	bPiPVisible = !bPiPVisible;
	if (GEngine) GEngine->AddOnScreenDebugMessage(
		86, 2.f,
		bPiPVisible ? FColor::Green : FColor::Red,
		bPiPVisible
		? TEXT(">> CAM ON <<")
		: TEXT(">> CAM OFF <<"));
}

// ---------------------------------------------------------------------------
// DrawHUD
// ---------------------------------------------------------------------------

void ADroneHUD::DrawHUD()
{
	Super::DrawHUD();
	if (!Canvas || !bHUDVisible) return;

	if (bMotorPanelVisible)  DrawMotorPanel();
	if (bFlightPanelVisible) DrawFlightData();
	if (bModePanelVisible)   DrawModePanel();
	if (bInputPanelVisible)  DrawInputPanel();
	if (bMinimapVisible)     DrawMinimap();
	if (bPiPVisible)         DrawPiP();
}

// ---------------------------------------------------------------------------
// Motor Thrust Panel
// ---------------------------------------------------------------------------

void ADroneHUD::DrawMotorPanel()
{
	float PX = 10.f, PY = 10.f;
	float PW = 320.f, PH = 170.f;

	DrawRect(ColorDark, PX, PY, PW, PH);
	DrawRect(FLinearColor(0.f, 1.f, 0.5f, 0.3f), PX, PY, PW, 2.f);
	DrawText(TEXT("-- MOTOR THRUST --"),
		ColorGreen, PX + 70.f, PY + 6.f,
		GEngine->GetSmallFont(), 1.1f);

	float BX = PX + 20.f;
	float BY = PY + 30.f;
	float BW = 60.f, BH = 100.f;
	float Gap = 70.f;

	DrawMotorBar(BX, BY, BW, BH, Motor_FL, TEXT("FL"));
	DrawMotorBar(BX + Gap, BY, BW, BH, Motor_FR, TEXT("FR"));
	DrawMotorBar(BX + Gap * 2.f, BY, BW, BH, Motor_BL, TEXT("BL"));
	DrawMotorBar(BX + Gap * 3.f, BY, BW, BH, Motor_BR, TEXT("BR"));
}

void ADroneHUD::DrawMotorBar(
	float X, float Y, float W, float H,
	float Value, const FString& Label)
{
	DrawRect(FLinearColor(0.1f, 0.1f, 0.1f, 1.f), X, Y, W, H);
	float FillH = H * FMath::Clamp(Value, 0.f, 1.f);
	FLinearColor BC = Value > 0.7f ? ColorRed
		: Value > 0.3f ? ColorAmber : ColorGreen;
	DrawRect(BC, X, Y + H - FillH, W, FillH);
	DrawRect(ColorGray, X, Y, W, 1.f);
	DrawRect(ColorGray, X, Y + H, W, 1.f);
	DrawRect(ColorGray, X, Y, 1.f, H);
	DrawRect(ColorGray, X + W, Y, 1.f, H);
	DrawText(FString::Printf(TEXT("%.0f%%"), Value * 100.f),
		ColorWhite, X + 4.f, Y + H + 4.f,
		GEngine->GetSmallFont(), 0.9f);
	DrawText(Label, ColorGreen, X + 4.f, Y - 14.f,
		GEngine->GetSmallFont(), 1.f);
}

// ---------------------------------------------------------------------------
// Flight Data Panel
// ---------------------------------------------------------------------------

void ADroneHUD::DrawFlightData()
{
	float PW = 220.f, PH = 140.f;
	float PX = Canvas->SizeX * 0.5f - PW * 0.5f;
	float PY = 10.f;

	DrawRect(ColorDark, PX, PY, PW, PH);
	DrawRect(FLinearColor(0.f, 1.f, 0.5f, 0.3f), PX, PY, PW, 2.f);
	DrawText(TEXT("-- FLIGHT DATA --"),
		ColorGreen, PX + 40.f, PY + 6.f,
		GEngine->GetSmallFont(), 1.1f);

	float TX = PX + 10.f, TY = PY + 24.f, LS = 16.f;

	DrawText(FString::Printf(TEXT("ALT  : %.2f m"), Altitude),
		ColorCyan, TX, TY, GEngine->GetSmallFont(), 1.f);
	DrawText(FString::Printf(TEXT("PITCH: %.1f"), Pitch),
		ColorWhite, TX, TY + LS, GEngine->GetSmallFont(), 1.f);
	DrawText(FString::Printf(TEXT("ROLL : %.1f"), Roll),
		ColorWhite, TX, TY + LS * 2, GEngine->GetSmallFont(), 1.f);

	DrawRect(ColorGray, PX + 8.f, TY + LS * 3 - 2.f, PW - 16.f, 1.f);

	DrawText(FString::Printf(TEXT("X: %.1f m"), PosX / 100.f),
		ColorGreen, TX, TY + LS * 3, GEngine->GetSmallFont(), 1.f);
	DrawText(FString::Printf(TEXT("Y: %.1f m"), PosY / 100.f),
		ColorGreen, TX, TY + LS * 4, GEngine->GetSmallFont(), 1.f);
	DrawText(FString::Printf(TEXT("Z: %.1f m"), PosZ / 100.f),
		ColorGreen, TX, TY + LS * 5, GEngine->GetSmallFont(), 1.f);
}

// ---------------------------------------------------------------------------
// Mode / Keys Panel
// ---------------------------------------------------------------------------

void ADroneHUD::DrawModePanel()
{
	float PW = 220.f, PH = 250.f;
	float PX = Canvas->SizeX - PW - 10.f;
	float PY = 10.f;

	DrawRect(ColorDark, PX, PY, PW, PH);
	DrawRect(FLinearColor(0.f, 1.f, 0.5f, 0.3f), PX, PY, PW, 2.f);

	float TX = PX + 10.f;
	float TY = PY + 8.f;
	float LS = 16.f;

	FString CamStr = bFPVMode
		? TEXT("CAM : FPV")
		: TEXT("CAM : 3RD");
	DrawText(CamStr, ColorAmber, TX, TY,
		GEngine->GetSmallFont(), 1.f);
	TY += LS;

	DrawText(bJoystickMode
		? TEXT("INPUT: JOYSTICK")
		: TEXT("INPUT: KEYBOARD"),
		ColorWhite, TX, TY, GEngine->GetSmallFont(), 1.f);
	TY += LS;

	DrawText(bBraking
		? TEXT("BRAKE: ON")
		: TEXT("BRAKE: OFF"),
		bBraking ? ColorRed : ColorGray,
		TX, TY, GEngine->GetSmallFont(), 1.f);
	TY += LS;

	DrawText(bLoiterMode
		? TEXT("LOITER: ON")
		: TEXT("LOITER: OFF"),
		bLoiterMode ? ColorCyan : ColorGray,
		TX, TY, GEngine->GetSmallFont(), 1.f);
	TY += LS;

	DrawText(bRTLMode
		? TEXT("RTL: ON")
		: TEXT("RTL: OFF"),
		bRTLMode ? ColorOrange : ColorGray,
		TX, TY, GEngine->GetSmallFont(), 1.f);
	TY += LS + 4.f;

	DrawRect(ColorGray, TX, TY, PW - 20.f, 1.f);
	TY += 6.f;

	DrawText(TEXT("-- KEYS --"), ColorGreen, TX, TY,
		GEngine->GetSmallFont(), 1.f);
	TY += LS;

	const TArray<FString> Keys = {
		TEXT("W/S  = Forward/Back"),
		TEXT("A/D  = Left/Right"),
		TEXT("E/Q  = Up/Down"),
		TEXT("Z/X  = Yaw"),
		TEXT("SPACE= Brake"),
		TEXT("G=Gimbal H=HUD M=Map"),
		TEXT("1=Motor 2=Flight"),
		TEXT("3=Mode  4=Input"),
		TEXT("N=ArmLights V=Body"),
		TEXT("L=Loiter R=RTL"),
		TEXT("C=Cam  T=InputMode"),
	};

	for (const FString& K : Keys)
	{
		DrawText(K, ColorGray, TX, TY,
			GEngine->GetSmallFont(), 0.9f);
		TY += 14.f;
	}
}

// ---------------------------------------------------------------------------
// Input Panel
// ---------------------------------------------------------------------------

void ADroneHUD::DrawInputPanel()
{
	float PX = 10.f;
	float PY = 190.f;
	float PW = 320.f, PH = 110.f;

	DrawRect(ColorDark, PX, PY, PW, PH);
	DrawRect(FLinearColor(0.f, 1.f, 0.5f, 0.3f), PX, PY, PW, 2.f);
	DrawText(TEXT("-- INPUT --"),
		ColorGreen, PX + 110.f, PY + 6.f,
		GEngine->GetSmallFont(), 1.1f);

	float BX = PX + 10.f;
	float BW = PW - 80.f;
	float BY = PY + 26.f;
	float LS = 20.f;

	DrawInputBar(BX, BY, BW, Throttle, TEXT("THROT"));
	DrawInputBar(BX, BY + LS, BW, Pitch, TEXT("PITCH"));
	DrawInputBar(BX, BY + LS * 2, BW, Roll, TEXT("ROLL "));
	DrawInputBar(BX, BY + LS * 3, BW, Yaw, TEXT("YAW  "));
}

void ADroneHUD::DrawInputBar(
	float X, float Y, float W,
	float Value, const FString& Label)
{
	DrawText(Label, ColorGray, X, Y,
		GEngine->GetSmallFont(), 0.9f);

	float BX = X + 55.f;
	float BW = W - 55.f;
	float BH = 10.f;

	DrawRect(FLinearColor(0.1f, 0.1f, 0.1f, 1.f), BX, Y, BW, BH);

	float Mid = BX + BW * 0.5f;
	float Fill = Value * BW * 0.5f;

	if (Fill > 0.f)
		DrawRect(ColorGreen, Mid, Y, Fill, BH);
	else if (Fill < 0.f)
		DrawRect(ColorRed, Mid + Fill, Y, -Fill, BH);

	DrawRect(ColorGray, Mid, Y, 1.f, BH);

	DrawText(FString::Printf(TEXT("%.2f"), Value),
		ColorWhite, BX + BW + 4.f, Y,
		GEngine->GetSmallFont(), 0.9f);
}

// ---------------------------------------------------------------------------
// Minimap
// ---------------------------------------------------------------------------

void ADroneHUD::DrawMinimap()
{
	float MS = MinimapSize;
	float PX = Canvas->SizeX - MS - 10.f;
	float PY = Canvas->SizeY - MS - 10.f;
	float CX = PX + MS * 0.5f;
	float CY = PY + MS * 0.5f;
	float R = MS * 0.5f - 4.f;

	DrawRect(ColorDark, PX, PY, MS, MS);

	int32 Segs = 64;
	for (int32 i = 0; i < Segs; i++)
	{
		float A1 = FMath::DegreesToRadians(360.f / Segs * i);
		float A2 = FMath::DegreesToRadians(360.f / Segs * (i + 1));
		DrawLine(
			CX + FMath::Cos(A1) * R,
			CY + FMath::Sin(A1) * R,
			CX + FMath::Cos(A2) * R,
			CY + FMath::Sin(A2) * R,
			ColorGreen, 1.5f);
	}

	DrawText(TEXT("N"), ColorGreen, CX - 4.f, PY + 2.f,
		GEngine->GetSmallFont(), 1.f);
	DrawText(TEXT("S"), ColorGreen, CX - 4.f, PY + MS - 14.f,
		GEngine->GetSmallFont(), 1.f);
	DrawText(TEXT("W"), ColorGreen, PX + 2.f, CY - 6.f,
		GEngine->GetSmallFont(), 1.f);
	DrawText(TEXT("E"), ColorGreen, PX + MS - 12.f, CY - 6.f,
		GEngine->GetSmallFont(), 1.f);

	DrawText(FString::Printf(TEXT("%.0fm"),
		MinimapRange / 100.f),
		ColorGray, PX + MS - 36.f, PY + MS - 14.f,
		GEngine->GetSmallFont(), 0.85f);

	DrawText(TEXT("MAP"), ColorGreen, PX + 6.f, PY + 4.f,
		GEngine->GetSmallFont(), 0.9f);

	DrawMinimapArrow(CX, CY, DroneWorldRot.Yaw, 12.f, ColorGreen);

	if (bGimbalOn)
	{
		float GimYawRad = FMath::DegreesToRadians(GimbalWorldYaw);
		float ConeSize = 20.f;
		float ConeSpread = 20.f;
		float A1 = GimYawRad - FMath::DegreesToRadians(ConeSpread);
		float A2 = GimYawRad + FMath::DegreesToRadians(ConeSpread);
		DrawLine(CX, CY,
			CX + FMath::Cos(A1) * ConeSize,
			CY + FMath::Sin(A1) * ConeSize,
			FLinearColor(0.f, 0.8f, 1.f, 0.6f), 1.5f);
		DrawLine(CX, CY,
			CX + FMath::Cos(A2) * ConeSize,
			CY + FMath::Sin(A2) * ConeSize,
			FLinearColor(0.f, 0.8f, 1.f, 0.6f), 1.5f);
	}
}

void ADroneHUD::DrawMinimapArrow(
	float CX, float CY, float Angle,
	float Size, FLinearColor Color)
{
	float Rad = FMath::DegreesToRadians(Angle - 90.f);
	float TipX = CX + FMath::Cos(Rad) * Size;
	float TipY = CY + FMath::Sin(Rad) * Size;
	float L1R = Rad + FMath::DegreesToRadians(140.f);
	float L2R = Rad - FMath::DegreesToRadians(140.f);
	float L1X = CX + FMath::Cos(L1R) * Size * 0.6f;
	float L1Y = CY + FMath::Sin(L1R) * Size * 0.6f;
	float L2X = CX + FMath::Cos(L2R) * Size * 0.6f;
	float L2Y = CY + FMath::Sin(L2R) * Size * 0.6f;
	DrawLine(TipX, TipY, L1X, L1Y, Color, 2.f);
	DrawLine(TipX, TipY, L2X, L2Y, Color, 2.f);
	DrawLine(L1X, L1Y, L2X, L2Y, Color, 2.f);
}

// ---------------------------------------------------------------------------
// PiP Camera Box
// ---------------------------------------------------------------------------

void ADroneHUD::DrawPiP()
{
	float PX = Canvas->SizeX - PiPWidth - 10.f;
	float PY = Canvas->SizeY - MinimapSize - PiPHeight - 20.f;
	float CX = PX + PiPWidth * 0.5f;
	float CY = PY + PiPHeight * 0.5f;

	DrawRect(FLinearColor(0.f, 0.f, 0.f, 0.95f),
		PX, PY, PiPWidth, PiPHeight);

	if (PiPTarget)
	{
		Canvas->K2_DrawTexture(
			PiPTarget,
			FVector2D(PX, PY),
			FVector2D(PiPWidth, PiPHeight),
			FVector2D(0.f, 0.f),
			FVector2D(1.f, 1.f),
			FLinearColor::White,
			BLEND_Translucent);
	}

	DrawRect(ColorGreen, PX, PY, PiPWidth, 2.f);
	DrawRect(ColorGreen, PX, PY + PiPHeight - 2.f, PiPWidth, 2.f);
	DrawRect(ColorGreen, PX, PY, 2.f, PiPHeight);
	DrawRect(ColorGreen, PX + PiPWidth - 2.f, PY, 2.f, PiPHeight);

	DrawRect(FLinearColor(0.f, 1.f, 0.5f, 0.4f),
		CX - 20.f, CY - 0.5f, 40.f, 1.f);
	DrawRect(FLinearColor(0.f, 1.f, 0.5f, 0.4f),
		CX - 0.5f, CY - 20.f, 1.f, 40.f);

	float DotSize = 10.f;
	DrawRect(FLinearColor(0.f, 1.f, 0.5f, 1.f),
		CX - DotSize * 0.5f,
		CY - DotSize * 0.5f,
		DotSize, DotSize);

	int32 Segs = 20;
	float Radius = 18.f;
	for (int32 i = 0; i < Segs; i++)
	{
		float A1 = FMath::DegreesToRadians((360.f / Segs) * i);
		float A2 = FMath::DegreesToRadians((360.f / Segs) * (i + 1));
		DrawLine(
			CX + FMath::Cos(A1) * Radius,
			CY + FMath::Sin(A1) * Radius,
			CX + FMath::Cos(A2) * Radius,
			CY + FMath::Sin(A2) * Radius,
			FLinearColor(0.f, 1.f, 0.5f, 0.9f), 1.5f);
	}

	DrawText(TEXT("CAM"), ColorGreen, PX + 6.f, PY + 5.f,
		GEngine->GetSmallFont(), 1.f);
	DrawText(FString::Printf(TEXT("ALT: %.1fm"), Altitude),
		ColorGreen, PX + 6.f, PY + PiPHeight - 16.f,
		GEngine->GetSmallFont(), 0.9f);
}