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

#if !defined(BORMAN_DEMO)
#include "se_data/nonm072.h"
#if !defined(DENGEKI_DEMO)
#include "se_data/nonm073.h"
#include "se_data/nonm074.h"
#include "se_data/nonm075.h"
#include "se_data/nonm076.h"
#include "se_data/nonm077.h"
#include "se_data/nonm078.h"
#include "se_data/nonm079.h"
#include "se_data/nonm080.h"
#include "se_data/nonm081.h"
#include "se_data/nonm082.h"
#include "se_data/nonm083.h"
#include "se_data/nonm084.h"
#include "se_data/nonm085.h"
#include "se_data/nonm086.h"
#include "se_data/nonm087.h"
#include "se_data/nonm088.h"
#include "se_data/nonm089.h"
#include "se_data/nonm090.h"
#include "se_data/nonm091.h"
#include "se_data/nonm092.h"
#include "se_data/nonm093.h"
#include "se_data/nonm094.h"
#include "se_data/nonm095.h"
#include "se_data/nonm096.h"
#include "se_data/nonm097.h"
#include "se_data/nonm098.h"
#include "se_data/nonm099.h"
#include "se_data/nonm100.h"
#include "se_data/nonm101.h"
#include "se_data/nonm102.h"
#include "se_data/nonm103.h"
#include "se_data/nonm104.h"
#include "se_data/nonm105.h"
#include "se_data/nonm106.h"
#include "se_data/nonm107.h"
#include "se_data/nonm108.h"
#include "se_data/nonm109.h"
#include "se_data/nonm110.h"
#include "se_data/nonm111.h"
#include "se_data/nonm112.h"
#include "se_data/nonm113.h"
#include "se_data/nonm114.h"
#include "se_data/nonm115.h"
#include "se_data/nonm116.h"
#include "se_data/nonm120.h"
#include "se_data/nonm119.h"
#include "se_data/nonm121.h"
#include "se_data/nonm117.h"
#include "se_data/nonm118.h"
#include "se_data/nonm122.h"
#endif // !DENGEKI_DEMO
#endif // !BORMAN_DEMO

/*===========================================================================*/
/* Dummy Sound Effect Data                                                   */
/*===========================================================================*/

u_char se_dummy[] = { 0x00,0x00,0xFE,0xFF };

/*===========================================================================*/
/* Sound Effect Table                                                        */
/*===========================================================================*/

struct SETBL se_tbl[128] = {
	/* pri,tracks,kind,character */
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },//0
#if defined(BORMAN_DEMO) || defined(DENGEKI_DEMO)
	{ 0x10, 0x01, 0x01, 0x00, { burner00,	se_dummy,	se_dummy	} },
#else
	{ 0x20, 0x03, 0x01, 0x00, { burner00,	burner01,	burner02	} },
