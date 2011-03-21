#!/bin/bash
/usr/bin/python ~/workspace/python/putclub/src/putclub.py all > ~/listning.html
if [ -d ~/listen ]
then
	filename=`date +%y%m%d`.html
else
   	mkdir ~/listen
fi
/usr/bin/python ~/workspace/python/putclub/src/putclub.py date down > ~/listen/$filename \
	&& cp -ru mp3 ~/listen/	\
	&& rm -rf mp3

