#pragma once

class IGlobalVars
{
	float	realTime;
	int		frameCount;
	float	absoluteFrameTime;
	float	absoluteFrameStartTimestdev;
	float	curTime;
	float	frameTime;
	int		maxClients;
	int		tickCount;
	float	intervalPerTick;
	float	interpolationAmount;
	int		simTicksThisFrame;
	int		networkProtocol;
	char	pad00[ 14 ];
};