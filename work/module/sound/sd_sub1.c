/*
 * Sound Driver for PS2 IOP
 * Sub-Module 1
 *
 * ver.ZONE OF THE ENDERS
 */
#include <sys/types.h>
#include "sd_incl.h"
#include "sd_ext.h"

// NOMATCH: access to mem_str_w produces subtraction at the wrong point in time
int sound_sub( void )
{
	sptr->tmpd += sptr->tmp;
	
	if( sptr->tmpd >= 256 && sptr->unkD4 ){
		sptr->unkD9--;
		if( !sptr->unkD9 ){
			sptr->unkD9 = sptr->unkD4;
			if( sptr->unkD8 == 0xFF ){
				if( fx_sound_code ){
					sptr->unkE0 = 1;
					mptr = sptr->unkDC;
					sptr->ngc = 1;
					fx_sound_code++;
				}
			} else {
				if( sound_w[(sptr->unkD8 & 0x1F) & 0xFF].unkE1 ){
					sptr->unkE0 = 1;
					mptr = sptr->unkDC;
					sptr->ngc = 1;
					sound_w[(sptr->unkD8 & 0x1F) & 0xFF].unkE1 = 0;
				}
			}
		}
	}
	
	if( sptr->unkD4 && !sptr->unkE0 ){
		sptr->tmpd &= 0xFF;
	} else {
		key_fg = 0;
		if( sptr->tmpd >= 256 ){
			sptr->tmpd &= 0xFF;
			sptr->ngc--;
			if( !sptr->ngc ){
				if( tx_read() ){
					keyoff();
					return 1;
				}
			} else {
				keych();
			}
			tempo_ch();
			bendch();
			vol_compute();
			fader_automation1();
		} else {
			note_cntl();
		}
		fader_automation2();
		if( key_fg ){
			if( sptr->snos < 256 ){
				keyon();
			} else {
				mem_str_w[mtrack-32].unk00 = 2;
			}
		}
	}
	return 0;
}

// NOMATCH: this may not be functionally equivalent, check assignment of mdata1
int tx_read( void )
{
	int i, temp2 = 0;
	
	for( i = 1 ; i ; i = 0 ){
		temp2++;
		mdata1 = mptr[((temp2 == 256) ? 256 : 1) + 3];
		if( !mdata1 ) return 1;
		mdata2 = mptr[2];
		mdata3 = mptr[1];
		mdata4 = mptr[0];
		mptr+=4;
		if( mdata1 >= 128 ){
			cntl_tbl[mdata1-128]();
			if( mdata1 == 0xF2 || mdata1 == 0xF3 || mdata1 == 0xFF ){
				temp2 = 0;
			}
			if( mdata1 == 0xFF ) return 1;
			if( mdata1 == 0xDA || mdata1 == 0xDB ){
				temp2 = 0;
			}
		} else {
			if( sptr->ngg < 0x64 && mdata4 ){
				key_fg = 1;
			}
			sptr->rest_fg = 0;
			note_set();
			temp2 = 0;
		}
	}
	return 0;
}

void note_set( void )
{
	u_int temp;
	
	sptr->ngs = mdata2;
	sptr->ngg = mdata3;
	sptr->vol = (mdata4 & 0x7F);
	note_compute();
	sptr->ngc = sptr->ngs;
	temp = (sptr->ngg * sptr->ngc)/100;
	
	if( !temp ){
		temp = 1;
	}
	sptr->ngo = temp;
}

void adsr_reset( void )
{
	spu_tr_wk[mtrack].rr = sptr->rrd;
	spu_tr_wk[mtrack].env3_fg = 1;
}

