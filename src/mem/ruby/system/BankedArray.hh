/*
 * Copyright (c) 2012 Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: Brad Beckmann
 *
 */

#ifndef __MEM_RUBY_SYSTEM_BANKEDARRAY_HH__
#define __MEM_RUBY_SYSTEM_BANKEDARRAY_HH__

#include <vector>

#include "mem/ruby/common/TypeDefines.hh"
#include "sim/eventq.hh"



class BankedArray : public EventManager
{
private:
    unsigned int banks;
    unsigned int accessLatency;
    unsigned int bankBits;
    unsigned int startIndexBit;

    //std::vector<bool> busyBanks;

    class TickEvent : public Event
    {
    public:
        TickEvent() : Event() {}
        void process() {}
        Index idx;
        Tick startAccess;
    };
    friend class TickEvent;

    // If the tick event is scheduled then the bank is busy
    // otherwise, schedule the event and wait for it to complete
    std::vector<TickEvent> busyBanks;

    unsigned int mapIndexToBank(Index idx);

public:
    BankedArray(unsigned int banks, unsigned int accessLatency, unsigned int startIndexBit);

    // Note: We try the access based on the cache index, not the address
    // This is so we don't get aliasing on blocks being replaced
    bool tryAccess(Index idx);

};

#endif
