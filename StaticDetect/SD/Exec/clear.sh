#!/bin/sh

###############################
#	by chenfei
#	date: 2016/02/26
###############################



# clear InfoDir. ResDir. DetectDir

echo "Clear InfoDir, CloudDetectDir, FTP, GW, MAIL";


rm -rf /SSP/Detect/InfoDir/*.json;
rm -rf /SSP/Detect/CloudDetectDir/*.json;
rm -rf /SSP/Data/FTP/*.json;
rm -rf /SSP/Data/GW/*.json;
rm -rf /SSP/Data/MAIL/*.json;


echo "Clear End";
echo "Ready.......";