void note_compute( void )
{
	int temp, temp2;
	
	if( mdata1 >= 0x48 ){
		drum_set( mdata1 );
		temp = 0x24;
	} else {
		temp = mdata1;
	}
	
	temp += sptr->ptps;
	temp = (temp << 8) + sptr->tund;
	temp = temp + sptr->lp1_freq + sptr->lp2_freq;
	
	while( temp >= 0x6000 ){
		temp -= 0x6000;
	}
	
	temp2 = sptr->swpd;
	sptr->swpd = temp;
	sptr->vibhc = sptr->vibcc = 0;
	sptr->vib_tmp_cnt = sptr->vib_tbl_cnt = 0;
	sptr->vibd = 0;
	sptr->trec = sptr->trehc = 0;
	adsr_reset();
	sptr->swpc = sptr->swsc;
	
	if( sptr->swpc ){
		sptr->swphc = sptr->swshc;
		if( !sptr->swsk ){
			temp = sptr->swpd;
			if( sptr->swss > 0x7F00 ){
				sptr->swpd += 1 - (sptr->swss & 0xFFFF);
			} else {
				sptr->swpd -= sptr->swss;
			}
			swpadset( temp );
		} else {
			sptr->swpm = sptr->swpd;
			sptr->swpd = temp2;
		}
	}
	temp = sptr->swpd;
	freq_set( temp );
}

void swpadset( int a0 )
{
	register u_int temp;
	
	if( sptr->swpc ){
		temp = (sptr->swpc << 8) / sptr->tmp;

		if( a0 < 0 ){
			a0 = 0;
		} else if( a0 >= 0x6000 ){
			a0 = 0x5FFF;
		}
		
	    sptr->swpm = a0;
	    a0 -= sptr->swpd;
		
		if( a0 < 0 ){
			a0 = -a0 / temp;
			sptr->swpad = -a0;
		} else {
			sptr->swpad = a0 / temp;
		}
	}
}

void vol_compute( void )
{
	u_int temp;
	
	if( sptr->pvoc ){
		if( !(--sptr->pvoc & 0xFF) ){
			sptr->pvod = sptr->pvom << 8;
		} else {
			sptr->pvod += sptr->pvoad;
		}
	}
	if( sptr->vol ){
		if( sptr->tred ){
			if( sptr->trehs == sptr->trehc ){
				sptr->trec += sptr->trecad;
				if( sptr->trec < 0 ){
					temp = sptr->tred * -sptr->trec;
				} else if( sptr->trec == 0 ){
					temp = 1;
				} else {
					temp = sptr->tred * sptr->trec;
				}
			} else {
				sptr->trehc++;
				temp = 0;
			}
		} else {
			temp = 0;
		}
		volxset( (temp >> 8) & 0xFF );
	}
	pan_generate();
}

void pan_generate( void )
{
	if( sptr->panc ){
		if( !((char)--sptr->panc) ){
			sptr->pand = sptr->panm;
		} else {
			sptr->pand += sptr->panad;
		}
		sptr->panf = sptr->pand >> 8;
	}
}

void key_cut_off( void )
{
	if( sptr->rrd >= 8 ){
		spu_tr_wk[mtrack].rr = 7;
		spu_tr_wk[mtrack].env3_fg = 1;
	}
}

void keych( void )
{
	u_int temp, temp2, temp3;
	
	if( sptr->ngg < 0x64 && (sptr->ngc == 1) ){
		key_cut_off();
	}
	
	if( sptr->ngo ){
		sptr->ngo--;
		if( !sptr->ngo ){
			keyoff();
		}
	}
	
	temp3 = 0;
	
	if( sptr->swpc ){
		if( sptr->swphc ){
			sptr->swphc--;
		} else if( !sptr->swsk ){
			if( !(--sptr->swpc) ){
				sptr->swpd = sptr->swpm;
			} else {
				sptr->swpd += sptr->swpad;
			}
		} else {
			por_compute();
		}
		temp3 = 1;
	}
	
	temp = 0;
	
	if( sptr->vibdm ){
		if( sptr->vibhc == sptr->vibhs ){
			sptr->vibhc++;
		} else {
			if( sptr->vibcc == sptr->vibcs ){
				sptr->vibd = sptr->vibdm;
			} else {
				if( sptr->vibcc ){
					sptr->vibd += sptr->vibad;
				} else {
					sptr->vibd = sptr->vibad;
				}
				sptr->vibcc++;
			}
			sptr->vib_tmp_cnt += sptr->vibcad;
			if( sptr->vib_tmp_cnt >= 256 ){
				sptr->vib_tmp_cnt &= 0xFF;
				temp = vib_compute();
				temp3 = 1;
			}
		}
	}
	
	temp2 = random();
	
	if( temp2 ){
		temp += temp2;
		temp3 = 1;
	}
	if( temp3 ){
		freq_set( sptr->swpd + temp );
	}
}

