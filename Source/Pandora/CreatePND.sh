#!/bin/bash

export TAG_NAME=`git describe --tags | sed -e 's/_[0-9].*//'`
export VERSION_NUM=`git describe --match "${TAG_NAME}_[0-9]*" HEAD | sed -e 's/-g.*//' -e "s/${TAG_NAME}_//"`
export MAJOR=`echo $VERSION_NUM | sed 's/-[^.]*$//' | sed -r 's/.[^.]*$//' | sed -r 's/.[^.]*$//'`
export MINOR=`echo $VERSION_NUM | sed 's/-[^.]*$//' | sed -r 's/.[^.]*$//' | sed -r 's/.[.]*//'`
export REVISION=`echo $VERSION_NUM | sed 's/-[^.]*$//' | sed -r 's/.*(.[0-9].)//'`
export BUILD=`echo $VERSION_NUM | sed -e 's/[0-9].[0-9].[0-9]//' -e 's/-//'`

export ROOTDIR=$(cd ../../ && pwd)

mkdir -p ${ROOTDIR}/Build/PND
cp -rv ${ROOTDIR}/Bin/Pandora/arm/32/Killer ${ROOTDIR}/Build/PND/

cat > ${ROOTDIR}/Build/PND/Killer_PXML.xml << __EOF__
<?xml version="1.0" encoding="UTF-8"?>
<PXML xmlns="http://openpandora.org/namespaces/PXML">
	<package id="Rico.Killer">
		<version major="${MAJOR}" minor="${MINOR}" release="${REVISION}" build="${BUILD}"/>
		<author name="Rico Tyrell" email="killer@redringrico.com"/>
		<titles>
			<title lang="en_US">Killer</title>
			<title lang="en_GB">Killer</title>
		</titles>
	</package>
	<application id="Rico.Killer">
		<titles>
			<title lang="en_US">Killer</title>
			<title lang="en_GB">Killer</title>
		</titles>
		<version major="${MAJOR}" minor="${MINOR}" release="${REVISION}" build="${BUILD}"/>
		<descriptions>
			<description lang="en_US">An arcade-style 3D beat-'em-up</description>
			<description lang="en_GB">An arcade-style 3D beat-'em-up</description>
		</descriptions>
		<exec command="Killer"/>
		<author name="Rico Tyrell" email="killer@redringrico.com"/>
		<categories>
			<category name="Game">
				<subcategory name="ArcadeGame"/>
			</category>
		</categories>
		<licenses>
			<license name="GPLv3" url="http://www.gnu.org/licenses/gpl.html" sourcecodeurl="https://www.github.com/RedRingRico/Killer"/>
		</licenses>
	</application>
</PXML>
__EOF__

cat > ${ROOTDIR}/Build/PND/powervr.ini << __EOF__
[default]
WindowSystem=libpvrPVR2D_FLIPWSEGL.so
__EOF__

cp -rv ${ROOTDIR}/Content/* ${ROOTDIR}/Build/PND/

cp --preserve=links -rv $PANDORA_SDK/toolchain/arm-none-linux-gnueabi/lib/libstdc++.*so* ${ROOTDIR}/Build/PND/
rm -rv ${ROOTDIR}/Build/PND/libstdc++.so.6.0.18-gdb.py

./pnd_make.sh -d ${ROOTDIR}/Build/PND -p ${ROOTDIR}/Build/killer.pnd -x ${ROOTDIR}/Build/PND/Killer_PXML.xml

