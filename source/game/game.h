/*
 *『ZONE OF THE ENDERS』(for PlayStation 2)
 * Copyright (C) Konami Computer Entertainment Japan
 * Codebase Restoration by Joy Division
 */
#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

#include "libalg.h"
#include "libfrm.h"

/*---------------------------------------------------------------------------*
 * Continue Data for GAME Class
 *---------------------------------------------------------------------------*/

// ref.default.pdb
struct CONTINUE_DATA {
	uint8   u8Difficulty;
	uint8   u8PlayerLevel;
	uint16  u16PlayerExp;
	float   fPlayerArmor;
	uint8   u8PlayerLevel2;
	uint16  u16PlayerExp2;
	float   fPlayerArmor2;
	uint8   u8Story;
	uint8   u8CurStage;
	uint8   u8LastStage;
	bool32  bSick;
	uint8   u8CurPassNum;
	uint32  u32GetPassFlag;
	uint32  u32UsePassFlag;
	uint32  u32ProgFlag;
	uint16  u16TrainFlag;
	uint8   u8Weapon;
	uint16  u16BulletNum[11];
	uint16  u16GameFlag;
	uint16  u16GameClear;
	uint16  u16DestEnemy;
	uint16  u16Save;
	uint16  u16Continue;
	uint8   u8RescueRank[5];
	uint16  u16NumMummyheadsDestroyed;
	uint16  u16NumRaptorsDestroyed;
	uint16  u16NumCyclopsesDestroyed;
	uint16  u16NumEnemiesThrown;
	uint16  u16NumBurstAttacks;
	uint16  u16NumBuildingsDestroyed;
	uint8   u8DifficultiesFinished;
	uint8   u8Padding;
	uint16  u16NumPorterKills;
	uint16  u16NumKillsAsRaptor;
	uint16  u16NumKillsHavingVirus;
	uint8   u8Placeholder[22];
};

/*---------------------------------------------------------------------------*
 * Global GAME Class
 *---------------------------------------------------------------------------*/

// ref.default.pdb
class GAME
{
public: //! unconfirmed modifier
	static uint8            u8Mode;
	static uint8            u8State;
	static FRM_OBJECT*      pfrmPlayer;
	static float            fPlayerLockDist;
	static float            fPartyLockDist;
	static uint16           u16EscapeTime;
	static uint8            u8MaxEnemyNum;
	static uint16           u16SpecialAtt;
	static bool32           bLeaveArea;
	static uint32           u32LeaveProc;
	static bool32           bAutoMove;
	static bool32           bNavigate;
	static ALG_VECTOR       vecNaviPos;
	static bool32           bCinema;
	static bool32           bRescue;
	static char*            pszSupVoice;
	static uint32           u32PadMask;
	static uint8            u8HiddenCntr;
	static uint16           u16MaxBulNum[11];
	static uint16           u16AddBulNum[11];
	static CONTINUE_DATA    cont;

public:
	static void         Init();
	static void         SetMode(uint8);
	static void         SetState(uint8);
	static void         SetDifficulty(uint8);
	static void         SetPlayer(FRM_OBJECT *);
	static void         SetPlayerLevel(uint8);
	static void         SetPlayerExp(uint16);
	static void         AddPlayerExp(uint16);
	static void         SubPlayerExp();
	static void         SetPlayerArmor(float);
	static void         ChangePlayerData();
	static void         RestorePlayerData();
	static void         SetWeapon(uint8);
	static void         SetBulletNum(uint8, uint16);
	static void         SetPass(uint8);
	static void         UsePass(uint8);
	static void         SetProgram(uint8);
	static void         ResetProgram(uint8);
	static void         SetTraining(uint8);
	static void         ResetTraining(uint8);
	static void         SetSpecialAtt(uint16);
	static void         SetPlayerLockDist(float);
	static void         SetPartyLockDist(float);
	static void         SetEscapeTime(uint16);
	static void         SetMaxEnemyNum(uint8);
	static void         ResetSpecialAtt(uint16);
	static void         SetLeaveArea();
	static void         ResetLeaveArea();
	static void         SetLeaveAreaProc(uint32);
	static void         SetSick();
	static void         ResetSick();
	static void         CountGameClear();
	static void         CountDestroyEnemy();
	static void         CountSave();
	static void         DiscountSave();
	static void         CountContinue();
	static void         SaveRescueRank(uint8, uint8);
	static void         SetAutoMove();
	static void         ResetAutoMove();
	static void         SetNavigatePos(ALG_VECTOR *);
	static void         SetNavigate();
	static void         ResetNavigate();
	static void         SetCinema();
	static void         ResetCinema();
	static void         SetRescue();
	static void         ResetRescue();
	static void         SetSupportVoice(char *);
	static void         ResetSupportVoice();
	static void         SetPadMask(uint32);
	static void         SetStory(uint8);
	static void         SetCurrentStage(uint8);
	static uint8        Mode();
	static uint8        State();
	static uint8        FirstDifficulty();
	static uint8        CurrentDifficulty();
	static FRM_OBJECT&  Player();
	static FRM_OBJECT*  PlayerPtr();
	static uint8        PlayerLevel();
	static uint16       PlayerExp();
	static float        PlayerMaxArm();
	static float        PlayerArmor();
	static float        PlayerLockDist();
	static float        PartyLockDist();
	static uint8        MaxEnemyNum();
	static uint16       EscapeTime();
	static uint8        Weapon();
	static uint16       BulletNum(uint8);
	static uint16       MaxBulletNum(uint8);
	static uint16       AddBulletNum(uint8);
	static sint32       AllPass(uint8);
	static uint8        CurrentPassNum();
	static sint32       CurrentPass(uint8);
	static sint32       Program(uint8);
	static sint32       Training(uint8);
	static uint16       SpecialAtt();
	static sint32       LeaveArea();
	static void         CallLeaveAreaProc();
	static sint32       AutoMove();
	static sint32       Navigate();
	static void         GetNavigatePos(ALG_VECTOR *);
	static sint32       Cinema();
	static sint32       Rescue();
	static char*        SupportVoice();
	static uint32       PadMask();
	static uint8        Story();
	static uint8        CurrentStage();
	static uint8        LastStage();
	static sint32       Sick();
	static void         SetContinueData(uint8 *);
	static void         GetContinueData(uint8 *);
	static void         UpdateGameflags();
	static void         SetGameflags();
	static void         InitHiddenCommand();
	static void         CheckHiddenCommand();
	static uint16       GetDestEnemy();
	static uint16       GetSaveCount();
	static uint16       GetContinueCount();
	static uint8        GetRescueRank(sint32);
	static void         SetSaveCount(uint16);
	static void         MummyheadDestroyed();
	static void         RaptorDestroyed();
	static void         CyclopsDestroyed();
	static void         PorterDestroyed();
	static void         KillHavingVirus();
	static void         KillAsRaptor();
	static void         EnemyThrown();
	static void         PerformedBurstAttack();
	static void         DestroyedBuilding();
	static void         SetDifficultyFinished(uint8);
	static uint8        GetDifficultiesFinished();
};

#endif /* END OF FILE */
