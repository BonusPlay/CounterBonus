#pragma once

#pragma region FLAGS

#define IN_ATTACK					(1 << 0)
#define IN_JUMP						(1 << 1)
#define IN_DUCK						(1 << 2)
#define IN_FORWARD					(1 << 3)
#define IN_BACK						(1 << 4)
#define IN_USE						(1 << 5)
#define IN_CANCEL					(1 << 6)
#define IN_LEFT						(1 << 7)
#define IN_RIGHT					(1 << 8)
#define IN_MOVELEFT					(1 << 9)
#define IN_MOVERIGHT				(1 << 10)
#define IN_ATTACK2					(1 << 11)
#define IN_RUN						(1 << 12)
#define IN_RELOAD					(1 << 13)
#define IN_ALT1						(1 << 14)
#define IN_ALT2						(1 << 15)
#define IN_SCORE					(1 << 16)   
#define IN_SPEED					(1 << 17)	
#define IN_WALK						(1 << 18)	
#define IN_ZOOM						(1 << 19)	
#define IN_WEAPON1					(1 << 20)	
#define IN_WEAPON2					(1 << 21)
#define IN_BULLRUSH					(1 << 22)
#define IN_GRENADE1					(1 << 23)
#define IN_GRENADE2					(1 << 24)	
#define	IN_ATTACK3					(1 << 25)
#define	FL_ONGROUND					(1 << 0)	
#define FL_DUCKING					(1 << 1)	
#define	FL_WATERJUMP				(1 << 2)	
#define FL_ONTRAIN					(1 << 3)
#define FL_INRAIN					(1 << 4)	
#define FL_FROZEN					(1 << 5)
#define FL_ATCONTROLS				(1 << 6)
#define	FL_CLIENT					(1 << 7)	
#define FL_FAKECLIENT				(1 << 8)	
#define	FL_INWATER					(1 << 9)										
#define	FL_FLY						(1 << 10)	
#define	FL_SWIM						(1 << 11)
#define	FL_CONVEYOR					(1 << 12)
#define	FL_NPC						(1 << 13)
#define	FL_GODMODE					(1 << 14)
#define	FL_NOTARGET					(1 << 15)
#define	FL_AIMTARGET				(1 << 16)	
#define	FL_PARTIALGROUND			(1 << 17)	
#define FL_STATICPROP				(1 << 18)
#define FL_GRAPHED					(1 << 19) 
#define FL_GRENADE					(1 << 20)
#define FL_STEPMOVEMENT				(1 << 21)	
#define FL_DONTTOUCH				(1 << 22)
#define FL_BASEVELOCITY				(1 << 23)
#define FL_WORLDBRUSH				(1 << 24)	
#define FL_OBJECT					(1 << 25) 
#define FL_KILLME					(1 << 26)
#define FL_ONFIRE					(1 << 27)	
#define FL_DISSOLVING				(1 << 28)
#define FL_TRANSRAGDOLL				(1 << 29)
#define FL_UNBLOCKABLE_BY_PLAYER	(1 << 30) 
#define PLAYER_FLAG_BITS			10
#define DISPSURF_FLAG_SURFACE		(1<<0)
#define DISPSURF_FLAG_WALKABLE		(1<<1)
#define DISPSURF_FLAG_BUILDABLE		(1<<2)
#define DISPSURF_FLAG_SURFPROP1		(1<<3)
#define DISPSURF_FLAG_SURFPROP2		(1<<4)

#pragma endregion // FLAGS

enum LifeState : int
{
	LIFE_ALIVE = 0,	// alive
	LIFE_DYING = 1, // playing death animation or still falling off of a ledge waiting to hit ground
	LIFE_DEAD = 2	// dead. lying still.
};

