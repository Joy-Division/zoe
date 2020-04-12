#ifndef INCLUDED_CARL_H
#define INCLUDED_CARL_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"
#include "libdg.h"
#include "libgv.h"

/* (bgsphere.cc) */
void CR_SetStageLoad( char *, int, char **, int );
void CR_SetStageLoad( u_char, int, char **, int );

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class CR_EDGE : public GV_ACTOR //! check modifier
{
public: //! check modifier
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
	float           fWidth;

public:
	CR_EDGE(const CR_EDGE&);
	CR_EDGE(ALG_MATRIX*, ALG_VECTOR*);
	~CR_EDGE();

	void Invisible();
	void Visible();

	void Act(); // GV_ACTOR override

	CR_EDGE& operator=(CR_EDGE&);
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class CR_WINDOW
{
public: //! check modifier
	float           fXwindow;
	float           fYwindow;
	float           fWrange;
	float           fHrange;
	float           fXrange;
	float           fYrange;
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
	int             ctr;

	enum STATE {
		OPEN, CLOSE
	} st;

	CR_WINDOW* pPrev;
	CR_WINDOW* pNext;

// *** HVS addition ***
//	bool    m_bXPositionAdjustedinWS;
//	float   m_fXAmountAdjustedinWS;

	static class CR_WINDOW* pWinTop;

protected:
	void Unlink();
	void SetZ();
	void Validate();

public: //! check modifier
	static const float fWLine = TEMP_ZERO;
	static const float fHLine = TEMP_ZERO;
	static const float fHTitle = TEMP_ZERO;

public:
	CR_WINDOW();
	~CR_WINDOW();

	void Init(sint32, sint32, sint32, sint32);
	void SetOffset(sint32, sint32);
	void SetPosition(sint32, sint32);
	void SetPositionWideScreen(sint32, sint32, sint32, sint32);
	void SetArea(sint32, sint32);
	void SetFrameColor(float, float, float, float);
	void SetBgColor(float, float, float, float);
	void SetOrder(uint32);
	void Open();
	void Close();
	void AnmOpen(float*, float*, float, float);
	void AnmClose(float*, float*, float, float);
	void SetCursor(sint32, sint32);
	void Queue(void*);
	void Dequeue(void*);
	void SetScissor(DAT128*);
	void ResetScissor(DAT128*);

// *** HVS addition ***
//	void vEnableDepthBufferWritesForPolArea(bool);

	CR_WINDOW& operator=(CR_WINDOW&);
};

#endif /* END OF FILE */
