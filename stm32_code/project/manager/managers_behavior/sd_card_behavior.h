/*
 * sd_card_behavior.h
 *
 *  Created on: Jun 2, 2025
 *      Author: viny
 */

#ifndef MANAGER_MANAGERS_BEHAVIOR_SD_CARD_BEHAVIOR_H_
#define MANAGER_MANAGERS_BEHAVIOR_SD_CARD_BEHAVIOR_H_

#include "../manager.h"
extern char SDPath[4]; /* SD logical drive path */

void sd_card_init (void);
void sd_card_update (void);

#endif /* MANAGER_MANAGERS_BEHAVIOR_SD_CARD_BEHAVIOR_H_ */
