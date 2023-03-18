#include "MFCC_BasicImpl.h"

//based on kws_ds_cnn.cpp
MFCC_BasicImpl::MFCC_BasicImpl(int16_t* audio_data_buffer)
{
    audio_buffer = audio_data_buffer;
    sliding_window_len = 1;
    init_mfcc();
}

MFCC_BasicImpl::~MFCC_BasicImpl()
{
}
