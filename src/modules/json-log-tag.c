/*
 *   IRC - Internet Relay Chat, src/modules/monitor.c
 *   (C) 2021 Bram Matthys and The UnrealIRCd Team
 *
 *   See file AUTHORS in IRC package for additional names of
 *   the programmers.
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 1, or (at your option)
 *   any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "unrealircd.h"

ModuleHeader MOD_HEADER
  = {
	"json-log-tag",
	"5.0",
	"unrealircd.org/json-log tag for S2S and ircops",
	"UnrealIRCd Team",
	"unrealircd-5",
    };

/* Forward declarations */
int json_log_mtag_is_ok(Client *client, char *name, char *value);
int json_log_mtag_can_send(Client *target);

MOD_INIT()
{	
	MessageTagHandlerInfo mtag;

	MARK_AS_OFFICIAL_MODULE(modinfo);

	memset(&mtag, 0, sizeof(mtag));
	mtag.name = "unrealircd.org/json-log";
	mtag.is_ok = json_log_mtag_is_ok;
	mtag.can_send = json_log_mtag_can_send;
	mtag.flags = MTAG_HANDLER_FLAGS_NO_CAP_NEEDED;
	MessageTagHandlerAdd(modinfo->handle, &mtag);

	return MOD_SUCCESS;
}

MOD_LOAD()
{
	return MOD_SUCCESS;
}

MOD_UNLOAD()
{
	return MOD_SUCCESS;
}

/** This function verifies if the client sending
 * We simply allow from servers without any syntax checking.
 */
int json_log_mtag_is_ok(Client *client, char *name, char *value)
{
	if (IsServer(client) || IsMe(client))
		return 1;

	return 0;
}

/** Outgoing filter for this message tag */
int json_log_mtag_can_send(Client *target)
{
	if (IsServer(target) || IsOper(target))
		return 1;
	return 0;
}
