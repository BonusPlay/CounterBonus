#pragma once

#include "../SourceEngine/SDK.hpp"

typedef void(__cdecl *MsgFn)(const char*, ...);
typedef void(__cdecl *WarningFn)(const char*, ...);

class Toolbox
{
private:
	static Toolbox* instance;

	Toolbox();
	~Toolbox();

	Toolbox(const Toolbox&) = delete;

public:
	static Toolbox* getInstance();

	MsgFn msg;
	WarningFn warning;

	SourceEngine::Vector GetEntityBone(SourceEngine::IClientEntity* pEntity, SourceEngine::ECSPlayerBones Bone);
	bool ScreenTransform(const SourceEngine::Vector& point, SourceEngine::Vector& screen);
	bool WorldToScreen(const SourceEngine::Vector &origin, SourceEngine::Vector &screen);

	uint64_t FindSignature(const char* szModule, const char* szSignature);

	bool Clamp(SourceEngine::QAngle &angles);

private:
	void Normalize(SourceEngine::QAngle& angle);
	void ClampAngles(SourceEngine::QAngle &angles);
};