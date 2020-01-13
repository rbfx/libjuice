/**
 * Copyright (c) 2020 Paul-Louis Ageneau
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "juice/juice.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void on_state_changed(juice_agent_t *agent, juice_state_t state,
                      void *user_ptr) {}

void on_candidate(juice_agent_t *agent, const char *sdp, void *user_ptr) {
	printf("Candidate: %s\n", sdp);
}

void on_recv(juice_agent_t *agent, const char *data, size_t size,
             void *user_ptr) {}

int main(int argc, char **argv) {
	juice_log_set_level(JUICE_LOG_LEVEL_VERBOSE);

	juice_config_t config;
	config.is_lite = false;
	config.is_controlling = true;
	config.cb_state_changed = on_state_changed;
	config.cb_candidate = on_candidate;
	config.cb_recv = on_recv;

	juice_agent_t *agent = juice_agent_create(&config);

	char buffer[BUFFER_SIZE];
	juice_agent_get_local_description(agent, buffer, BUFFER_SIZE);
	printf("Local description:\n%s\n", buffer);

	juice_agent_gather_candidates(agent);

	sleep(2);

	juice_agent_get_local_description(agent, buffer, BUFFER_SIZE);
	printf("Local description:\n%s\n", buffer);
	return 0;
}
