#!/bin/bash

_mpd_cached="/tmp/mpd.db"
_mpd_org="/home/wor/.mpd/mpd.db"

if ck_daemon mpd; then 
    # mpd stopped -> to start
    if [[ -f ${_mpd_org} && $1 == start ]]; then
        echo "caching mpd.db $1"
        mv "${_mpd_org}" "${_mpd_cached}" || exit 1
        ln -s "${_mpd_cached}" "${_mpd_org}" || exit 1
    fi
else
    # mpd running -> to stop
    if [[ -e ${_mpd_cached} && -L ${_mpd_org} && $1 == stop ]]; then
        echo "uncaching mpd.db $1"
        mv "${_mpd_cached}" "${_mpd_org}"  
    fi
fi

unset -v _mpd_cached
unset -v _mpd_org