enum EWeaponType
{
	WeapType_Pistol = 0,
	WeapType_Rifle = 1,
	WeapType_SMG = 2,
	WeapType_Sniper = 3,
	WeapType_KnifeType = 4,
	WeapType_Grenade = 5,
	WeapType_LMG = 6,
	WeapType_Shotgun = 7,
	WeapType_ZeusGun = 8,
	WeapType_C4Explosive = 9,
};

enum ESpectatorView
{
	SV_NotSpectating = 0,
	SV_DeathCam = 1,
	SV_FreezeCam = 2,
	SV_Fixed = 3,
	SV_FirstPerson = 4,
	SV_ThirdPerson = 5,
	SV_Free = 6,
};

enum EWeaponIDs
{
	WID_None = 0,
	WID_Deagle = 1,
	WID_Dual_Berettas = 2,
	WID_Five_Seven = 3,
	WID_Glock = 4,
	WID_AK47 = 7,
	WID_AUG = 8,
	WID_AWP = 9,
	WID_FAMAS = 10,
	WID_G3SG1_Auto = 11,
	WID_Galil = 13,
	WID_M249 = 14,
	WID_M4A4 = 16,
	WID_MAC10 = 17,
	WID_P90 = 19,
	WID_UMP45 = 24,
	WID_XM1014 = 25,
	WID_PPBizon = 26,
	WID_MAG7 = 27,
	WID_Negev = 28,
	WID_SawedOff = 29,
	WID_Tec9 = 30,
	WID_Zeus = 31,
	WID_P2000 = 32,
	WID_MP7 = 33,
	WID_MP9 = 34,
	WID_Nova = 35,
	WID_P250 = 36,
	WID_SCAR_Auto = 38,
	WID_SG553 = 39,
	WID_Scout = 40,
	WID_Knife = 42,
	WID_Flashbang = 43,
	WID_HEFrag = 44,
	WID_Smoke = 45,
	WID_Molly = 46,
	WID_Decoy = 47,
	WID_Firebomb = 48,
	WID_C4 = 49,
	WID_MusicKit = 58,
	WID_Default_Knife = 59,
	WID_M4A1S = 60,
	WID_USP = 61,
	WID_TradeUpContract = 62,
	WID_CZ75 = 63,
	WID_Revolver = 64,
	WID_BayonetKnife = 500,
	WID_FlipKnife = 505,
	WID_GutKnife = 506,
	WID_KarambitKnife = 507,
	WID_M9BayonetKnife = 508,
	WID_HuntsmanKnife = 509,
	WID_FalchionKnife = 512,
	WID_BowieKnife = 514,
	WID_ButterflyKnife = 515,
	WID_ShadowDaggerKnife = 516,
};

