/*
    Copyright 2021 Picovoice Inc.

    You may not use this file except in compliance with the license. A copy of the license is located in the "LICENSE"
    file accompanying this source.

    Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
    an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
    specific language governing permissions and limitations under the License.
*/

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "stm32h750b_discovery.h"

#include "pv_params.h"
#include "pv_audio_rec.h"
#include "pv_st_h750b.h"
#include "pv_picovoice.h"

#define UUID_ADDRESS (0x1FF0F420)
#define UUID_SIZE    (12)

#define MEMORY_BUFFER_SIZE (70 * 1024)
#define AUDIO_IN_INSTANCE (0)

static const char *ACCESS_KEY = "${ACCESS_KEY}"; //AccessKey string obtained from Picovoice Console (https://picovoice.ai/console/)

static int8_t memory_buffer[MEMORY_BUFFER_SIZE] __attribute__((aligned(16)));

static const float PORCUPINE_SENSITIVITY = 0.75f;
static const float RHINO_SENSITIVITY = 0.5f;
static const float RHINO_ENDPOINT_DURATION_SEC = 1.0f;
static const bool RHINO_REQUIRE_ENDPOINT = true;

extern UART_HandleTypeDef huart1;

static uint8_t uuid[UUID_SIZE];

const uint8_t *pv_get_uuid(void) {
    return (const uint8_t *) uuid;
}

const uint32_t pv_get_uuid_size(void) {
    return UUID_SIZE;
}

static void inference_callback(pv_inference_t *inference) {
    BSP_LED_Off(LED1);
    printf("{\n");
    printf("    is_understood : '%s',\n", (inference->is_understood ? "true" : "false"));
    if (inference->is_understood) {
        printf("    intent : '%s',\n", inference->intent);
        if (inference->num_slots > 0) {
            printf("    slots : {\n");
            for (int32_t i = 0; i < inference->num_slots; i++) {
                printf("        '%s' : '%s',\n", inference->slots[i], inference->values[i]);
            }
            printf("    }\n");
        }
    }
    printf("}\n\n");
    for (int32_t i = 0; i < 10; i++) {
        BSP_LED_Toggle(LED1);
        BSP_LED_Toggle(LED2);
        HAL_Delay(30);
    }
    pv_inference_delete(inference);
}

static void wake_word_callback(void) {
    printf("[wake word]\n");
    BSP_LED_On(LED1);
}

extern void Error_Handler(void);

pv_status_t pv_init_uuid() {
    memcpy(uuid, (uint8_t *) UUID_ADDRESS, UUID_SIZE);
    return PV_STATUS_SUCCESS;
}

void print_error_message(char **message_stack, int32_t message_stack_depth) {
    for (int32_t i = 0; i < message_stack_depth; i++) {
        printf("[%ld] %s\n", i, message_stack[i]);
    }
}

pv_status_t pv_init(pv_picovoice_t* handle) {

  const uint8_t *board_uuid = pv_get_uuid();
  printf("UUID: ");
  for (uint32_t i = 0; i < pv_get_uuid_size(); i++) {
	  printf(" %.2x", board_uuid[i]);
  }
  printf("\r\n");

  pv_status_t status = pv_audio_rec_init(AUDIO_IN_INSTANCE);

  if (status != PV_STATUS_SUCCESS) {
	  printf("Audio init failed with '%s'", pv_status_to_string(status));
	  Error_Handler();
  }

  status = pv_audio_rec_start(AUDIO_IN_INSTANCE);

  if (status != PV_STATUS_SUCCESS) {
	  printf("Recording audio failed with '%s'", pv_status_to_string(status));
	  Error_Handler();
  }

  char **message_stack = NULL;
  int32_t message_stack_depth = 0;
  pv_status_t error_status;

  status =
	pv_picovoice_init(
	  ACCESS_KEY,
	  MEMORY_BUFFER_SIZE,
	  memory_buffer,
	  sizeof(KEYWORD_ARRAY),
	  KEYWORD_ARRAY,
	  PORCUPINE_SENSITIVITY,
	  wake_word_callback,
	  sizeof(CONTEXT_ARRAY),
	  CONTEXT_ARRAY,
	  RHINO_SENSITIVITY,
	  RHINO_ENDPOINT_DURATION_SEC,
	  RHINO_REQUIRE_ENDPOINT,
	  inference_callback,
	  &handle);

  if (status != PV_STATUS_SUCCESS) {
	  printf("Picovoice init failed with '%s'", pv_status_to_string(status));

	  error_status = pv_get_error_stack(&message_stack, &message_stack_depth);
	  if (error_status != PV_STATUS_SUCCESS) {
		  printf("Unable to get Picovoice error state with '%s':\n", pv_status_to_string(error_status));
		  Error_Handler();
	  }

	  print_error_message(message_stack, message_stack_depth);
	  pv_free_error_stack(message_stack);

	  Error_Handler();
  }

  const char *rhino_context = NULL;
  status = pv_picovoice_context_info(handle, &rhino_context);
  if (status != PV_STATUS_SUCCESS) {
    printf("retrieving context info failed with '%s'", pv_status_to_string(status));
    Error_Handler();
  }
  printf("Rhino context info: %s\r\n", rhino_context);
  return PV_STATUS_SUCCESS;
}

void pv_deinit(pv_picovoice_t* handle) {
  pv_audio_rec_deinit(AUDIO_IN_INSTANCE);
  pv_picovoice_delete(handle);
}

void pv_error_handler(void) {
    while (true);
}

void assert_failed(uint8_t *file, uint32_t line) {
    (void) file;
    (void) line;
    pv_error_handler();
}

int __io_putchar(int ch) {
    HAL_UART_Transmit(&huart1, (uint8_t *) &ch, 1, 1000);
    return ch;
}
