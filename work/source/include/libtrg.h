/*
 * [ LibTRG ]
 * Target Library
 *
 * ver.ZONE OF THE ENDERS
 */
#ifndef INC_LIBTRG_H
#define INC_LIBTRG_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"
#include "libalg.h"
#include "libene.h"
#include "libfrm.h"

// external
class FRM_OBJECT;

// internal
class ITEM_DATA;
class BULLET_DATA;
class TRG_STATUS;
class TRG_OBJECT;

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class ITEM_DATA
{
public: //! unconfirmed modifier
	uint8       u8ItemNum;
	uint8*      pu8Item;
	bool32      bGet;
	TRG_OBJECT* ptrgItem;

public:
	void        SetNum(uint8);
	void        SetItemData(uint8*);
	void        SetGetFlag(sint32);
	void        SetTrg(TRG_OBJECT*);
	uint8       Num();
	uint8*      ItemData();
	sint32      GetFlag();
	TRG_OBJECT* Target();
	uint8       Kind();
};

/*---------------------------------------------------------------------------*/

class BULLET_DATA
{
public: //! unconfirmed modifier
	uint8       u8Type;
	TRG_OBJECT* ptrgBul;

public:
	void        SetType(uint8);
	void        SetTrg(TRG_OBJECT*);
	uint8       Type();
	TRG_OBJECT* Target();
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class TRG_STATUS
{
public: //! unconfirmed modifier
	uint16      u16ID;
	uint16      u16SubID;
	uint32      u32NameID;
	uint8       u8Shape;
	ALG_VECTOR  vecSize;
	float       fRadius;
	float       fBoxRad;
	uint8       u8Prop;
	uint8       u8Prio;
	uint8       u8Side;
	uint8       u8Type;
	uint16      u16Att;
	float       fPower;
	ALG_MATRIX  matPos;
	uint8       u8Level;
	float       fMaxArm;
	float       fArmor;
	void*       pvData;

public:
	TRG_STATUS();
	
	TRG_STATUS& operator=(const TRG_STATUS&);
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class TRG_OBJECT
{
public: //! unconfirmed modifier
	TRG_STATUS  status;
	TRG_STATUS  staPush;
	TRG_STATUS  staPower;
	TRG_OBJECT* ptrgPrev;
	TRG_OBJECT* ptrgNext;

	static TRG_OBJECT*  ptrgList;
	static TRG_OBJECT*  ptrgCurrent;
	static uint16       u16IDIndex;

protected:
	void PushVecSph(ALG_VECTOR*);
	void PushVecBox(ALG_VECTOR*);
	
	static sint32 CheckSphCol(TRG_OBJECT*, TRG_OBJECT*);
	static sint32 CheckSphBoxCol(TRG_OBJECT*, TRG_OBJECT*);
	static sint32 CheckTrgCol(TRG_OBJECT*, TRG_OBJECT*);

public:
	TRG_OBJECT();
	~TRG_OBJECT();
	
	void            SetSubID(uint16);
	void            SetNameID(uint32);
	void            SetProp(uint8);
	void            ResetProp(uint8);
	void            SetPrio(uint8);
	void            SetSide(uint8);
	void            SetType(uint8);
	void            SetMat(ALG_MATRIX*);
	void            SetRadius(float);
	void            SetSize(float, float, float);
	void            SetAtt(uint16);
	void            ResetAtt(uint16);
	void            SetPower(float);
	float           Damage();
	uint16          ID();
	void            SwapID(TRG_OBJECT*);
	uint16          SubID();
	uint32          NameID();
	uint8           Prop();
	uint8           Side();
	uint8           Type();
	uint16          Att();
	float           Radius();
	ALG_VECTOR&     Size();
	uint16          PowerID();
	uint8           PushProp();
	uint8           PowerProp();
	ALG_MATRIX&     Mat();
	ALG_MATRIX&     PushMat();
	ALG_MATRIX&     PowerMat();
	uint8           PowerType();
	uint8           PowerSubID();
	uint16          PushAtt();
	uint16          PowerAtt();
	void            PushVector(ALG_VECTOR*);
	void            SetLevel(uint8);
	void            SetMaxArm(float);
	void            SetArmor(float);
	void            SetFrame(FRM_OBJECT*);
	void            SetParty(ENE_PARTY*);
	void            SetItem(ITEM_DATA*);
	void            SetBullet(BULLET_DATA*);
	uint8           Level();
	float           Armor();
	float           MaxArm();
	uint8           PowerLevel();
	FRM_OBJECT&     Frame();
	FRM_OBJECT&     PowerFrame();
	ENE_PARTY&      Party();
	ITEM_DATA&      Item();
	BULLET_DATA&    Bullet();
	BULLET_DATA&    PowerBullet();
	
	static void         StartDaemon();
	static void         Execute();
	static TRG_OBJECT*  CheckID(uint16);
	static TRG_OBJECT*  CheckNameID(uint32);
	static void         Reset();
	static TRG_OBJECT*  Get();
	
	TRG_OBJECT& operator=(const TRG_OBJECT&);
};

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: cpp; -*- */
/* vim: set noet ts=4 sw=4 ft=cpp ff=dos fenc=euc-jp : */
