#!/bin/bash
/usr/bin/python ~/workspace/python/putclub/src/putclub.py all >/var/www/listning.html
if [ -d /var/www/listen ]
then
	filename=`date +%y%m%d`.html
else
   	mkdir /var/www/listen
fi
/usr/bin/python ~/workspace/python/putclub/src/putclub.py date down >/var/www/listen/$filename \
	&& cp -ru mp3 /var/www/listen/	\
	&& rm -rf mp3

