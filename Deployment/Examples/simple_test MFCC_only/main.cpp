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
 * Description: Example code for running keyword spotting on Cortex-M boards
 */

#include "mfcc_basicimpl.h"
#include "wav_data.h"

int16_t audio_buffer[16000]=WAVE_DATA;

Timer T;
Serial pc(USBTX, USBRX);

int main()
{
  MFCC_BASICIMPL mfccImpl(audio_buffer);

  T.start();
  int start=T.read_us();
  mfccImpl.extract_features(); //extract mfcc features
  int end=T.read_us();
  T.stop();
  pc.printf("Total time : %d us\r\n",end-start);
  //print mfcc outputs

  for(int frame=0; frame < 25; frame++){
    pc.printf("frame %d: ", frame);
    for(int feature=0; feature < 10; feature++){
      // To print to 10 decimal places after the . with a rounded value, scale the fraction by 1010 and then divide by 232.
      //https://stackoverflow.com/a/57455345
      // Multiplied by 10^7 then divived by 2^8
      uint8_t feature_float = (mfccImpl.mfcc_buffer[frame*25+feature] * 10000000 + 128 )/ 256;
      pc.printf(" %1.7f ", feature_flot);
    }
  }
  
  printf("Detected %s (%d%%)\r\n",output_class[max_ind],((int)kws.output[max_ind]*100/128));

  return 0;
}
