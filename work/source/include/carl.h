#ifndef INC_CARL_H
#define INC_CARL_H

#include "global.h"
#include "zoe_types.h"
#include "libdg.h"
#include "libgv.h"

/* (bgsphere.cc) */
void CR_SetStageLoad( char *, sint32, char **, sint32 );
void CR_SetStageLoad( u_char, sint32, char **, sint32 );

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class CR_EDGE:
  public GV_ACTOR //! unconfirmed modifier
{
public: //! unconfirmed modifier
	DG_OBJ_QUE      que;
	DG_OBJ_POLYGON  polAlp1;
	DG_VERTEX       vertAlp1[2];
	DAT128          tagAlp1[4];
	DG_OBJ_POLYGON  polAlp2;
	DG_VERTEX       vertAlp2[2];
	DAT128          tagAlp2[3];
	DG_OBJ_POLYGON  polShift1;
	DG_VERTEX       vertShift1[4];
	DAT128          tagShift1[4];
	DG_OBJ_POLYGON  polShift2;
	DG_VERTEX       vertShift2[4];
	DG_OBJ_POLYGON  polEdge;
	DG_VERTEX       vertEdge[2];
	DAT128          tagEdge[3];
	ALG_MATRIX*     pmatRef;
	ALG_VECTOR      vecSize;
	ALG_VECTOR      vecCol;
	float32         fWidth;

public:
	CR_EDGE(const CR_EDGE&);
	CR_EDGE(ALG_MATRIX*, ALG_VECTOR*);
	~CR_EDGE();
	
	void Invisible();
	void Visible();
	void Act();
	
	CR_EDGE& operator=(CR_EDGE&);
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class CR_WINDOW
{
public: //! unconfirmed modifier
	float32         fXwindow;
	float32         fYwindow;
	float32         fWrange;
	float32         fHrange;
	float32         fXrange;
	float32         fYrange;
	DG_OBJ_QUE      que;
	DG_OBJ_POLYGON  polTitle;
	DG_OBJ_POLYGON  polFrame0;
	DG_OBJ_POLYGON  polFrame1;
	DG_OBJ_POLYGON  polBottom;
	DG_OBJ_POLYGON  polArea;
	DG_OBJ_POLYGON  polBar0;
	DG_OBJ_POLYGON  polBar1;
	DG_OBJ_CALLBACK callSet;
	DG_OBJ_CALLBACK callClear;
	DG_VERTEX       vertTitle[6];
	DG_VERTEX       vertFrame0[6];
	DG_VERTEX       vertFrame1[6];
	DG_VERTEX       vertBottom[2];
	DG_VERTEX       vertBar0[2];
	DG_VERTEX       vertBar1[2];
	DG_VERTEX       vertArea[2];
	DAT128          tagArea[3];
	DAT128          tagFrame0[3];
	sint32          ctr;
	
	enum STATE {
		OPEN,
		CLOSE
	} st;
	
	CR_WINDOW*      pPrev;
	CR_WINDOW*      pNext;
//  bool            m_bXPositionAdjustedinWS;   // HVS addition
//  float           m_fXAmountAdjustedinWS;     // HVS addition

	static class CR_WINDOW* pWinTop;

protected:
	void Unlink();
	void SetZ();
	void Validate();

public: //! unconfirmed modifier
	static const float32 fWLine = TEMP_ZERO;
	static const float32 fHLine = TEMP_ZERO;
	static const float32 fHTitle = TEMP_ZERO;

public:
	CR_WINDOW();
	~CR_WINDOW();
	
	void Init(sint32, sint32, sint32, sint32);
	void SetOffset(sint32, sint32);
	void SetPosition(sint32, sint32);
	void SetPositionWideScreen(sint32, sint32, sint32, sint32);
	void SetArea(sint32, sint32);
	void SetFrameColor(float32, float32, float32, float32);
	void SetBgColor(float32, float32, float32, float32);
	void SetOrder(uint32);
	void Open();
	void Close();
	void AnmOpen(float32*, float32*, float32, float32);
	void AnmClose(float32*, float32*, float32, float32);
	void SetCursor(sint32, sint32);
	void Queue(void*);
	void Dequeue(void*);
	void SetScissor(DAT128*);
	void ResetScissor(DAT128*);
//  void vEnableDepthBufferWritesForPolArea(bool);  // HVS addition
	
	CR_WINDOW& operator=(CR_WINDOW&);
};

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: cpp; -*- */
/* vim: set noet ts=4 sw=4 ft=cpp ff=dos fenc=euc-jp : */
