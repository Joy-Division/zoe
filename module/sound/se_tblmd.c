#include <sys/types.h>
#include "sd_incl.h"

/*===========================================================================*/
/* Sound Effect Data                                                         */
/*===========================================================================*/

#include "se_data/burner.h"
#include "se_data/megashot.h"
#include "se_data/laser.h"
#include "se_data/ken3.h"
#include "se_data/break.h"
#include "se_data/def.h"
#include "se_data/tate2.h"
#include "se_data/kenken.h"
#include "se_data/kenuk3.h"
#include "se_data/bak.h"
#include "se_data/kenbak.h"
#include "se_data/kettei.h"
#include "se_data/daibaku2.h"
#include "se_data/megasho2.h"
#include "se_data/keikoku2.h"
#include "se_data/sakusyu.h"
#include "se_data/system.h"
#include "se_data/iget.h"
#include "se_data/bag.h"
#include "se_data/nap.h"
#include "se_data/shot2.h"
#include "se_data/beam1.h"
#include "se_data/tyaku.h"
#include "se_data/glabak.h"
#include "se_data/tekibaku.h"
#include "se_data/balk.h"
#include "se_data/bagnage.h"
#include "se_data/bltyaku.h"
#include "se_data/canon.h"
#include "se_data/naguri2.h"
#include "se_data/napsya2.h"
#include "se_data/tame2.h"
#include "se_data/tukami.h"
#include "se_data/buildai.h"
#include "se_data/builchu.h"
#include "se_data/builgla.h"
#include "se_data/builsho.h"
#include "se_data/jaberin.h"
#include "se_data/geyser.h"
#include "se_data/rapc4.h"
#include "se_data/phalanx.h"
#include "se_data/halberd.h"
#include "se_data/chaklam.h"
#include "se_data/decoy.h"
#include "se_data/light.h"
#include "se_data/guntlet1.h"
#include "se_data/ryfle01.h"
#include "se_data/mamdef.h"
#include "se_data/itemhit1.h"
#include "se_data/itemget1.h"
#include "se_data/itembox1.h"
#include "se_data/progget1.h"
#include "se_data/winopn01.h"
#include "se_data/winclo01.h"
#include "se_data/sentak01.h"
#include "se_data/start01.h"
#include "se_data/cansel01.h"
#include "se_data/chowpn01.h"
#include "se_data/mamtate2.h"
#include "se_data/legscr01.h"
#include "se_data/legscr02.h"
#include "se_data/start02.h"
#include "se_data/recoch01.h"
#include "se_data/recoch02.h"
#include "se_data/builir01.h"
#include "se_data/noize04.h"
#include "se_data/noize05.h"
#include "se_data/halberd2.h"
#include "se_data/halscr01.h"
#include "se_data/start03.h"

// Unknown SE Data
#include "se_data/unknown.h"

/*===========================================================================*/
/* Dummy Sound Effect Data                                                   */
/*===========================================================================*/

u_char se_dummy[] = { 0x00,0x00,0xFE,0xFF };

/*===========================================================================*/
/* Sound Effect Table                                                        */
/*===========================================================================*/