enum EClassIDs
{
	CID_CAI_BaseNPC = 0,
	CID_CAK47 = 1,
	CID_CBaseAnimating = 2,
	CID_CBaseAnimatingOverlay = 3,
	CID_CBaseAttributableItem = 4,
	CID_CBaseButton = 5,
	CID_CBaseCombatCharacter = 6,
	CID_CBaseCombatWeapon = 7,
	CID_CBaseCSGrenade = 8,
	CID_CBaseCSGrenadeProjectile = 9,
	CID_CBaseDoor = 10,
	CID_CBaseEntity = 11,
	CID_CBaseFlex = 12,
	CID_CBaseGrenade = 13,
	CID_CBaseParticleEntity = 14,
	CID_CBasePlayer = 15,
	CID_CBasePropDoor = 16,
	CID_CBaseTeamObjectiveResource = 17,
	CID_CBaseTempEntity = 18,
	CID_CBaseToggle = 19,
	CID_CBaseTrigger = 20,
	CID_CBaseViewModel = 21,
	CID_CBaseVPhysicsTrigger = 22,
	CID_CBaseWeaponWorldModel = 23,
	CID_CBeam = 24,
	CID_CBeamSpotlight = 25,
	CID_CBoneFollower = 26,
	CID_CBreakableProp = 27,
	CID_CBreakableSurface = 28,
	CID_CC4 = 29,
	CID_CCascadeLight = 30,
	CID_CChicken = 31,
	CID_CColorCorrection = 32,
	CID_CColorCorrectionVolume = 33,
	CID_CCSGameRulesProxy = 34,
	CID_CCSPlayer = 35,
	CID_CCSPlayerResource = 36,
	CID_CCSRagdoll = 37,
	CID_CCSTeam = 38,
	CID_CDEagle = 39,
	CID_CDecoyGrenade = 40,
	CID_CDecoyProjectile = 41,
	CID_CDynamicLight = 42,
	CID_CDynamicProp = 43,
	CID_CEconEntity = 44,
	CID_CEmbers = 45,
	CID_CEntityDissolve = 46,
	CID_CEntityFlame = 47,
	CID_CEntityFreezing = 48,
	CID_CEntityParticleTrail = 49,
	CID_CEnvAmbientLight = 50,
	CID_CEnvDetailController = 51,
	CID_CEnvDOFController = 52,
	CID_CEnvParticleScript = 53,
	CID_CEnvProjectedTexture = 54,
	CID_CEnvQuadraticBeam = 55,
	CID_CEnvScreenEffect = 56,
	CID_CEnvScreenOverlay = 57,
	CID_CEnvTonemapController = 58,
	CID_CEnvWind = 59,
	CID_CFireCrackerBlast = 60,
	CID_CFireSmoke = 61,
	CID_CFireTrail = 62,
	CID_CFish = 63,
	CID_CFlashbang = 64,
	CID_CFogController = 65,
	CID_CFootstepControl = 66,
	CID_CFunc_Dust = 67,
	CID_CFunc_LOD = 68,
	CID_CFuncAreaPortalWindow = 69,
	CID_CFuncBrush = 70,
	CID_CFuncConveyor = 71,
	CID_CFuncLadder = 72,
	CID_CFuncMonitor = 73,
	CID_CFuncMoveLinear = 74,
	CID_CFuncOccluder = 75,
	CID_CFuncReflectiveGlass = 76,
	CID_CFuncRotating = 77,
	CID_CFuncSmokeVolume = 78,
	CID_CFuncTrackTrain = 79,
	CID_CGameRulesProxy = 80,
	CID_CHandleTest = 81,
	CID_CHEGrenade = 82,
	CID_CHostage = 83,
	CID_CHostageCarriableProp = 84,
	CID_CIncendiaryGrenade = 85,
	CID_CInferno = 86,
	CID_CInfoLadderDismount = 87,
	CID_CInfoOverlayAccessor = 88,
	CID_CItem_Healthshot = 89,
	CID_CKnife = 90,
	CID_CKnifeGG = 91,
	CID_CLightGlow = 92,
	CID_CMaterialModifyControl = 93,
	CID_CMolotovGrenade = 94,
	CID_CMolotovProjectile = 95,
	CID_CMovieDisplay = 96,
	CID_CParticleFire = 97,
	CID_CParticlePerformanceMonitor = 98,
	CID_CParticleSystem = 99,
	CID_CPhysBox = 100,
	CID_CPhysBoxMultiplayer = 101,
	CID_CPhysicsProp = 102,
	CID_CPhysicsPropMultiplayer = 103,
	CID_CPhysMagnet = 104,
	CID_CPlantedC4 = 105,
	CID_CPlasma = 106,
	CID_CPlayerResource = 107,
	CID_CPointCamera = 108,
	CID_CPointCommentaryNode = 109,
	CID_CPoseController = 110,
	CID_CPostProcessController = 111,
	CID_CPrecipitation = 112,
	CID_CPrecipitationBlocker = 113,
	CID_CPredictedViewModel = 114,
	CID_CProp_Hallucination = 115,
	CID_CPropDoorRotating = 116,
	CID_CPropJeep = 117,
	CID_CPropVehicleDriveable = 118,
	CID_CRagdollManager = 119,
	CID_CRagdollProp = 120,
	CID_CRagdollPropAttached = 121,
	CID_CRopeKeyframe = 122,
	CID_CSCAR17 = 123,
	CID_CSceneEntity = 124,
	CID_CSensorGrenade = 125,
	CID_CSensorGrenadeProjectile = 126,
	CID_CShadowControl = 127,
	CID_CSlideshowDisplay = 128,
	CID_CSmokeGrenade = 129,
	CID_CSmokeGrenadeProjectile = 130,
	CID_CSmokeStack = 131,
	CID_CSpatialEntity = 132,
	CID_CSpotlightEnd = 133,
	CID_CSprite = 134,
	CID_CSpriteOriented = 135,
	CID_CSpriteTrail = 136,
	CID_CStatueProp = 137,
	CID_CSteamJet = 138,
	CID_CSun = 139,
	CID_CSunlightShadowControl = 140,
	CID_CTeam = 141,
	CID_CTeamplayRoundBasedRulesProxy = 142,
	CID_CTEArmorRicochet = 143,
	CID_CTEBaseBeam = 144,
	CID_CTEBeamEntPoint = 145,
	CID_CTEBeamEnts = 146,
	CID_CTEBeamFollow = 147,
	CID_CTEBeamLaser = 148,
	CID_CTEBeamPoints = 149,
	CID_CTEBeamRing = 150,
	CID_CTEBeamRingPoint = 151,
	CID_CTEBeamSpline = 152,
	CID_CTEBloodSprite = 153,
	CID_CTEBloodStream = 154,
	CID_CTEBreakModel1 = 155,
	CID_CTEBSPDecal = 156,
	CID_CTEBubbles = 157,
	CID_CTEBubbleTrail = 158,
	CID_CTEClientProjectile = 159,
	CID_CTEDecal = 160,
	CID_CTEDust = 161,
	CID_CTEDynamicLight = 162,
	CID_CTEEffectDispatch = 163,
	CID_CTEEnergySplash = 164,
	CID_CTEExplosion = 165,
	CID_CTEFireBullets = 166,
	CID_CTEFizz = 167,
	CID_CTEFootprintDecal = 168,
	CID_CTEFoundryHelpers = 169,
	CID_CTEGaussExplosion = 170,
	CID_CTEGlowSprite = 171,
	CID_CTEImpact = 172,
	CID_CTEKillPlayerAttachments = 173,
	CID_CTELargeFunnel = 174,
	CID_CTEMetalSparks = 175,
	CID_CTEMuzzleFlash = 176,
	CID_CTEParticleSystem = 177,
	CID_CTEPhysicsProp = 178,
	CID_CTEPlantBomb = 179,
	CID_CTEPlayerAnimEvent = 180,
	CID_CTEPlayerDecal = 181,
	CID_CTEProjectedDecal = 182,
	CID_CTERadioIcon = 183,
	CID_CTEShatterSurface = 184,
	CID_CTEShowLine = 185,
	CID_CTesla = 186,
	CID_CTESmoke = 187,
	CID_CTESparks = 188,
	CID_CTESprite = 189,
	CID_CTESpriteSpray = 190,
	CID_CTest_ProxyToggle_Networkable = 191,
	CID_CTestTraceline = 192,
	CID_CTEWorldDecal = 193,
	CID_CTriggerPlayerMovement = 194,
	CID_CTriggerSoundOperator = 195,
	CID_CVGuiScreen = 196,
	CID_CVoteController = 197,
	CID_CWaterBullet = 198,
	CID_CWaterLODControl = 199,
	CID_CWeaponAug = 200,
	CID_CWeaponAWP = 201,
	CID_CWeaponBaseItem = 202,
	CID_CWeaponBizon = 203,
	CID_CWeaponCSBase = 204,
	CID_CWeaponCSBaseGun = 205,
	CID_CWeaponCycler = 206,
	CID_CWeaponElite = 207,
	CID_CWeaponFamas = 208,
	CID_CWeaponFiveSeven = 209,
	CID_CWeaponG3SG1 = 210,
	CID_CWeaponGalil = 211,
	CID_CWeaponGalilAR = 212,
	CID_CWeaponGlock = 213,
	CID_CWeaponHKP2000 = 214,
	CID_CWeaponM249 = 215,
	CID_CWeaponM3 = 216,
	CID_CWeaponM4A1 = 217,
	CID_CWeaponMAC10 = 218,
	CID_CWeaponMag7 = 219,
	CID_CWeaponMP5Navy = 220,
	CID_CWeaponMP7 = 221,
	CID_CWeaponMP9 = 222,
	CID_CWeaponNegev = 223,
	CID_CWeaponNOVA = 224,
	CID_CWeaponP228 = 225,
	CID_CWeaponP250 = 226,
	CID_CWeaponP90 = 227,
	CID_CWeaponSawedoff = 228,
	CID_CWeaponSCAR20 = 229,
	CID_CWeaponScout = 230,
	CID_CWeaponSG550 = 231,
	CID_CWeaponSG552 = 232,
	CID_CWeaponSG556 = 233,
	CID_CWeaponSSG08 = 234,
	CID_CWeaponTaser = 235,
	CID_CWeaponTec9 = 236,
	CID_CWeaponTMP = 237,
	CID_CWeaponUMP45 = 238,
	CID_CWeaponUSP = 239,
	CID_CWeaponXM1014 = 240,
	CID_CWorld = 241,
	CID_DustTrail = 242,
	CID_MovieExplosion = 243,
	CID_ParticleSmokeGrenade = 244,
	CID_RocketTrail = 245,
	CID_SmokeTrail = 246,
	CID_SporeExplosion = 247,
	CID_SporeTrail = 248,

};