void por_compute( void )
{
	int temp;
	u_int temp2, temp3;
	
	temp = sptr->swpm - sptr->swpd;
	
	if( temp < 0 ){
		temp = -temp;
		temp3 = temp & 0xFF;
		temp2 = temp >> 8;
		temp3 = (sptr->swsc * temp3) >> 8;
		temp2 *= sptr->swsc;
		temp = temp2 + temp3;
		if( temp == 0 ){
			temp = 1;
		}
		temp = -temp;
	} else if( temp == 0 ){
		sptr->swpc = 0;
	} else {
		temp3 = temp & 0xFF;
		temp2 = temp >> 8;
		temp3 = (sptr->swsc * temp3) >> 8;
		temp2 *= sptr->swsc;
		temp = temp2 + temp3;
		if( temp == 0 ){
			temp = 1;
		}
	}
	sptr->swpd += temp;
}

int vib_compute( void )
{
	int temp;
	u_int temp2;
	
	sptr->vib_tbl_cnt += sptr->vib_tc_ofst;
	sptr->vib_tbl_cnt &= 0x3F;
	temp2 = VIBX_TBL[sptr->vib_tbl_cnt & 0x1F];
	
	if( sptr->vibd >= 0x7FFF ){
		temp = (sptr->vibd >> 7) & 0xFE;
		temp = (temp * temp2) >> 8;
	} else {
		temp = ((sptr->vibd >> 8) & 0x7F) + 2;
		temp = (temp * temp2) >> 1;
	}
	
	if( sptr->vib_tbl_cnt >= 32 ){
		temp = -temp;
	}
	return temp;
}

int vib_generate( char a0 )
{
	char temp2;
	int temp3;
	
	if( a0 < 0 ){
		temp2 = -((u_char)a0) << 1;
		if( temp2 < 0 ){
			temp2 = -temp2;
		}
		temp2 = (u_char)temp2 >> 2;
		temp3 = ((sptr->vibd >> 8) & 0xFF) * temp2;
		temp3 = -temp3;
	} else {
		temp2 = (u_char)a0 << 1;
		if( temp2 < 0 ){
			temp2 = -temp2;
		}
		temp2 = (u_char)temp2 >> 2;
		temp3 = ((sptr->vibd >> 8) & 0xFF) * temp2;
	}
	if( sptr->vibdm >= 0x7FFF ){
		temp3 >>= 2;
	}
	return temp3;
}

void bendch( void )
{
	int temp;
	
	if( !sptr->swpc ){
		mdata1 = mptr[3];
		if( mdata1 == 0xE4 ){
			sptr->swphc = mptr[2];
			sptr->swpc = mptr[1];
			temp = mptr[0];
			mptr += 4;
			temp = (temp + sptr->ptps) << 8;
			temp += sptr->tund;
			swpadset( temp );
		}
	}
}

void note_cntl( void )
{
	char temp;
	u_int temp2, temp3, temp4, temp5, temp6;
	
	if( sptr->vol && sptr->tred && (sptr->trehs == sptr->trehc) ){
		temp = sptr->tmpd;
		sptr->trec += ((sptr->trecad * temp) >> 8);
		if( sptr->trec < 0 ){
			temp6 = sptr->tred * -(sptr->trec);
		} else if( sptr->trec == 0 ){
			temp6 = 1;
		} else {
			temp6 = sptr->tred * sptr->trec;
		}
		volxset( (temp6 >> 8) & 0xFF );
	}
	
	temp4 = 0;
	temp5 = sptr->swpd;
	
	if( sptr->swpc && !sptr->swphc ){
		temp4 = 1;
		if( !sptr->swsk ){
			sptr->swpd += sptr->swpad;
		} else {
			por_compute();
		}
		temp5 = sptr->swpd;
	}
	
	if( sptr->vibd && (sptr->vibhs == sptr->vibhc) ){
		sptr->vib_tmp_cnt += sptr->vibcad;
		if( sptr->vib_tmp_cnt >= 256 ){
			sptr->vib_tmp_cnt &= 0xFF;
			temp3 = vib_compute();
			temp5 += temp3;
			temp4 = 1;
		}
	}
	
	temp2 = random();
	
	if( temp2 ){
		temp4 = 1;
		temp5 += temp2;
	}
	
	if( temp4 ){
		freq_set( temp5 );
	}
}