struct SETBL se_tbl[128] = {
	/* pri,tracks,kind,character */
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,		se_dummy,		se_dummy	} },
	{ 0x20, 0x03, 0x01, 0x00, { burner00,		burner01,		burner02	} },
	{ 0x10, 0x02, 0x01, 0x00, { beam100,		beam101,		se_dummy	} },
	{ 0x40, 0x03, 0x01, 0x00, { megashot00,		megashot01,		megashot02	} },
	{ 0x10, 0x02, 0x01, 0x00, { laser00,		laser01,		se_dummy	} },
	{ 0x10, 0x03, 0x01, 0x00, { ken300,			ken301,			ken302		} },
	{ 0x40, 0x02, 0x01, 0x00, { break00,		break01,		se_dummy	} },
	{ 0x10, 0x02, 0x01, 0x00, { def00,			def01,			se_dummy	} },
	{ 0x20, 0x02, 0x01, 0x00, { tate200,		tate201,		se_dummy	} },
	{ 0x30, 0x02, 0x01, 0x00, { kenken00,		kenken01,		se_dummy	} },
	{ 0x30, 0x03, 0x01, 0x00, { kenuk300,		kenuk301,		kenuk302	} },
	{ 0x30, 0x02, 0x01, 0x00, { bak00,			bak01,			se_dummy	} },
	{ 0x50, 0x03, 0x01, 0x00, { tekibaku00,		tekibaku01,		tekibaku02	} },
	{ 0x50, 0x03, 0x01, 0x00, { kenbak00,		kenbak01,		kenbak02	} },
	{ 0x10, 0x03, 0x01, 0x00, { glabak00,		glabak01,		glabak02	} },
	{ 0x50, 0x02, 0x01, 0x00, { light00,		light01,		se_dummy	} },
	{ 0x40, 0x02, 0x00, 0x00, { kettei00,		kettei01,		se_dummy	} },
	{ 0x30, 0x02, 0x01, 0x00, { tyaku00,		tyaku01,		se_dummy	} },
	{ 0x50, 0x01, 0x01, 0x00, { daibaku200,		se_dummy,		se_dummy	} },
	{ 0x50, 0x02, 0x01, 0x00, { balk00,			balk01,			se_dummy	} },
	{ 0x10, 0x01, 0x01, 0x00, { keikoku200,		se_dummy,		se_dummy	} },
	{ 0x10, 0x02, 0x01, 0x00, { legscr0100,		legscr0101,		se_dummy	} },
	{ 0x10, 0x02, 0x01, 0x00, { legscr0200,		legscr0201,		se_dummy	} },
	{ 0x50, 0x01, 0x01, 0x00, { sakusyu00,		se_dummy,		se_dummy	} },
	{ 0x10, 0x01, 0x01, 0x00, { system00,		se_dummy,		se_dummy	} },
	{ 0x50, 0x02, 0x01, 0x00, { iget00,			iget01,			se_dummy	} },
	{ 0x10, 0x02, 0x01, 0x00, { bag00,			bag01,			se_dummy	} },
	{ 0x10, 0x01, 0x01, 0x00, { nap00,			se_dummy,		se_dummy	} },
	{ 0x10, 0x02, 0x01, 0x00, { shot200,		shot201,		se_dummy	} },
	{ 0x10, 0x03, 0x01, 0x00, { megasho200,		megasho201,		megasho202	} },
	{ 0x10, 0x02, 0x01, 0x00, { bagnage00,		bagnage01,		se_dummy	} },
	{ 0x10, 0x02, 0x01, 0x00, { bltyaku00,		bltyaku01,		se_dummy	} },
	{ 0x40, 0x03, 0x01, 0x01, { canon00,		canon01,		canon02		} },
	{ 0x30, 0x03, 0x01, 0x00, { naguri200,		naguri201,		naguri202	} },
	{ 0x10, 0x02, 0x01, 0x00, { napsya200,		napsya201,		se_dummy	} },
	{ 0x30, 0x03, 0x01, 0x01, { tame200,		tame201,		tame202		} },
	{ 0x30, 0x02, 0x01, 0x00, { tukami00,		tukami01,		se_dummy	} },
	{ 0x50, 0x03, 0x01, 0x00, { buildai00,		buildai01,		buildai02	} },
	{ 0x20, 0x02, 0x01, 0x00, { builchu00,		builchu01,		se_dummy	} },
	{ 0x20, 0x03, 0x01, 0x00, { builgla00,		builgla01,		builgla02	} },
	{ 0x10, 0x02, 0x01, 0x00, { builsho00,		builsho01,		se_dummy	} },
	{ 0x20, 0x02, 0x01, 0x00, { jaberin00,		jaberin01,		se_dummy	} },
	{ 0x20, 0x02, 0x01, 0x00, { geyser00,		geyser01,		se_dummy	} },
	{ 0x20, 0x02, 0x01, 0x00, { rapc400,		rapc401,		se_dummy	} },
	{ 0x20, 0x03, 0x01, 0x00, { phalanx00,		phalanx01,		phalanx02	} },
	{ 0x20, 0x03, 0x01, 0x00, { halberd00,		halberd01,		halberd02	} },
	{ 0x20, 0x02, 0x01, 0x00, { chaklam00,		chaklam01,		se_dummy	} },
	{ 0x20, 0x02, 0x01, 0x00, { decoy00,		decoy01,		se_dummy	} },
	{ 0x20, 0x02, 0x01, 0x00, { guntlet100,		guntlet101,		se_dummy	} },
	{ 0x20, 0x02, 0x01, 0x00, { ryfle0100,		ryfle0101,		se_dummy	} },
	{ 0x10, 0x02, 0x01, 0x00, { mamdef00,		mamdef01,		se_dummy	} },
	{ 0x20, 0x02, 0x01, 0x00, { itemhit100,		itemhit101,		se_dummy	} },
	{ 0x30, 0x02, 0x01, 0x00, { itemget100,		itemget101,		se_dummy	} },
	{ 0x50, 0x02, 0x01, 0x00, { itembox100,		itembox101,		se_dummy	} },
	{ 0x10, 0x03, 0x01, 0x00, { progget100,		progget101,		progget102	} },
	{ 0x10, 0x01, 0x00, 0x00, { winopn0100,		se_dummy,		se_dummy	} },
	{ 0x10, 0x01, 0x00, 0x00, { winclo0100,		se_dummy,		se_dummy	} },
	{ 0x10, 0x01, 0x00, 0x00, { sentak0100,		se_dummy,		se_dummy	} },
	{ 0x10, 0x02, 0x00, 0x00, { start0100,		start0101,		se_dummy	} },
	{ 0x10, 0x02, 0x00, 0x00, { cansel0100,		cansel0101,		se_dummy	} },
	{ 0x10, 0x02, 0x00, 0x00, { chowpn0100,		chowpn0101,		se_dummy	} },
	{ 0x20, 0x02, 0x01, 0x00, { mamtate200,		mamtate201,		se_dummy	} },
	{ 0x50, 0x03, 0x00, 0x00, { start0200,		start0201,		start0202	} },
	{ 0x00, 0x01, 0x00, 0x00, { se_dummy,		se_dummy,		se_dummy	} },
	{ 0x20, 0x01, 0x01, 0x00, { recoch0100,		se_dummy,		se_dummy	} },
	{ 0x20, 0x01, 0x01, 0x00, { recoch0200,		se_dummy,		se_dummy	} },
	{ 0x80, 0x02, 0x00, 0x00, { noize0400,		noize0401,		se_dummy	} },
	{ 0x40, 0x03, 0x01, 0x00, { builir0100,		builir0101,		builir0102	} },
	{ 0x80, 0x03, 0x00, 0x00, { noize0500,		noize0501,		noize0502	} },
	{ 0x30, 0x02, 0x01, 0x00, { halberd200,		halberd201,		se_dummy	} },
	{ 0x30, 0x02, 0x01, 0x00, { halscr0100,		halscr0101,		se_dummy	} },
	{ 0x10, 0x02, 0x00, 0x00, { start0300,		start0301,		se_dummy	} },

	/* --- UNKNOWN SE DATA --- */
	{ 0x10, 0x02, 0x00, 0x00, { unk_0001BC14,	unk_0001BC54,	se_dummy		} },
	{ 0x80, 0x03, 0x00, 0x00, { unk_0001BC84,	unk_0001BD50,	unk_0001BE10	} },
	{ 0x10, 0x01, 0x00, 0x00, { unk_0001BE68,	se_dummy,		se_dummy		} },
	{ 0x10, 0x03, 0x00, 0x00, { unk_0001BEA8,	unk_0001BEF4,	unk_0001BF48	} },
	{ 0x30, 0x03, 0x01, 0x00, { unk_0001BF98,	unk_0001BFC8,	unk_0001BFF8	} },
	{ 0x30, 0x02, 0x01, 0x00, { unk_0001C028,	unk_0001C050,	se_dummy		} },
	{ 0x40, 0x02, 0x00, 0x00, { unk_0001C078,	unk_0001C0A4,	se_dummy		} },
	{ 0x30, 0x01, 0x00, 0x00, { unk_0001C0D4,	se_dummy,		se_dummy		} },
	{ 0x40, 0x02, 0x00, 0x00, { unk_0001C0FC,	unk_0001C130,	se_dummy		} },
	{ 0x40, 0x01, 0x00, 0x00, { unk_0001C164,	se_dummy,		se_dummy		} },
	{ 0x50, 0x01, 0x00, 0x00, { unk_0001C190,	se_dummy,		se_dummy		} },
	{ 0x10, 0x02, 0x01, 0x00, { unk_0001C1C8,	unk_0001C1EC,	se_dummy		} },
	{ 0x10, 0x02, 0x01, 0x00, { unk_0001C210,	unk_0001C234,	se_dummy		} },
	{ 0x40, 0x02, 0x00, 0x00, { unk_0001C258,	unk_0001C294,	se_dummy		} },
	{ 0x30, 0x01, 0x00, 0x00, { unk_0001C2C4,	se_dummy,		se_dummy		} },
	{ 0x40, 0x02, 0x00, 0x00, { unk_0001C320,	unk_0001C360,	se_dummy		} },
	{ 0x50, 0x02, 0x00, 0x00, { unk_0001C3A4,	unk_0001C3EC,	se_dummy		} },
	{ 0x30, 0x02, 0x01, 0x00, { unk_0001C424,	unk_0001C454,	se_dummy		} },
	{ 0x30, 0x02, 0x01, 0x00, { unk_0001C484,	unk_0001C4B8,	se_dummy		} },
	{ 0x30, 0x02, 0x00, 0x00, { unk_0001C4EC,	unk_0001C518,	se_dummy		} },
	{ 0x10, 0x02, 0x01, 0x00, { unk_0001C544,	unk_0001C56C,	se_dummy		} },
	{ 0x50, 0x03, 0x00, 0x00, { unk_0001C594,	unk_0001C5E8,	unk_0001C640	} },
	{ 0x50, 0x02, 0x00, 0x00, { unk_0001C6B4,	unk_0001C720,	se_dummy		} },
	{ 0x10, 0x01, 0x01, 0x00, { unk_0001C754,	se_dummy,		se_dummy		} },
	{ 0x10, 0x01, 0x01, 0x00, { unk_0001C7AC,	se_dummy,		se_dummy		} },
	{ 0x30, 0x01, 0x00, 0x00, { unk_0001C7DC,	se_dummy,		se_dummy		} },
	{ 0x50, 0x03, 0x01, 0x00, { unk_0001C808,	unk_0001C83C,	unk_0001C880	} },
	{ 0x50, 0x03, 0x01, 0x00, { unk_0001C8CC,	unk_0001C900,	unk_0001C958	} },
	{ 0x50, 0x03, 0x00, 0x00, { unk_0001C990,	unk_0001C9C0,	unk_0001CA1C	} },
	{ 0x50, 0x03, 0x00, 0x00, { unk_0001CA80,	unk_0001CADC,	unk_0001CB50	} },
	{ 0x30, 0x01, 0x00, 0x00, { unk_0001CBC8,	se_dummy,		se_dummy		} },
	{ 0x30, 0x01, 0x01, 0x00, { unk_0001CC14,	se_dummy,		se_dummy		} },
	{ 0x30, 0x01, 0x01, 0x00, { unk_0001CC78,	se_dummy,		se_dummy		} },
	{ 0x50, 0x02, 0x01, 0x00, { unk_0001CCCC,	unk_0001CD00,	se_dummy		} },
	{ 0x20, 0x02, 0x01, 0x00, { unk_0001CD50,	unk_0001CDB0,	se_dummy		} },
	{ 0x20, 0x03, 0x01, 0x00, { unk_0001CE00,	unk_0001CE40,	unk_0001CE80	} },
	{ 0xA0, 0x03, 0x00, 0x00, { unk_0001CEAC,	unk_0001CF14,	unk_0001CF7C	} },
	{ 0x30, 0x03, 0x00, 0x00, { unk_0001CFD8,	unk_0001D000,	unk_0001D02C	} },
	{ 0xFF, 0x02, 0x01, 0x00, { unk_0001D050,	unk_0001D090,	se_dummy		} },
	{ 0xFF, 0x03, 0x01, 0x00, { unk_0001D0D4,	unk_0001D114,	unk_0001D158	} },
	{ 0x50, 0x01, 0x00, 0x00, { unk_0001D198,	se_dummy,		se_dummy		} },
	{ 0x30, 0x02, 0x00, 0x00, { unk_0001D1D4,	unk_0001D208,	se_dummy		} },
	{ 0x20, 0x01, 0x00, 0x00, { unk_0001D240,	se_dummy,		se_dummy		} },
	{ 0x20, 0x03, 0x00, 0x00, { unk_0001D284,	unk_0001D2B0,	unk_0001D2DC	} },
	{ 0x50, 0x02, 0x01, 0x00, { unk_0001D308,	unk_0001D35C,	se_dummy		} },
	{ 0x50, 0x03, 0x01, 0x00, { unk_0001D588,	unk_0001D5EC,	unk_0001D618	} },
	{ 0x50, 0x03, 0x01, 0x00, { unk_0001D644,	unk_0001D67C,	unk_0001D6AC	} },
	{ 0x50, 0x03, 0x01, 0x00, { unk_0001D490,	unk_0001D4B8,	unk_0001D4E0	} },
	{ 0x50, 0x03, 0x01, 0x00, { unk_0001D3AC,	unk_0001D408,	unk_0001D438	} },
	{ 0x50, 0x02, 0x01, 0x00, { unk_0001D508,	unk_0001D554,	se_dummy		} },
	{ 0x50, 0x02, 0x00, 0x00, { unk_0001D6DC,	unk_0001D770,	se_dummy		} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,		se_dummy,		se_dummy		} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,		se_dummy,		se_dummy		} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,		se_dummy,		se_dummy		} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,		se_dummy,		se_dummy		} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,		se_dummy,		se_dummy		} }
};
