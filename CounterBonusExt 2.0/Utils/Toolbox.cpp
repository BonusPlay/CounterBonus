#include "Toolbox.h"

Vector velocityComp (Vector enemyPos, Vector enemyVelocity, Vector playerVelocity, float dist)
{
	enemyPos.x += (enemyVelocity.x) / dist;
	enemyPos.y += (enemyVelocity.y) / dist;
	enemyPos.z += (enemyVelocity.z) / dist;
	enemyPos.x -= (playerVelocity.x) / dist;
	enemyPos.y -= (playerVelocity.y) / dist;
	enemyPos.z -= (playerVelocity.z) / dist;
	return enemyPos;
}

float get3ddist (Vector pos1, Vector pos2)
{
	return sqrt (
		powf (pos2.x - pos1.x, 2.0) +
		powf (pos2.y - pos1.y, 2.0) +
		powf (pos2.z - pos1.z, 2.0));
}

QAngle clampAngle (QAngle angles)
{
	if (angles.x > 89.0f && angles.x <= 180.0f)
		angles.x = 89.0f;
	if (angles.x > 180.0f)
		angles.x -= 360.f;
	if (angles.x < -89.0f)
		angles.x = -89.0f;
	if (angles.y > 180.f)
		angles.y -= 360.f;
	if (angles.y < -180.f)
		angles.y += 360.f;
	if (angles.z != 0.0f)
		angles.z = 0.0f;
	return angles;
}

QAngle calcAngle (Vector src, Vector end, Vector punchAngles, Vector viewOrigin)
{
	QAngle angles;
	Vector delta = { (src.x - end.x), (src.y - end.y), (src.z + viewOrigin.z - end.z) };
	float hyp = sqrt (delta.x * delta.x + delta.y * delta.y);
	angles.x = atanf (delta.z / hyp) * 57.295779513082f - punchAngles.x * Settings->pitchMinPunch; // TODO: fix
	angles.y = atanf (delta.y / delta.x) * 57.295779513082f - punchAngles.y * Settings->yawMinPunch; // TODO: fix
	angles.z = 0.0f;
	if (delta.x >= 0.0)
		angles.y += 180.0f;
	return angles;
}

QAngle smoothAngle (QAngle src, QAngle end, float smoothAmount)
{
	QAngle angles;
	angles.x = end.x - src.x;
	angles.y = end.y - src.y;
	angles.z = 0.0f;
	angles = clampAngle (angles);
	angles.x = src.x + angles.x / 100.0f * smoothAmount;
	angles.y = src.y + angles.y / 100.0f * smoothAmount;
	angles.z = 0.0f;
	angles = clampAngle (angles);
	return angles;
}