u_int random( void )
{
	u_int temp = 0;
	char temp2;
	
	if( sptr->rdms ){
		sptr->rdmc += sptr->rdms;
		if( sptr->rdmc > 256 ){
			sptr->rdms &= 0xFF;
			sptr->rdmo++;
			sptr->rdmo &= 0x7F;
			temp2 = rdm_tbl[sptr->rdmo];
			temp = rdm_tbl[sptr->rdmo+1] << 8;
			temp += temp2;
			temp &= sptr->rdmd;
		}
	}
	return temp;
}

void tempo_ch( void )
{
	if( sptr->tmpc ){
		if( !(--sptr->tmpc) ){
			sptr->tmpw = sptr->tmpm << 8;
		} else {
			sptr->tmpw += sptr->tmpad;
		}
		sptr->tmp = sptr->tmpw >> 8;
	}
}

void volxset( u_char a0 )
{
	int temp, temp2;
	
	temp = sptr->vol;
	temp -= a0;
	temp += sptr->lp1_vol;
	temp += sptr->lp2_vol;
	
	if( temp < 0 ){
		temp = 0;
	} else if( temp >= 128 ){
		temp = 0x7F;
	}
	
	temp2 = (sptr->pvod >> 8) & 0xFF;
	vol_set( ((temp2 * temp + 128) >> 8) & 0xFF );
}

void fader_automation1( void )
{
	int temp, temp2;
	
	if( sptr->unkE8 == 1 && (sptr->unkE4 != auto_phase_fg) ){
		sptr->unkE4 = auto_phase_fg;
		
		switch( auto_phase_fg ){
		case 0: break;
		case 1: temp = (sptr->unkE9 << 8) + sptr->unkE9; temp2 = sptr->unkF1; break;
		case 2: temp = (sptr->unkEA << 8) + sptr->unkEA; temp2 = sptr->unkF2; break;
		case 3: temp = (sptr->unkEB << 8) + sptr->unkEB; temp2 = sptr->unkF3; break;
		case 4: temp = (sptr->unkEC << 8) + sptr->unkEC; temp2 = sptr->unkF4; break;
		case 5: temp = (sptr->unkED << 8) + sptr->unkED; temp2 = sptr->unkF5; break;
		case 6: temp = (sptr->unkEE << 8) + sptr->unkEE; temp2 = sptr->unkF6; break;
		case 7: temp = (sptr->unkEF << 8) + sptr->unkEF; temp2 = sptr->unkF7; break;
		case 8: temp = (sptr->unkF0 << 8) + sptr->unkF0; temp2 = sptr->unkF8; break;
		default:
			auto_phase_fg = 0;
			break;
		}
		
		if( auto_phase_fg ){
			mix_fader[mtrack].unk08 = temp;
			if( mix_fader[mtrack].unk08 == mix_fader[mtrack].unk04 ){
				mix_fader[mtrack].unk00 = 0;
			} else {
				if( temp2 ){
					mix_fader[mtrack].unk00 = (mix_fader[mtrack].unk08 - mix_fader[mtrack].unk04) / (temp2 * 10);
					if( mix_fader[mtrack].unk00 == 0 ){
						mix_fader[mtrack].unk00 = 1;
					}
				} else {
					mix_fader[mtrack].unk04 = mix_fader[mtrack].unk08;
					mix_fader[mtrack].unk00 = 0;
				}
			}
		}
	}
}

