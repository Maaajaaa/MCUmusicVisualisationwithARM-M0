#include "MFCC_BASICIMPL.h"

//based on kws_ds_cnn.cpp
MFCC_BASICIMPL::MFCC_BASICIMPL(int16_t* audio_data_buffer)
{
    audio_buffer = audio_data_buffer;
    sliding_window_len = 1;
    init_mfcc();
}

MFCC_BASICIMPL::~MFCC_BASICIMPL()
{
}