struct EBones
{
public:
#define Bone_Spine0 1
#define Bone_Spine1 2
#define Bone_Spine2 3
#define Bone_Spine3 4
#define Bone_Neck 5
#define Bone_Head 6
#define Bone_LeftClavicle 7
#define Bone_LeftUpperarm 8
#define Bone_LeftLowerarm 9
#define Bone_LeftHand 10
#define Bone_RightClavicle 11
#define Bone_RightUpperarm 12
#define Bone_RightLowerarm 13
#define Bone_RightHand 14
#define Bone_LeftUpperleg 15
#define Bone_LeftLowerleg 16
#define Bone_LeftAnkle 17
#define Bone_RightUpperleg 18
#define Bone_RightLowerleg 19
#define Bone_RightAnkle 20
#define Bone_MAX 21

	int bone;
};

enum EHitboxes
{
	// These are outdated as fuck
	HB_Pelvis = 0,
	HB_LeftThigh = 1,
	HB_LeftCalf = 2,
	HB_LeftFoot = 3,
	HB_RightThigh = 4,
	HB_RightCalf = 5,
	HB_RightFoot = 6,
	HB_Spine1 = 7,
	HB_Spine2 = 8,
	HB_Spine3 = 9,
	HB_Neck = 10,
	HB_Head = 11,
	HB_LeftUpperArm = 12,
	HB_LeftForearm = 13,
	HB_LeftHand = 14,
	HB_RightUpperArm = 15,
	HB_RightForearm = 16,
	HB_RightHand = 17,
	HB_LeftClavicle = 18,
	HB_RightClavicle = 19,
	HB_Helmet = 20,
	HB_Spine4 = 21,
};

enum ETeams : int
{
	Team_NoTeam = 0,
	Team_Spectator = 1,
	Team_Terrorists = 2,
	Team_CounterTerrorists = 3,
};

enum ESignOnState : int
{
	SOS_None = 0,
	SOS_Challenge = 1,
	SOS_Connected = 2,
	SOS_New = 3,
	SOS_Prespawn = 4,
	SOS_Spawn = 5,
	SOS_Full = 6,
	SOS_ChangeLevel = 7,
};