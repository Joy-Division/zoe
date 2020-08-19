#ifndef INCLUDED_LIBTRG_H
#define INCLUDED_LIBTRG_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

#include "libalg.h"
//#include "libene.h"
//#include "libfrm.h"

// external
class ENE_PARTY;
class FRM_OBJECT;

// internal
class ITEM_DATA;
class BULLET_DATA;
class TRG_STATUS;
class TRG_OBJECT;

//=============================================================================
// Item Data
//=============================================================================

class ITEM_DATA
{
public: //! check modifier
	UINT8		u8ItemNum;
	UINT8*		pu8Item;
	BOOL32		bGet;
	TRG_OBJECT*	ptrgItem;

public:
	void		SetNum( UINT8 );
	void		SetItemData( UINT8* );
	void		SetGetFlag( SINT32 );
	void		SetTrg( TRG_OBJECT* );
	UINT8		Num();
	UINT8*		ItemData();
	SINT32		GetFlag();
	TRG_OBJECT*	Target();
	UINT8		Kind();
};

//=============================================================================
// Bullet Data
//=============================================================================

class BULLET_DATA
{
public: //! check modifier
	UINT8		u8Type;
	TRG_OBJECT*	ptrgBul;

public:
	void		SetType( UINT8 );
	void		SetTrg( TRG_OBJECT* );
	UINT8		Type();
	TRG_OBJECT*	Target();
};

//=============================================================================
// Target Status
//=============================================================================

class TRG_STATUS
{
public: //! check modifier
	UINT16		u16ID;
	UINT16		u16SubID;
	UINT32		u32NameID;
	UINT8		u8Shape;
	ALG_VECTOR	vecSize;
	float		fRadius;
	float		fBoxRad;
	UINT8		u8Prop;
	UINT8		u8Prio;
	UINT8		u8Side;
	UINT8		u8Type;
	UINT16		u16Att;
	float		fPower;
	ALG_MATRIX	matPos;
	UINT8		u8Level;
	float		fMaxArm;
	float		fArmor;
	void*		pvData;

public:
	TRG_STATUS();

	TRG_STATUS& operator = ( const TRG_STATUS& );
};

//=============================================================================
// Target Object
//=============================================================================

class TRG_OBJECT
{
public: //! check modifier
	TRG_STATUS	status;
	TRG_STATUS	staPush;
	TRG_STATUS	staPower;
	TRG_OBJECT*	ptrgPrev;
	TRG_OBJECT*	ptrgNext;

	static TRG_OBJECT*	ptrgList;
	static TRG_OBJECT*	ptrgCurrent;
	static UINT16		u16IDIndex;

protected:
	void PushVecSph( ALG_VECTOR* );
	void PushVecBox( ALG_VECTOR* );

	static int32 CheckSphCol	( TRG_OBJECT*, TRG_OBJECT* );
	static int32 CheckSphBoxCol	( TRG_OBJECT*, TRG_OBJECT* );
	static int32 CheckTrgCol	( TRG_OBJECT*, TRG_OBJECT* );

public:
	TRG_OBJECT();
	~TRG_OBJECT();

	void			SetSubID( UINT16 );
	void			SetNameID( UINT32 );
	void			SetProp( UINT8 );
	void			ResetProp( UINT8 );
	void			SetPrio( UINT8 );
	void			SetSide( UINT8 );
	void			SetType( UINT8 );
	void			SetMat( ALG_MATRIX* );
	void			SetRadius( float );
	void			SetSize( float, float, float );
	void			SetAtt( UINT16 );
	void			ResetAtt( UINT16 );
	void			SetPower( float );
	float			Damage();
	UINT16			ID();
	void			SwapID( TRG_OBJECT* );
	UINT16			SubID();
	UINT32			NameID();
	UINT8			Prop();
	UINT8			Side();
	UINT8			Type();
	UINT16			Att();
	float			Radius();
	ALG_VECTOR&		Size();
	UINT16			PowerID();
	UINT8			PushProp();
	UINT8			PowerProp();
	ALG_MATRIX&		Mat();
	ALG_MATRIX&		PushMat();
	ALG_MATRIX&		PowerMat();
	UINT8			PowerType();
	UINT8			PowerSubID();
	UINT16			PushAtt();
	UINT16			PowerAtt();
	void			PushVector( ALG_VECTOR* );
	void			SetLevel( UINT8 );
	void			SetMaxArm( float );
	void			SetArmor( float );
	void			SetFrame( FRM_OBJECT* );
	void			SetParty( ENE_PARTY* );
	void			SetItem( ITEM_DATA* );
	void			SetBullet( BULLET_DATA* );
	UINT8			Level();
	float			Armor();
	float			MaxArm();
	UINT8			PowerLevel();
	FRM_OBJECT&		Frame();
	FRM_OBJECT&		PowerFrame();
	ENE_PARTY&		Party();
	ITEM_DATA&		Item();
	BULLET_DATA&	Bullet();
	BULLET_DATA&	PowerBullet();

	static void			StartDaemon();
	static void			Execute();
	static TRG_OBJECT*	CheckID( UINT16 );
	static TRG_OBJECT*	CheckNameID( UINT32 );
	static void			Reset();
	static TRG_OBJECT*	Get();

	TRG_OBJECT& operator = ( const TRG_OBJECT& );
};

#endif /* END OF FILE */
