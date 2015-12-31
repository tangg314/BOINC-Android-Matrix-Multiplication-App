#!/bin/bash

##registers files to download folder and generates work
~/projects/test4vm/bin/stage_file --copy server/7999

for t in {0..7999..1}
do
~/projects/test4vm/bin/create_work --appname compute --wu_name t0_$t --wu_template templates/inputA7999.xml --result_template templates/outputA0.xml A7999 B7999 name
done

