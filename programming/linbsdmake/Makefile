# $FreeBSD: stable/9/cddl/lib/Makefile 249643 2013-04-19 09:19:10Z mm $


#MK_INCLUDE_SRC_OPTS_MK_FILE

source "domake.sh"

DO_MK_INCLUDE_SRC_OPTS_MK_FILE()

SUBDIR=	${_drti} \
	libavl \
	libctf \
	${_libdtrace} \
	libnvpair \
	libumem \
	libuutil \
	${_libzfs_core} \
	${_libzfs} \
	${_libzpool}

MK_IF_NOT_EQ ${MK_ZFS} MK_NOT_EQUAL_OPERATOR "no" MK_IFNOTEQ_BRACKET_END 
_libzfs_core=	libzfs_core
_libzfs=	libzfs
MK_IF_NOT_EQ ${MK_LIBTHR} MK_NOT_EQUAL_OPERATOR "no" MK_IFNOTEQ_BRACKET_END
_libzpool=	libzpool
MK_ENDIF
MK_ENDIF

MK_IF_EQ MK_EXECUTE_SHEL_IF_CMD ${MACHINE_ARCH} MK_EQUAL_COND "amd64" MK_END_OF_SQ_BRACKET || MK_START_OF_SQ_BRACKET ${MACHINE_ARCH} MK_EQUAL_COND "i386" MK_SHELL_IF_CMD_END
_drti=          drti
_libdtrace=     libdtrace
MK_ENDIF

DO_SUBDIR_MAKE ${SUBDIR}
