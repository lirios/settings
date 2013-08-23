#!/bin/bash
basefilename=hawaii-system-preferences
cat ${basefilename}.desktop.in > ${basefilename}.desktop
grep --no-filename '\[.*]\s*=' ${basefilename}_*.desktop >> ${basefilename}.desktop