#endif
	{ 0x10, 0x02, 0x01, 0x00, { beam100,	beam101,	se_dummy	} },
	{ 0x40, 0x03, 0x01, 0x00, { megashot00,	megashot01,	megashot02	} },
	{ 0x10, 0x02, 0x01, 0x00, { laser00,	laser01,	se_dummy	} },
	{ 0x10, 0x03, 0x01, 0x00, { ken300,		ken301,		ken302		} },
	{ 0x40, 0x02, 0x01, 0x00, { break00,	break01,	se_dummy	} },
	{ 0x10, 0x02, 0x01, 0x00, { def00,		def01,		se_dummy	} },
	{ 0x20, 0x02, 0x01, 0x00, { tate200,	tate201,	se_dummy	} },
	{ 0x30, 0x02, 0x01, 0x00, { kenken00,	kenken01,	se_dummy	} },
	{ 0x30, 0x03, 0x01, 0x00, { kenuk300,	kenuk301,	kenuk302	} },//10
	{ 0x30, 0x02, 0x01, 0x00, { bak00,		bak01,		se_dummy	} },
	{ 0x50, 0x03, 0x01, 0x00, { tekibaku00,	tekibaku01,	tekibaku02	} },
	{ 0x50, 0x03, 0x01, 0x00, { kenbak00,	kenbak01,	kenbak02	} },
	{ 0x10, 0x03, 0x01, 0x00, { glabak00,	glabak01,	glabak02	} },
	{ 0x50, 0x02, 0x01, 0x00, { light00,	light01,	se_dummy	} },
	{ 0x40, 0x02, 0x00, 0x00, { kettei00,	kettei01,	se_dummy	} },
	{ 0x30, 0x02, 0x01, 0x00, { tyaku00,	tyaku01,	se_dummy	} },
	{ 0x50, 0x01, 0x01, 0x00, { daibaku200,	se_dummy,	se_dummy	} },
	{ 0x50, 0x02, 0x01, 0x00, { balk00,		balk01,		se_dummy	} },
	{ 0x10, 0x01, 0x01, 0x00, { keikoku200,	se_dummy,	se_dummy	} },//20
	{ 0x10, 0x02, 0x01, 0x00, { legscr0100,	legscr0101,	se_dummy	} },
	{ 0x10, 0x02, 0x01, 0x00, { legscr0200,	legscr0201,	se_dummy	} },
	{ 0x50, 0x01, 0x01, 0x00, { sakusyu00,	se_dummy,	se_dummy	} },
	{ 0x10, 0x01, 0x01, 0x00, { system00,	se_dummy,	se_dummy	} },
	{ 0x50, 0x02, 0x01, 0x00, { iget00,		iget01,		se_dummy	} },
	{ 0x10, 0x02, 0x01, 0x00, { bag00,		bag01,		se_dummy	} },
	{ 0x10, 0x01, 0x01, 0x00, { nap00,		se_dummy,	se_dummy	} },
	{ 0x10, 0x02, 0x01, 0x00, { shot200,	shot201,	se_dummy	} },
	{ 0x10, 0x03, 0x01, 0x00, { megasho200,	megasho201,	megasho202	} },
	{ 0x10, 0x02, 0x01, 0x00, { bagnage00,	bagnage01,	se_dummy	} },//30
	{ 0x10, 0x02, 0x01, 0x00, { bltyaku00,	bltyaku01,	se_dummy	} },
	{ 0x40, 0x03, 0x01, 0x01, { canon00,	canon01,	canon02		} },
	{ 0x30, 0x03, 0x01, 0x00, { naguri200,	naguri201,	naguri202	} },
	{ 0x10, 0x02, 0x01, 0x00, { napsya200,	napsya201,	se_dummy	} },
	{ 0x30, 0x03, 0x01, 0x01, { tame200,	tame201,	tame202		} },
	{ 0x30, 0x02, 0x01, 0x00, { tukami00,	tukami01,	se_dummy	} },
	{ 0x50, 0x03, 0x01, 0x00, { buildai00,	buildai01,	buildai02	} },
	{ 0x20, 0x02, 0x01, 0x00, { builchu00,	builchu01,	se_dummy	} },
#if defined(BORMAN_DEMO) || defined(DENGEKI_DEMO)
	{ 0x20, 0x02, 0x01, 0x00, { builgla00,	builgla01,	se_dummy	} },
#else
	{ 0x20, 0x03, 0x01, 0x00, { builgla00,	builgla01,	builgla02	} },
#endif
	{ 0x10, 0x02, 0x01, 0x00, { builsho00,	builsho01,	se_dummy	} },//40
	{ 0x20, 0x02, 0x01, 0x00, { jaberin00,	jaberin01,	se_dummy	} },
	{ 0x20, 0x02, 0x01, 0x00, { geyser00,	geyser01,	se_dummy	} },
	{ 0x20, 0x02, 0x01, 0x00, { rapc400,	rapc401,	se_dummy	} },
	{ 0x20, 0x03, 0x01, 0x00, { phalanx00,	phalanx01,	phalanx02	} },
	{ 0x20, 0x03, 0x01, 0x00, { halberd00,	halberd01,	halberd02	} },
	{ 0x20, 0x02, 0x01, 0x00, { chaklam00,	chaklam01,	se_dummy	} },
	{ 0x20, 0x02, 0x01, 0x00, { decoy00,	decoy01,	se_dummy	} },
	{ 0x20, 0x02, 0x01, 0x00, { guntlet100,	guntlet101,	se_dummy	} },
	{ 0x20, 0x02, 0x01, 0x00, { ryfle0100,	ryfle0101,	se_dummy	} },
	{ 0x10, 0x02, 0x01, 0x00, { mamdef00,	mamdef01,	se_dummy	} },//50
	{ 0x20, 0x02, 0x01, 0x00, { itemhit100,	itemhit101,	se_dummy	} },
	{ 0x30, 0x02, 0x01, 0x00, { itemget100,	itemget101,	se_dummy	} },
	{ 0x50, 0x02, 0x01, 0x00, { itembox100,	itembox101,	se_dummy	} },
	{ 0x10, 0x03, 0x01, 0x00, { progget100,	progget101,	progget102	} },
	{ 0x10, 0x01, 0x00, 0x00, { winopn0100,	se_dummy,	se_dummy	} },
	{ 0x10, 0x01, 0x00, 0x00, { winclo0100,	se_dummy,	se_dummy	} },
	{ 0x10, 0x01, 0x00, 0x00, { sentak0100,	se_dummy,	se_dummy	} },
	{ 0x10, 0x02, 0x00, 0x00, { start0100,	start0101,	se_dummy	} },
