/*
 * Copyright (C) 2018 Arm Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Description: Keyword spotting example code using MFCC feature extraction
 * and neural network. 
 */


//from dnn.h
#define SAMP_FREQ 16000
#define MFCC_DEC_BITS 2
#define FRAME_SHIFT_MS 40
#define FRAME_SHIFT ((int16_t)(SAMP_FREQ * 0.001 * FRAME_SHIFT_MS))
#define NUM_FRAMES 25
#define NUM_MFCC_COEFFS 10
#define MFCC_BUFFER_SIZE (NUM_FRAMES*NUM_MFCC_COEFFS)
#define FRAME_LEN_MS 40
#define FRAME_LEN ((int16_t)(SAMP_FREQ * 0.001 * FRAME_LEN_MS))

#include "mfcc_mcu.h"

MFCC_MCU::MFCC_MCU()
{
}

MFCC_MCU::~MFCC_MCU()
{
  delete mfcc;
}

void MFCC_MCU::init_mfcc()
{
  num_mfcc_features;//nn->get_num_mfcc_features();
  num_frames; //nn->get_num_frames();
  frame_len; //nn->get_frame_len();
  frame_shift; //nn->get_frame_shift();

  
  frame_len = FRAME_LEN;
  frame_shift = FRAME_SHIFT;
  num_mfcc_features = NUM_MFCC_COEFFS;
  num_frames = NUM_FRAMES;
  in_dec_bits = MFCC_DEC_BITS;

  mfcc = new MFCC(num_mfcc_features, frame_len, in_dec_bits);
  mfcc_buffer = new q7_t[num_frames*num_mfcc_features];
  audio_block_size = recording_win*frame_shift;
  audio_buffer_size = audio_block_size + frame_len - frame_shift;
  
}

void MFCC_MCU::extract_features() 
{
  if(num_frames>recording_win) {
    //move old features left 
    memmove(mfcc_buffer,mfcc_buffer+(recording_win*num_mfcc_features),(num_frames-recording_win)*num_mfcc_features);
  }
  //compute features only for the newly recorded audio
  int32_t mfcc_buffer_head = (num_frames-recording_win)*num_mfcc_features; 
  for (uint16_t f = 0; f < recording_win; f++) {
    mfcc->mfcc_compute(audio_buffer+(f*frame_shift),&mfcc_buffer[mfcc_buffer_head]);
    mfcc_buffer_head += num_mfcc_features;
  }
}  