void fader_automation2( void )
{
	int temp, temp2;
	
	if( (sptr->unkE4 != auto_env_pos && sptr->unkE8 == 2) || (sptr->unkE4 != auto_env_pos2 && sptr->unkE8 == 3) ){
		switch(sptr->unkE8) {
		case 2: sptr->unkE4 = auto_env_pos; break;
		case 3: sptr->unkE4 = auto_env_pos2; break;
		default:
			break;
		}
		
		if( sptr->unkE4 >= sptr->unkF1 ){
			temp = (sptr->unkE9 << 8) + sptr->unkE9;
		} else if( sptr->unkE4 >= sptr->unkF2 ){
			temp = (sptr->unkE4 - sptr->unkF1) * (sptr->unkEA - sptr->unkE9);
			temp = ((temp << 8) + temp) / (sptr->unkF2 - sptr->unkF1);
			temp += (sptr->unkE9 << 8) + sptr->unkE9;
		} else if( sptr->unkE4 >= sptr->unkF3 ){
			temp = (sptr->unkE4 - sptr->unkF2) * (sptr->unkEB - sptr->unkEA);
			temp = ((temp << 8) + temp) / (sptr->unkF3 - sptr->unkF2);
			temp += (sptr->unkEA << 8) + sptr->unkEA;
		} else if( sptr->unkE4 >= sptr->unkF4 ){
			temp = (sptr->unkE4 - sptr->unkF3) * (sptr->unkEC - sptr->unkEB);
			temp = ((temp << 8) + temp) / (sptr->unkF4 - sptr->unkF3);
			temp += (sptr->unkEB << 8) + sptr->unkEB;
		} else if( sptr->unkE4 >= sptr->unkF5 ){
			temp = (sptr->unkE4 - sptr->unkF4) * (sptr->unkED - sptr->unkEC);
			temp = ((temp << 8) + temp) / (sptr->unkF5 - sptr->unkF4);
			temp += (sptr->unkEC << 8) + sptr->unkEC;
		} else if( sptr->unkE4 >= sptr->unkF6 ){
			temp = (sptr->unkE4 - sptr->unkF5) * (sptr->unkEE - sptr->unkED);
			temp = ((temp << 8) + temp) / (sptr->unkF6 - sptr->unkF5);
			temp += (sptr->unkED << 8) + sptr->unkED;
		} else if( sptr->unkE4 >= sptr->unkF7 ){
			temp = (sptr->unkE4 - sptr->unkF6) * (sptr->unkEF - sptr->unkEE);
			temp = ((temp << 8) + temp) / (sptr->unkF7 - sptr->unkF6);
			temp += (sptr->unkEE << 8) + sptr->unkEE;
		} else if( sptr->unkE4 >= sptr->unkF8 ){
			temp = (sptr->unkE4 - sptr->unkF7) * (sptr->unkF0 - sptr->unkEF);
			temp = ((temp << 8) + temp) / (sptr->unkF8 - sptr->unkF7);
			temp += (sptr->unkEF << 8) + sptr->unkEF;
		} else {
			temp = (sptr->unkF0 << 8) + sptr->unkF0;
		}
		
		temp2 = 1;
		mix_fader[mtrack].unk08 = temp;
		
		if( mix_fader[mtrack].unk08 == mix_fader[mtrack].unk04 ){
			mix_fader[mtrack].unk00 = 0;
		} else {
			if( temp2 ){
				mix_fader[mtrack].unk00 = (mix_fader[mtrack].unk08 - mix_fader[mtrack].unk04) / (temp2 * 10);
				if( !mix_fader[mtrack].unk00 ){
					mix_fader[mtrack].unk00 = 1;
				}
			} else {
				mix_fader[mtrack].unk04 = mix_fader[mtrack].unk08;
				mix_fader[mtrack].unk00 = 0;
			}
		}
	}
}

/*---------------------------------------------------------------------------*
 * END OF FILE
 *---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=unix fenc=euc-jp : */