#if defined(BORMAN_DEMO) || defined(DENGEKI_DEMO)
	{ 0x10, 0x01, 0x00, 0x00, { cansel0100,	se_dummy,	se_dummy	} },
#else
	{ 0x10, 0x02, 0x00, 0x00, { cansel0100,	cansel0101,	se_dummy	} },
#endif
	{ 0x10, 0x02, 0x00, 0x00, { chowpn0100,	chowpn0101,	se_dummy	} },//60
	{ 0x20, 0x02, 0x01, 0x00, { mamtate200,	mamtate201,	se_dummy	} },
	{ 0x50, 0x03, 0x00, 0x00, { start0200,	start0201,	start0202	} },
	{ 0x00, 0x01, 0x00, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x20, 0x01, 0x01, 0x00, { recoch0100,	se_dummy,	se_dummy	} },
	{ 0x20, 0x01, 0x01, 0x00, { recoch0200,	se_dummy,	se_dummy	} },
	{ 0x80, 0x02, 0x00, 0x00, { noize0400,	noize0401,	se_dummy	} },
	{ 0x40, 0x03, 0x01, 0x00, { builir0100,	builir0101,	builir0102	} },
	{ 0x80, 0x03, 0x00, 0x00, { noize0500,	noize0501,	noize0502	} },
	{ 0x30, 0x02, 0x01, 0x00, { halberd200,	halberd201,	se_dummy	} },
	{ 0x30, 0x02, 0x01, 0x00, { halscr0100,	halscr0101,	se_dummy	} },//70
	{ 0x10, 0x02, 0x00, 0x00, { start0300,	start0301,	se_dummy	} },//71

	/* --- Additional SE Data --- */

#if defined(BORMAN_DEMO) || defined(DENGEKI_DEMO)
#if defined(BORMAN_DEMO)
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
#else
	{ 0x10, 0x02, 0x00, 0x00, { nonm07200,	nonm07201,	se_dummy	} },//72
