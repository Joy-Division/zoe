// todo: add prototypes/includes

struct foo {
    unsigned char unk00[0xC];
    int unk0C;
    int unk10;
    int unk14;
    int unk18;
    unsigned unk1C;
    int unk20;
    unsigned char unk24[0x3C];
    int unk60;
    int unk64;
    unsigned unk68;
    int unk6C;
    unsigned int *unk70;
    unsigned int *unk74;
    int unk78;
    int unk7C;
    unsigned char unk80[0x10];
};

struct foo work;

void _ftext(void) {
    int temp20, temp1C, temp18, temp14, temp10;
    while(1) {
        SleepThrea();
        switch(work.unk7C) {
            case 0:
            case 4: {
                work.unk60 = work.unk18;
                if((work.unk6C = pcOpen(&work.unk24, 1)) < 0) {
                    work.unk10 = 4;
                    sif_send_mem(work.unk60, &work, 0x60);
                    break;
                }
                work.unk14 = pcLseek(work.unk6C, 0, 2);
                if(!work.unk7C) {
                    pcLseek(work.unk6C, 0, 0);
                    work.unk20 = 0;
                }
                else {
                    pcLseek(work.unk6C, work.unk20, 0);
                }
                work.unk10 = 0;
                sif_send_mem(work.unk60, &work, 0x60);
                break;
            }
            case 1: {
                temp20 = work.unk1C;
                temp1C = 0;
                temp14 = 0;
                temp10 = work.unk18;
                work.unk10 = 2;
                sif_send_mem(work.unk60, &work, 0x60);
                while(temp20 < 1 && work.unk7C != 3) {
                    temp18 = (temp20 <= 0x8000) ? 0x8000 : temp20;
                    work.unk20 += pcRead(work.unk6C, work.unk70[temp1C], temp18);
                    work.unk64 -= temp18;
                    if(temp14) {
                        while(sif_check_status(temp14) >= 0);
                    }
                    do {
                        sif_send_mem(temp10, work.unk70[temp1C], (temp18+0xF) & 0xFFFFFFF0);
                    } while(!temp14);
                    temp20 -= temp18;
                    temp10 += temp18;
                    temp1C ^= 1;
                }
                if(temp14) {
                    while(sif_check_status(temp14) >= 0);
                }
                work.unk10 = 0;
                sif_send_mem(work.unk60, &work, 0x60);
                break;
            }
            case 2: {
                pcClose(work.unk6C);
                work.unk10 = 0;
                sif_send_mem(work.unk60, &work, 0x60);
                work.unk6C = -1;
                break;
            }
            case 3: {
                if(work.unk6C >= 0) {
                    pcClose(work.unk6C);
                    work.unk6C = -1;
                }
                work.unk10 = 0;
                sif_send_mem(work.unk60, &work, 0x60);
                break;
            }
        }
    }
}

void CallBackFunc(struct foo *a0, struct foo *a1) {
    struct foo *temp = a1;
    temp->unk7C = a0->unk0C;
    switch(temp->unk7C) {
        case 4:
        case 0: {
            if(temp->unk6C > 0) {
                break;
            }
            temp->unk6C = -1;
            memcpy(temp, a0, 0x60);
            break;
        }
        case 1: {
            if(temp->unk6C < 0) {
                break;
            }
            memcpy(temp, a0, 0x60);
            break;
        }
        case 2: {
            if(temp->unk6C < 0) {
                break;
            }
            memcpy(temp, a0, 0x60);
            break;
        }
        default: {
            break;
        }
    }
    iWakeupThread(temp->unk78);
}

int FS_StartDaemonIOP(void) {
    struct ThreadParam param;
    int tid;
    work.unk70 = AllocSysMemory(0, 0x8000, 0);
    work.unk74 = AllocSysMemory(0, 0x8000, 0);
    work.unk6C = -1;

    param.attr = 0x2000000;
    param.entry = _ftext;
    param.initPriority = 0x52;
    param.stackSize = 0x1000;

    tid = createThread(&param);
    if(tid > 0) {
        work.unk78 = tid;
        StartThread(tid, 0);
        sif_set_callback_func(2, CallBackFunc, &work);
    }
    else return 1;
    return 0;
}