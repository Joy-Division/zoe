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

// ref.default.pdb
struct CONTINUE_DATA
{
	uint8	u8Difficulty;

	uint8	u8PlayerLevel;
	uint16	u16PlayerExp;
	float	fPlayerArmor;
	uint8	u8PlayerLevel2;
	uint16	u16PlayerExp2;
	float	fPlayerArmor2;

	uint8	u8Story;			// Story Progress
	uint8	u8CurStage;			// Current Stage
	uint8	u8LastStage;		// Previous Stage
	bool32	bSick;				// ADA Virus Flag

	uint8	u8CurPassNum;		// Password Count
	uint32	u32GetPassFlag;		// Get Password Flag
	uint32	u32UsePassFlag;		// Use Password Flag
	uint32	u32ProgFlag;		// Program Flag
	uint16	u16TrainFlag;		// VR Training Flag

	uint8	u8Weapon;
	uint16	u16BulletNum[11];	// Bullet Number List
	uint16	u16GameFlag;
	uint16	u16GameClear;
	uint16	u16DestEnemy;		// Destroyed Enemies Count

	uint16	u16Save;			// Save Count
	uint16	u16Continue;		// Continue Count

	uint8	u8RescueRank[5];	// RESCUE MISSION Rank List

	uint16	u16NumMummyheadsDestroyed;
	uint16	u16NumRaptorsDestroyed;
	uint16	u16NumCyclopsesDestroyed;
	uint16	u16NumEnemiesThrown;
	uint16	u16NumBurstAttacks;
	uint16	u16NumBuildingsDestroyed;

	uint8	u8DifficultiesFinished;
	uint8	u8Padding;

	uint16	u16NumPorterKills;
	uint16	u16NumKillsAsRaptor;
	uint16	u16NumKillsHavingVirus;

	uint8	u8Placeholder[22];
};

//=============================================================================
// Global GAME Class
//=============================================================================

// ref.default.pdb
class GAME
{
public: //! check modifier

	static uint8		u8Mode;				// Game Mode
	static uint8		u8State;			// Game State

	static FRM_OBJECT*	pfrmPlayer;			// Player Orbital Frame

	static float		fPlayerLockDist;	// Lockon Distance (Player)
	static float		fPartyLockDist;		// Lockon Distance (Enemy Party)
	static uint16		u16EscapeTime;		// ESCAPE Countdown
	static uint8		u8MaxEnemyNum;		// Enemy Limit
	static uint16		u16SpecialAtt;		// Special Attack

	static bool32		bLeaveArea;			// Area Change Flag
	static uint32		u32LeaveProc;		// Area Change Proc ID

	static bool32		bAutoMove;			// Auto Move Flag
	static bool32		bNavigate;			// Navigate Flag
	static ALG_VECTOR	vecNaviPos;			// Navigate Vector

	static bool32		bCinema;			// for DEMO MODE
	static bool32		bRescue;			// for RESCUE MISSION

	static char*		pszSupVoice;		// Support Voice
	static uint32		u32PadMask;			// GamePad Mask

	static uint8		u8HiddenCntr;		// for Konami Command

	static uint16		u16MaxBulNum[11];	// Bullet Num List (MAX)
	static uint16		u16AddBulNum[11];	// Bullet Num List (add)

	static CONTINUE_DATA cont;

public:

	static void Init();

	//
	// ***** SETTERS *****
	//

	static void SetMode( uint8 );
	static void SetState( uint8 );

	static void SetDifficulty( uint8 );

	// Player
	static void SetPlayer( FRM_OBJECT* );
	static void SetPlayerLevel( uint8 );
	static void SetPlayerExp( uint16 );
	static void AddPlayerExp( uint16 );
	static void SubPlayerExp();
	static void SetPlayerArmor( float );
	static void ChangePlayerData();
	static void RestorePlayerData();

	// Weapon & Ammo Value
	static void SetWeapon( uint8 );
	static void SetBulletNum( uint8, uint16 );