#endif
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} }
#else
	{ 0x10, 0x02, 0x00, 0x00, { nonm07200,	nonm07201,	se_dummy	} },//72
	{ 0x80, 0x03, 0x00, 0x00, { nonm07300,	nonm07301,	nonm07302	} },
	{ 0x10, 0x01, 0x00, 0x00, { nonm07400,	se_dummy,	se_dummy	} },
	{ 0x10, 0x03, 0x00, 0x00, { nonm07500,	nonm07501,	nonm07502	} },
	{ 0x30, 0x03, 0x01, 0x00, { nonm07600,	nonm07601,	nonm07602	} },
	{ 0x30, 0x02, 0x01, 0x00, { nonm07700,	nonm07701,	se_dummy	} },
	{ 0x40, 0x02, 0x00, 0x00, { nonm07800,	nonm07801,	se_dummy	} },
	{ 0x30, 0x01, 0x00, 0x00, { nonm07900,	se_dummy,	se_dummy	} },
	{ 0x40, 0x02, 0x00, 0x00, { nonm08000,	nonm08001,	se_dummy	} },//80
	{ 0x40, 0x01, 0x00, 0x00, { nonm08100,	se_dummy,	se_dummy	} },
	{ 0x50, 0x01, 0x00, 0x00, { nonm08200,	se_dummy,	se_dummy	} },
	{ 0x10, 0x02, 0x01, 0x00, { nonm08300,	nonm08301,	se_dummy	} },
	{ 0x10, 0x02, 0x01, 0x00, { nonm08400,	nonm08401,	se_dummy	} },
	{ 0x40, 0x02, 0x00, 0x00, { nonm08500,	nonm08501,	se_dummy	} },
	{ 0x30, 0x01, 0x00, 0x00, { nonm08600,	se_dummy,	se_dummy	} },
	{ 0x40, 0x02, 0x00, 0x00, { nonm08700,	nonm08701,	se_dummy	} },
	{ 0x50, 0x02, 0x00, 0x00, { nonm08800,	nonm08801,	se_dummy	} },
	{ 0x30, 0x02, 0x01, 0x00, { nonm08900,	nonm08901,	se_dummy	} },
	{ 0x30, 0x02, 0x01, 0x00, { nonm09000,	nonm09001,	se_dummy	} },//90
	{ 0x30, 0x02, 0x00, 0x00, { nonm09100,	nonm09101,	se_dummy	} },
	{ 0x10, 0x02, 0x01, 0x00, { nonm09200,	nonm09201,	se_dummy	} },
	{ 0x50, 0x03, 0x00, 0x00, { nonm09300,	nonm09301,	nonm09302	} },
	{ 0x50, 0x02, 0x00, 0x00, { nonm09400,	nonm09401,	se_dummy	} },
	{ 0x10, 0x01, 0x01, 0x00, { nonm09500,	se_dummy,	se_dummy	} },
	{ 0x10, 0x01, 0x01, 0x00, { nonm09600,	se_dummy,	se_dummy	} },
	{ 0x30, 0x01, 0x00, 0x00, { nonm09700,	se_dummy,	se_dummy	} },
	{ 0x50, 0x03, 0x01, 0x00, { nonm09800,	nonm09801,	nonm09802	} },
	{ 0x50, 0x03, 0x01, 0x00, { nonm09900,	nonm09901,	nonm09902	} },
	{ 0x50, 0x03, 0x00, 0x00, { nonm10000,	nonm10001,	nonm10002	} },//100
	{ 0x50, 0x03, 0x00, 0x00, { nonm10100,	nonm10101,	nonm10102	} },
	{ 0x30, 0x01, 0x00, 0x00, { nonm10200,	se_dummy,	se_dummy	} },
	{ 0x30, 0x01, 0x01, 0x00, { nonm10300,	se_dummy,	se_dummy	} },
	{ 0x30, 0x01, 0x01, 0x00, { nonm10400,	se_dummy,	se_dummy	} },
	{ 0x50, 0x02, 0x01, 0x00, { nonm10500,	nonm10501,	se_dummy	} },
	{ 0x20, 0x02, 0x01, 0x00, { nonm10600,	nonm10601,	se_dummy	} },
	{ 0x20, 0x03, 0x01, 0x00, { nonm10700,	nonm10701,	nonm10702	} },
	{ 0xA0, 0x03, 0x00, 0x00, { nonm10800,	nonm10801,	nonm10802	} },
	{ 0x30, 0x03, 0x00, 0x00, { nonm10900,	nonm10901,	nonm10902	} },
	{ 0xFF, 0x02, 0x01, 0x00, { nonm11000,	nonm11001,	se_dummy	} },//110
	{ 0xFF, 0x03, 0x01, 0x00, { nonm11100,	nonm11101,	nonm11102	} },
	{ 0x50, 0x01, 0x00, 0x00, { nonm11200,	se_dummy,	se_dummy	} },
	{ 0x30, 0x02, 0x00, 0x00, { nonm11300,	nonm11301,	se_dummy	} },
	{ 0x20, 0x01, 0x00, 0x00, { nonm11400,	se_dummy,	se_dummy	} },
	{ 0x20, 0x03, 0x00, 0x00, { nonm11500,	nonm11501,	nonm11502	} },
	{ 0x50, 0x02, 0x01, 0x00, { nonm11600,	nonm11601,	se_dummy	} },		// jaberin
	{ 0x50, 0x03, 0x01, 0x00, { nonm11700,	nonm11701,	nonm11702	} },
	{ 0x50, 0x03, 0x01, 0x00, { nonm11800,	nonm11801,	nonm11802	} },
	{ 0x50, 0x03, 0x01, 0x00, { nonm11900,	nonm11901,	nonm11902	} },		// tame2
	{ 0x50, 0x03, 0x01, 0x00, { nonm12000,	nonm12001,	nonm12002	} },//120	// canon
	{ 0x50, 0x02, 0x01, 0x00, { nonm12100,	nonm12101,	se_dummy	} },
	{ 0x50, 0x02, 0x00, 0x00, { nonm12200,	nonm12201,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} },
	{ 0x01, 0x01, 0x01, 0x00, { se_dummy,	se_dummy,	se_dummy	} }//127
#endif // BORMAN_DEMO || DENGEKI_DEMO
};
