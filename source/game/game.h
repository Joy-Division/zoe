#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

#include "libalg.h"
#include "libfrm.h"

//=============================================================================
// Continue Data for GAME Class
//=============================================================================

struct CONTINUE_DATA
{
	UINT8	u8Difficulty;

	UINT8	u8PlayerLevel;
	UINT16	u16PlayerExp;
	float	fPlayerArmor;
	UINT8	u8PlayerLevel2;
	UINT16	u16PlayerExp2;
	float	fPlayerArmor2;

	UINT8	u8Story;			// Story Progress
	UINT8	u8CurStage;			// Current Stage
	UINT8	u8LastStage;		// Previous Stage
	BOOL32	bSick;				// ADA Virus Flag

	UINT8	u8CurPassNum;		// Password Count
	UINT32	u32GetPassFlag;		// Get Password Flag
	UINT32	u32UsePassFlag;		// Use Password Flag
	UINT32	u32ProgFlag;		// Program Flag
	UINT16	u16TrainFlag;		// VR Training Flag

	UINT8	u8Weapon;
	UINT16	u16BulletNum[11];	// Bullet Number List
	UINT16	u16GameFlag;
	UINT16	u16GameClear;
	UINT16	u16DestEnemy;		// Destroyed Enemies Count

	UINT16	u16Save;			// Save Count
	UINT16	u16Continue;		// Continue Count

	UINT8	u8RescueRank[5];	// RESCUE MISSION Rank List

	UINT16	u16NumMummyheadsDestroyed;
	UINT16	u16NumRaptorsDestroyed;
	UINT16	u16NumCyclopsesDestroyed;
	UINT16	u16NumEnemiesThrown;
	UINT16	u16NumBurstAttacks;
	UINT16	u16NumBuildingsDestroyed;

	UINT8	u8DifficultiesFinished;
	UINT8	u8Padding;

	UINT16	u16NumPorterKills;
	UINT16	u16NumKillsAsRaptor;
	UINT16	u16NumKillsHavingVirus;

	UINT8	u8Placeholder[22];
};

//=============================================================================
// Global GAME Class
//=============================================================================

class GAME
{
public: //! check modifier

	static UINT8		u8Mode;				// Game Mode
	static UINT8		u8State;			// Game State

	static FRM_OBJECT*	pfrmPlayer;			// Player Orbital Frame

	static float		fPlayerLockDist;	// Lockon Distance (Player)
	static float		fPartyLockDist;		// Lockon Distance (Enemy Party)
	static UINT16		u16EscapeTime;		// ESCAPE Countdown
	static UINT8		u8MaxEnemyNum;		// Enemy Limit
	static UINT16		u16SpecialAtt;		// Special Attack

	static BOOL32		bLeaveArea;			// Area Change Flag
	static UINT32		u32LeaveProc;		// Area Change Proc ID

	static BOOL32		bAutoMove;			// Auto Move Flag
	static BOOL32		bNavigate;			// Navigate Flag
	static ALG_VECTOR	vecNaviPos;			// Navigate Vector

	static BOOL32		bCinema;			// for DEMO MODE
	static BOOL32		bRescue;			// for RESCUE MISSION

	static char*		pszSupVoice;		// Support Voice
	static UINT32		u32PadMask;			// GamePad Mask

	static UINT8		u8HiddenCntr;		// for Konami Command

	static UINT16		u16MaxBulNum[11];	// Bullet Num List (MAX)
	static UINT16		u16AddBulNum[11];	// Bullet Num List (add)

	static CONTINUE_DATA cont;

public:

	static void Init();

	//
	// ***** SETTERS *****
	//

	static void SetMode( UINT8 );
	static void SetState( UINT8 );

	static void SetDifficulty( UINT8 );

	// Player
	static void SetPlayer( FRM_OBJECT* );
	static void SetPlayerLevel( UINT8 );
	static void SetPlayerExp( UINT16 );
	static void AddPlayerExp( UINT16 );
	static void SubPlayerExp();
	static void SetPlayerArmor( float );
	static void ChangePlayerData();
	static void RestorePlayerData();

	// Weapon & Ammo Value
	static void SetWeapon( UINT8 );
	static void SetBulletNum( UINT8, UINT16 );

	// Itembox Password
	static void SetPass( UINT8 );
	static void UsePass( UINT8 );

	// Program Module
	static void SetProgram( UINT8 );
	static void ResetProgram( UINT8 );

	// VR Training Mode
	static void SetTraining( UINT8 );
	static void ResetTraining( UINT8 );

