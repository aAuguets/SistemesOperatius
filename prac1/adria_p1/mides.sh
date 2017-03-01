#!/bin/sh
#daaddaddasddadaaddadadadaaddadadaaaaaaaaaaaaaaaaaaaaas
chmod a+x mides.sh

#ls -l  --sort=size $1 | cut -f 5,6 -d" "
ls -h -l --block-size=k $1 | cut -f 5,9 -d" "
