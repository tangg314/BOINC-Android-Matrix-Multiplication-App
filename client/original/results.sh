#!/bin/bash

##generates matrix C elements from all of the workload folders
for t in {0..124..1}
do
	cp compute /home/gtics/Documents/632/pro/client/original/$t
	cd /home/gtics/Documents/632/pro/client/original/$t
	./compute >> /home/gtics/Documents/632/pro/client/results.txt
done
