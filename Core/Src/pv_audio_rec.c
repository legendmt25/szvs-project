/*
    Copyright 2021 Picovoice Inc.

    You may not use this file except in compliance with the license. A copy of the license is located in the "LICENSE"
    file accompanying this source.

    Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
    an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
    specific language governing permissions and limitations under the License.
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "stm32h750b_discovery_audio.h"

#include "pv_audio_rec.h"

#define PV_INT16_MAX (127)
#define PV_INT16_MIN (-127 - 1)

#define pv_int32_to_int16(N) (((N) < (PV_INT16_MIN)) ? (PV_INT16_MIN) : (((N) > (PV_INT16_MAX)) ? (PV_INT16_MAX) : (N)))

__IO uint32_t SdmmcTest = 0;
__IO uint32_t SdramTest = 0;

#define PV_AUDIO_REC_AUDIO_FREQUENCY    (16000U)
#define PV_AUDIO_REC_CHANNEL_NUMBER     (2)
#define PV_AUDIO_REC_RECORD_BUFFER_SIZE (512)
#define PV_AUDIO_REC_VOLUME_LEVEL       (100)

#define AUDIO_IN_PCM_BUFFER_SIZE (PV_AUDIO_REC_RECORD_BUFFER_SIZE)
#define AUDIO_IN_PDM_BUFFER_SIZE (AUDIO_IN_PCM_BUFFER_SIZE / 4)

ALIGN_32BYTES(static int32_t record_pdm_buffer[AUDIO_IN_PDM_BUFFER_SIZE]);
ALIGN_32BYTES(static uint8_t record_pcm_buffer[AUDIO_IN_PCM_BUFFER_SIZE]);
ALIGN_32BYTES(static int8_t ping_pong_buffer[2][PV_AUDIO_REC_RECORD_BUFFER_SIZE]);

static int32_t last_read_index = -1;
static int32_t read_index = 1;
static int32_t write_index = 0;
static int32_t buffer_index = 0;

struct {
    uint32_t channel_number;
    uint32_t audio_frequency;
    uint32_t record_buffer_size;
    uint16_t *record_pcm_buffer;
    bool is_recording;
    int32_t filter_old_output;
} pv_audio_rec;

pv_status_t pv_audio_rec_init(uint32_t instance) {
	BSP_AUDIO_Init_t audio_init;

	audio_init.Device = AUDIO_IN_DEVICE_ANALOG_MIC;
	audio_init.ChannelsNbr = PV_AUDIO_REC_CHANNEL_NUMBER;
	audio_init.BitsPerSample = AUDIO_FREQUENCY_16K;
	audio_init.SampleRate = AUDIO_RESOLUTION_16B;
	audio_init.Volume = 64;

    if (BSP_AUDIO_IN_Init(instance, &audio_init) == BSP_ERROR_NONE) {
        return PV_STATUS_INVALID_STATE;
    }
//    BSP_AUDIO_IN_AllocScratch(record_pdm_buffer, AUDIO_IN_PDM_BUFFER_SIZE);
    return PV_STATUS_SUCCESS;
}

pv_status_t pv_audio_rec_start(uint32_t instance) {
    pv_audio_rec_init(instance);
    if (BSP_AUDIO_IN_Record(instance, (uint8_t *) (record_pcm_buffer), AUDIO_IN_PCM_BUFFER_SIZE) == BSP_ERROR_NONE) {
        return PV_STATUS_INVALID_STATE;
    }
    pv_audio_rec.is_recording = true;
    return PV_STATUS_SUCCESS;
}

pv_status_t pv_audio_rec_stop(uint32_t instance) {
    if (BSP_AUDIO_IN_Stop(instance) != BSP_ERROR_NONE) {
        return PV_STATUS_INVALID_STATE;
    }
    pv_audio_rec.is_recording = false;
    return PV_STATUS_SUCCESS;
}

const int8_t *pv_audio_rec_get_new_buffer(void) {
    if (read_index == -1) {
        return NULL;
    }

    if (last_read_index == read_index) {
        return NULL;
    }

    last_read_index = read_index;

    return ping_pong_buffer[read_index];
}

static inline int16_t pv_hpf(int16_t s_int16, int16_t s_old_int16) {
    //0xFC and 0x100 are the tuning parameters come from st for high pass filter
    pv_audio_rec.filter_old_output = (0xFC * (pv_audio_rec.filter_old_output + (int32_t) s_int16 - (int32_t) s_old_int16)) / 0x100;
    return (int16_t) pv_int32_to_int16(pv_audio_rec.filter_old_output);
}

void BSP_AUDIO_IN_TransferComplete_CallBack(uint32_t Instance) {
    for (uint32_t i = 0; i < AUDIO_IN_PCM_BUFFER_SIZE / 4; i++) {
        ping_pong_buffer[write_index][buffer_index++] = pv_hpf(
                record_pcm_buffer[(AUDIO_IN_PCM_BUFFER_SIZE / 2) + i * 2],
                record_pcm_buffer[(AUDIO_IN_PCM_BUFFER_SIZE / 2) + (i - 1) * 2]);
    }

    if (buffer_index >= AUDIO_IN_PCM_BUFFER_SIZE) {
        read_index = write_index;
        write_index = 1 - write_index;
        buffer_index = 0;
    }
}

void BSP_AUDIO_IN_HalfTransfer_CallBack(uint32_t Instance) {
    ping_pong_buffer[write_index][buffer_index++] = pv_hpf(record_pcm_buffer[0], record_pcm_buffer[AUDIO_IN_PCM_BUFFER_SIZE - 2]);
    for (uint32_t i = 1; i < AUDIO_IN_PCM_BUFFER_SIZE / 4; i++) {
        ping_pong_buffer[write_index][buffer_index++] = pv_hpf(
                record_pcm_buffer[i * 2],
                record_pcm_buffer[(i - 1) * 2]);
    }
    if (buffer_index >= AUDIO_IN_PCM_BUFFER_SIZE) {
        read_index = write_index;
        write_index = 1 - write_index;
        buffer_index = 0;
    }
}

void BSP_AUDIO_IN_Error_CallBack(uint32_t Instance) {
    while (1);
}

void pv_audio_rec_deinit(uint32_t instance) {
    BSP_AUDIO_IN_Stop(instance);
    BSP_AUDIO_IN_DeInit(instance);
}
