/*
    Copyright 2021 Picovoice Inc.

    You may not use this file except in compliance with the license. A copy of the license is located in the "LICENSE"
    file accompanying this source.

    Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
    an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
    specific language governing permissions and limitations under the License.
*/

#ifndef PV_ST_H750_H
#define PV_ST_H750_H

#include "pv_picovoice.h"

#define PV_BOARD_NAME "STM32F769I-DISCO"

pv_status_t pv_init(pv_picovoice_t* handle);
const uint8_t *pv_get_uuid(void);
const uint32_t pv_get_uuid_size(void);
void pv_deinit(pv_picovoice_t* handle);

#endif // PV_ST_H750_H

