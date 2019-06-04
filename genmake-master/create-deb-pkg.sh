#!/bin/bash
build_dir=$(pwd)/build
VER=2.0
PKGNAME=genmake-${VER}

mkdir -p ${build_dir}/../src/usr/lib
mkdir -p ${build_dir}/../src/sbin

#*********copying mk files and genmake script***********#
cp -r ${build_dir}  ${build_dir}/../src/usr/lib
cp ${build_dir}/../genmake ${build_dir}/../src/sbin

#*********prepare to build installer****************#

mkdir -p ${build_dir}/../${PKGNAME}/debian 

cp -R ${build_dir}/../debpackage/* ${build_dir}/../${PKGNAME}/debian
tar pczf ${build_dir}/../${PKGNAME}.tar.gz ${build_dir}/../src
ln -s ${build_dir}/../${PKGNAME}.tar.gz ${build_dir}/../genmake_${VER}.orig.tar.gz
cp -R ${build_dir}/../src/* ${build_dir}/../${PKGNAME}/debian
sed -i s/VERSION_TEMPLATE/"$VER"/g ${build_dir}/../${PKGNAME}/debian/changelog

#****************generating installer*********************#

cd ${build_dir}/../${PKGNAME} && debuild -us -uc > /dev/null

#****************cleanup workspace***********************#

cd ${build_dir}/../ && rm -rf ${PKGNAME}* src && rm -rf *.build *.buildinfo *.changes *.xz *.dsc *.gz