	// Enemy Encounter
	static void SetSpecialAtt( UINT16 );
	static void SetPlayerLockDist( float );
	static void SetPartyLockDist( float );
	static void SetEscapeTime( UINT16 );
	static void SetMaxEnemyNum( UINT8 );
	static void ResetSpecialAtt( UINT16 );

	// Area Change
	static void SetLeaveArea();
	static void ResetLeaveArea();
	static void SetLeaveAreaProc( UINT32 );

	// ADA Virus
	static void SetSick();
	static void ResetSick();

	static void CountGameClear();
	static void CountDestroyEnemy();
	static void CountSave();
	static void DiscountSave();
	static void CountContinue();
	static void SaveRescueRank( UINT8, UINT8 );
	static void SetAutoMove();
	static void ResetAutoMove();
	static void SetNavigatePos( ALG_VECTOR* );
	static void SetNavigate();
	static void ResetNavigate();
	static void SetCinema();
	static void ResetCinema();
	static void SetRescue();
	static void ResetRescue();
	static void SetSupportVoice( char* );
	static void ResetSupportVoice();
	static void SetPadMask( UINT32 );

	// Game Progress
	static void SetStory( UINT8 );
	static void SetCurrentStage( UINT8 );

	//
	// ***** GETTERS *****
	//

	static UINT8 Mode();	// Get Game Mode
	static UINT8 State();	// Get Game State

	static UINT8 FirstDifficulty();		// Get First Difficulty
	static UINT8 CurrentDifficulty();	// Get Current Difficulty

	static FRM_OBJECT&	Player();		// Get Player Orbital Frame (ref)
	static FRM_OBJECT*	PlayerPtr();	// Get Player Orbital Frame (ptr)
	static UINT8		PlayerLevel();	// Get Player Level
	static UINT16		PlayerExp();	// Get Player Experience
	static float		PlayerMaxArm();	// Get Player Max Armor
	static float		PlayerArmor();	// Get Player Armor

	static float	PlayerLockDist();	// Get Player Lockon Distance
	static float	PartyLockDist();	// Get Enemy Party Lockon Distance
	static UINT8	MaxEnemyNum();		// Get Enemy Limit
	static UINT16	EscapeTime();		// Get ESCAPE Countdown

	static UINT8	Weapon();				//
	static UINT16	BulletNum( UINT8 );		//
	static UINT16	MaxBulletNum( UINT8 );	//
	static UINT16	AddBulletNum( UINT8 );	//
	static BOOL32	AllPass( UINT8 );		//
	static UINT8	CurrentPassNum();		//
	static BOOL32	CurrentPass( UINT8 );	//
	static BOOL32	Program( UINT8 );		//
	static BOOL32	Training( UINT8 );		//
	static UINT16	SpecialAtt();			// Get Special Attack

	static BOOL32	LeaveArea();			// Get Leave Area Flag
	static void		CallLeaveAreaProc();	// Call Leave Area Proc

	static BOOL32	AutoMove();						// Get Auto Move Flag
	static BOOL32	Navigate();						// Get Navigate Flag
	static void		GetNavigatePos( ALG_VECTOR* );	// Get Navigate Vector

	static BOOL32	Cinema();	// Get DEMO MODE status
	static BOOL32	Rescue();	// Get RESCUE MISSION status

	static char*	SupportVoice();		// Get Support Voice
	static UINT32	PadMask();			// Get GamePad Mask

	static UINT8	Story();			// Get Story Code
	static UINT8	CurrentStage();		// Get Current Stage Code
	static UINT8	LastStage();		// Get Previous Stage Code
	static BOOL32	Sick();				// Get ADA Virus Flag

	static void SetContinueData( UINT8* );
	static void GetContinueData( UINT8* );

	static void UpdateGameflags();
	static void SetGameflags();

	// Konami Command
	static void InitHiddenCommand();
	static void CheckHiddenCommand();

	static UINT16 GetDestEnemy();

	static UINT16	GetSaveCount();
	static UINT16	GetContinueCount();
	static UINT8	GetRescueRank( INT32 );
	static void		SetSaveCount( UINT16 );

	static void MummyheadDestroyed();
	static void RaptorDestroyed();
	static void CyclopsDestroyed();
	static void PorterDestroyed();
	static void KillHavingVirus();
	static void KillAsRaptor();
	static void EnemyThrown();
	static void PerformedBurstAttack();
	static void DestroyedBuilding();

	// Cleared Difficulty Utils
	static void		SetDifficultyFinished( UINT8 );
	static UINT8	GetDifficultiesFinished();
};

#endif /* END OF FILE */