	// Itembox Password
	static void SetPass( uint8 );
	static void UsePass( uint8 );

	// Program Module
	static void SetProgram( uint8 );
	static void ResetProgram( uint8 );

	// VR Training Mode
	static void SetTraining( uint8 );
	static void ResetTraining( uint8 );

	// Enemy Encounter
	static void SetSpecialAtt( uint16 );
	static void SetPlayerLockDist( float );
	static void SetPartyLockDist( float );
	static void SetEscapeTime( uint16 );
	static void SetMaxEnemyNum( uint8 );
	static void ResetSpecialAtt( uint16 );

	// Area Change
	static void SetLeaveArea();
	static void ResetLeaveArea();
	static void SetLeaveAreaProc( uint32 );

	// ADA Virus
	static void SetSick();
	static void ResetSick();

	static void CountGameClear();
	static void CountDestroyEnemy();
	static void CountSave();
	static void DiscountSave();
	static void CountContinue();
	static void SaveRescueRank( uint8, uint8 );
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
	static void SetPadMask( uint32 );

	// Game Progress
	static void SetStory( uint8 );
	static void SetCurrentStage( uint8 );

	//
	// ***** GETTERS *****
	//

	static uint8 Mode();	// Get Game Mode
	static uint8 State();	// Get Game State

	static uint8 FirstDifficulty();		// Get First Difficulty
	static uint8 CurrentDifficulty();	// Get Current Difficulty

	static FRM_OBJECT&	Player();		// Get Player Orbital Frame (ref)
	static FRM_OBJECT*	PlayerPtr();	// Get Player Orbital Frame (ptr)
	static uint8		PlayerLevel();	// Get Player Level
	static uint16		PlayerExp();	// Get Player Experience
	static float		PlayerMaxArm();	// Get Player Max Armor
	static float		PlayerArmor();	// Get Player Armor

	static float	PlayerLockDist();	// Get Player Lockon Distance
	static float	PartyLockDist();	// Get Enemy Party Lockon Distance
	static uint8	MaxEnemyNum();		// Get Enemy Limit
	static uint16	EscapeTime();		// Get ESCAPE Countdown

	static uint8	Weapon();				//
	static uint16	BulletNum( uint8 );		//
	static uint16	MaxBulletNum( uint8 );	//
	static uint16	AddBulletNum( uint8 );	//
	static bool32	AllPass( uint8 );		//
	static uint8	CurrentPassNum();		//
	static bool32	CurrentPass( uint8 );	//
	static bool32	Program( uint8 );		//
	static bool32	Training( uint8 );		//
	static uint16	SpecialAtt();			// Get Special Attack

	static bool32	LeaveArea();			// Get Leave Area Flag
	static void		CallLeaveAreaProc();	// Call Leave Area Proc

	static bool32	AutoMove();						// Get Auto Move Flag
	static bool32	Navigate();						// Get Navigate Flag
	static void		GetNavigatePos( ALG_VECTOR* );	// Get Navigate Vector

	static bool32	Cinema();	// Get DEMO MODE status
	static bool32	Rescue();	// Get RESCUE MISSION status

	static char*	SupportVoice();		// Get Support Voice
	static uint32	PadMask();			// Get GamePad Mask

	static uint8	Story();			// Get Story Code
	static uint8	CurrentStage();		// Get Current Stage Code
	static uint8	LastStage();		// Get Previous Stage Code
	static bool32	Sick();				// Get ADA Virus Flag

	static void SetContinueData( uint8* );
	static void GetContinueData( uint8* );

	static void UpdateGameflags();
	static void SetGameflags();

	// Konami Command
	static void InitHiddenCommand();
	static void CheckHiddenCommand();

	static uint16 GetDestEnemy();

	static uint16	GetSaveCount();
	static uint16	GetContinueCount();
	static uint8	GetRescueRank( int32 );
	static void		SetSaveCount( uint16 );

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
	static void		SetDifficultyFinished( uint8 );
	static uint8	GetDifficultiesFinished();
};

#endif /* END OF FILE */
