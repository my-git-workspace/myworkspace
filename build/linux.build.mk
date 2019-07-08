build_dir=$(PWD)/../build
RELEASE_VERSION=6.1
PKGNAME=qnapzfs-$(RELEASE_VERSION)
BUILDPKG=qnapzfs_$(RELEASE_VERSION)_amd64.deb
build:
	#compile linux_dependencies
	cd $(PWD)/../linux_dependencies && make clean && make && cd -
	
	#compile cddl
	cd $(PWD)/zfs-module && make clean && cd -
	cd $(PWD)/cddl && make clean && make && cd -

	#compile zfs-module
	cd $(PWD)/zfs-module && make clean && make && cd -
	
	#compile scst
	cd $(PWD)/../scst && make clean && make all && cd -
zfs:
	#compile cddl
	cd $(PWD)/zfs-module && make clean && cd -
	cd $(PWD)/cddl && make clean && make && cd -

	#compile zfs-module
	cd $(PWD)/zfs-module && make clean && make && cd -

load:
	sudo insmod $(PWD)/../linux_dependencies/ocf-linux-20171122/ocf/ocf.ko && \
	sudo insmod $(PWD)/../linux_dependencies/ocf-linux-20171122/ocf/cryptosoft.ko && \
	sudo insmod $(PWD)/sys/cddl/compat/lpl/lpl.ko && \
	sudo insmod $(PWD)/zfs-module/zfs.ko 
unload:
	sudo rmmod zfs && sudo rmmod cryptosoft && sudo rmmod ocf && sudo rmmod lpl

deb: #build
	#--------------------------------------------------------------------------------------------------------#
	#-------------------------- Copy binaries --------------------------#
	#--------------------------------------------------------------------------------------------------------#
	mkdir -p ${build_dir}/installer/src/lib/modules/4.2.8
	mkdir -p ${build_dir}/installer/src/sbin
	mkdir -p ${build_dir}/installer/src/usr/lib
	mkdir -p ${build_dir}/installer/src/etc/init.d
	mkdir -p ${build_dir}/installer/src/usr/share/man/man8
	#--------------------------------------------------------------------------------------------------------#
	#-------------------------- copy ko and so --------------------------#
	#--------------------------------------------------------------------------------------------------------#
	find $(PWD) -name "*.ko" -type f -exec cp {} ${build_dir}/installer/src/lib/modules/4.2.8 \;
	find $(PWD) -name "*.so" -type f -exec cp {} ${build_dir}/installer/src/usr/lib \;
	cd $(PWD)/../scst && find $(PWD)/../scst -name "*.ko" -type f -exec cp {} ${build_dir}/installer/src/lib/modules/4.2.8 \;
	cd $(PWD)/../scst && find $(PWD)/../scst -name "*.so" -type f -exec cp {} ${build_dir}/installer/src/usr/lib \;
 
	#--------------------------------------------------------------------------------------------------------#
	#-------------------------- copy linux-dependencies and binaries --------------------------#
	#--------------------------------------------------------------------------------------------------------#
	cp $(PWD)/../linux_dependencies/ocf-linux-20171122/ocf/ocf.ko ${build_dir}/installer/src/lib/modules/4.2.8/
	cp $(PWD)/../linux_dependencies/ocf-linux-20171122/ocf/cryptosoft.ko ${build_dir}/installer/src/lib/modules/4.2.8/
	cp $(PWD)/../linux_dependencies/ocf-linux-20171122/ocf/cryptodev.ko ${build_dir}/installer/src/lib/modules/4.2.8/
	cp $(PWD)/../linux_dependencies/libbsd/libbsd.so ${build_dir}/installer/src/usr/lib/
	cp $(PWD)/../linux_dependencies/libefi/libefi.so ${build_dir}/installer/src/usr/lib/
	cp $(PWD)/cddl/sbin/zfs/zfs ${build_dir}/installer/src/sbin
	cp $(PWD)/cddl/sbin/zpool/zpool ${build_dir}/installer/src/sbin

	cp $(PWD)/cddl/usr.bin/zfileclone/zfileclone ${build_dir}/installer/src/sbin
	cp $(PWD)/cddl/usr.bin/zfilecopy/zfilecopy ${build_dir}/installer/src/sbin
	cp $(PWD)/cddl/usr.bin/zinject/zinject ${build_dir}/installer/src/sbin
	cp $(PWD)/cddl/usr.sbin/zdb/zdb ${build_dir}/installer/src/sbin

	cp $(PWD)/cddl/contrib/opensolaris/cmd/zfs/zfs_linux.8 ${build_dir}/installer/src/usr/share/man/man8/zfs.8
	cp $(PWD)/cddl/contrib/opensolaris/cmd/zpool/zpool_linux.8 ${build_dir}/installer/src/usr/share/man/man8/zpool.8
	#-------------------------- copy scst binaries --------------------------#
	cp $(PWD)/../scst/app/cli/iscsiadm/main/iscsiadm ${build_dir}/installer/src/sbin
	cp $(PWD)/../scst/app/cli/scstadm/main/scstadm ${build_dir}/installer/src/sbin
	cp $(PWD)/../scst/app/cli/scsidevadm/main/scsidevadm ${build_dir}/installer/src/sbin
	cp $(PWD)/../scst/fed/iSCSI/login_app/iscsi-scstd ${build_dir}/installer/src/sbin
	#-------------------------- copy service file --------------------------#
	cp $(PWD)/../build/installer/iscsi-scstd ${build_dir}/installer/src/etc/init.d
	#--------------------------------------------------------------------------------------------------------#

	#--------------------------------------------------------------------------------------------------------#
	#-------------------------- Prepare to build package --------------------------#
	#--------------------------------------------------------------------------------------------------------#
	mkdir -p ${build_dir}/installer/${PKGNAME}/debian
	cp -R ${build_dir}/installer/debpackage/* ${build_dir}/installer/${PKGNAME}/debian/
 
	tar pczf ${build_dir}/installer/${PKGNAME}.tar.gz ${build_dir}/installer/src
	ln -s ${build_dir}/installer/${PKGNAME}.tar.gz ${build_dir}/installer/qnapzfs_${RELEASE_VERSION}.orig.tar.gz
 
	cp -R ${build_dir}/installer/src/* ${build_dir}/installer/${PKGNAME}/debian/
	sed -i 's/VERSION_TEMPLATE/${RELEASE_VERSION}/g' ${build_dir}/installer/${PKGNAME}/debian/changelog
 	
	#--------------------------------------------------------------------------------------------------------#
	#-------------------------- generating installer --------------------------#
	#--------------------------------------------------------------------------------------------------------#
	cd ${build_dir}/installer/${PKGNAME} && debuild -us -uc > /dev/null
 
	#--------------------------------------------------------------------------------------------------------#
	#-------------------------- clean workspace --------------------------#
	#--------------------------------------------------------------------------------------------------------#
	cd ${build_dir}/installer && rm -rf ${PKGNAME}* src && rm -rf *.build *.changes *.xz *.dsc *.gz
	mv ${build_dir}/installer/${BUILDPKG} $(PWD)




	
