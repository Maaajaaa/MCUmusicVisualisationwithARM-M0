//class tat implements the mfcc mcu

#ifndef __MFCC_BASICIMPL_H__
#define __MFCC_BASICIMPL_H__

class MFCC_BASICIMPL : public MFCC_MCU {
    public: 
        MFCC_BASICIMPL(int16_t* audio_buffer);
        ~MFCC_BASICIMPL();
};

#endif