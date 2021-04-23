// Copyright (c) 2011-2020 The Bitcoin Core developers
// Copyright (c) 2021 The PIVX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PIVX_MAPPORT_H
#define PIVX_MAPPORT_H

/** -upnp default */
#ifdef USE_UPNP
static const bool DEFAULT_UPNP = USE_UPNP;
#else
static const bool DEFAULT_UPNP = false;
#endif

void StartMapPort();
void InterruptMapPort();
void StopMapPort();

#endif //PIVX_MAPPORT_H
