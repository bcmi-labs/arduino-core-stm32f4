#!/bin/bash
TEST_BUILD_NUMBER=$1

#Gets current version number and sets next version number
VERSION_CURR=$(cat platform.txt | grep version= | head -n 1 | sed s/^.*version=//g)
VERSION=$VERSION_CURR"-"$TEST_BUILD_NUMBER

#Gets current platform name and sets next platform name based on next version number
PLATFORM_CURR=$(cat platform.txt | grep name= | head -n 1 | sed s/^.*name=//g)
#PLATFORM_TEST=$PLATFORM_CURR" - Test Build"
PLATFORM=$PLATFORM_CURR" - Test Build: "$VERSION

PWD=`pwd`
SRC_FOLDER=`basename $PWD`
ARCH=$(echo $SRC_FOLDER | awk -F'-' '{print $3}')
FILENAME=package_arduino_${ARCH}_${VERSION}.tar.bz2
FILENAME_JSON=package_arduino_${ARCH}_${VERSION}.json

#Replaces name and version entries in platform.txt file
sed -i "s/name=.*/name=${PLATFORM}/" platform.txt
sed -i "s/version=.*/version=${VERSION}/" platform.txt

#Creates destination folder
DIST_FOLDER='dist'
if ! [ -d $DIST_FOLDER ]; then
  mkdir $DIST_FOLDER
fi

#Packs target Arduino core
tar --exclude='.DS_Store' --exclude=extras/** --exclude=$DIST_FOLDER/**  --exclude=.git* --exclude=.idea -cjf $DIST_FOLDER/$FILENAME ./

#Restores replaced entries in platform.txt
sed -i "s/name=.*/name=${PLATFORM_CURR}/" platform.txt
sed -i "s/version=.*/version=${VERSION_CURR}/" platform.txt

#Gets SHA-256 and Size of packed file
CHKSUM=`sha256sum $DIST_FOLDER/$FILENAME | awk '{ print $1 }'`
SIZE=`wc -c $DIST_FOLDER/$FILENAME | awk '{ print $1 }'`

#Create json file from tempate
cat extras/package_index.json.test.template |
sed "s/%%VERSION%%/${VERSION}/" |
sed "s/%%FILENAME%%/${FILENAME}/" |
sed "s/%%CHECKSUM%%/${CHKSUM}/" |
sed "s/%%SIZE%%/${SIZE}/" > $DIST_FOLDER/$FILENAME_JSON
