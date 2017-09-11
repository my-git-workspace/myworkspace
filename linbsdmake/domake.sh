#!/bin/bash
#set -x
COMMON_MAKE_DIR='\/opt\/myworkspace\/qnap\.git\/zfs\-build'
if [ $# -lt 2 ];then 
	echo "$0 <platform> <dir path>"
	exit 0
fi
platform=$1
generic_make_files=`find $2 -name Makefile.generic`
#generic_make_files='Makefile.generic'
if [ ${platform} == 'linux' ];then
	MK_PATH='VPATH+='
	MK_CURDIR='$(shell pwd)'
	MK_INCLUDE_LIB_MK_FILE="include ${COMMON_MAKE_DIR}\/linux.lib.mk"
	MK_INCLUDE_SRC_OPTS_MK_FILE=''
	MK_ENDIF='endif'
	MK_INCLUDE_SUBDIR_MK_FILE="include ${COMMON_MAKE_DIR}\/linux.subdir.mk"
	MK_NOT_EQUAL_OPERATOR=","
	MK_IF_NOT_EQ='ifneq ('
	MK_IFNOTEQ_BRACKET_END=')'
	MK_IF_EQ='ifeq ( '
	MK_EXECUTE_SHEL_IF_CMD='$(shell if ['
	MK_END_OF_SQ_BRACKET=']'
	MK_START_OF_SQ_BRACKET='['
	MK_EQUAL_COND='='
	MK_SHELL_IF_CMD_END='];then echo true;else echo false;fi ), true)'
fi

if [ ${platform} == 'bsd' ];then
	MK_PATH='.PATH:'
	MK_CURDIR='${.CURDIR}'
	MK_INCLUDE_LIB_MK_FILE='.include <bsd.lib.mk>'
	MK_INCLUDE_SRC_OPTS_MK_FILE='.include <src.opts.mk>'
	MK_ENDIF='.endif'
	MK_INCLUDE_SUBDIR_MK_FILE='.include <bsd.subdir.mk>'
	MK_NOT_EQUAL_OPERATOR="!="
	MK_IF_NOT_EQ='.if '
	MK_IFNOTEQ_BRACKET_END=''
	MK_IF_EQ='.if '
	MK_EXECUTE_SHEL_IF_CMD=''
	MK_END_OF_SQ_BRACKET=''
	MK_START_OF_SQ_BRACKET=''
	MK_EQUAL_COND='=='
	MK_SHELL_IF_CMD_END=''
fi


SUB_PATTERN="s/MK_PATH/${MK_PATH}/g;s/MK_CURDIR/${MK_CURDIR}/g;s/MK_INCLUDE_LIB_MK_FILE/${MK_INCLUDE_LIB_MK_FILE}/g;s/MK_INCLUDE_SRC_OPTS_MK_FILE/${MK_INCLUDE_SRC_OPTS_MK_FILE}/g;s/MK_ENDIF/${MK_ENDIF}/g;s/MK_INCLUDE_SUBDIR_MK_FILE/${MK_INCLUDE_SUBDIR_MK_FILE}/g"

IFEQ_LOGICAL_OR_PATTERN="s/MK_IF_EQ/${MK_IF_EQ}/g;s/MK_EXECUTE_SHEL_IF_CMD/${MK_EXECUTE_SHEL_IF_CMD}/g;s/MK_END_OF_SQ_BRACKET/${MK_END_OF_SQ_BRACKET}/g;s/MK_START_OF_SQ_BRACKET/${MK_START_OF_SQ_BRACKET}/g;s/MK_EQUAL_COND/${MK_EQUAL_COND}/g;s/MK_SHELL_IF_CMD_END/${MK_SHELL_IF_CMD_END}/g"	

IFNEQ_PATTERN="s/MK_NOT_EQUAL_OPERATOR/${MK_NOT_EQUAL_OPERATOR}/g;s/MK_IF_NOT_EQ/${MK_IF_NOT_EQ}/g;s/MK_IFNOTEQ_BRACKET_END/${MK_IFNOTEQ_BRACKET_END}/g"

SUB_PATTERN=$SUB_PATTERN";"$IFNEQ_PATTERN
SUB_PATTERN=$SUB_PATTERN";"$IFEQ_LOGICAL_OR_PATTERN

for gmake in $generic_make_files
do
	dir=`dirname $gmake`
	echo $gmake
	#echo $dir
	sed  "$SUB_PATTERN" $gmake 
	#sed  "$SUB_PATTERN" $gmake > $dir/Makefile
done

#sed  "s/MK_PATH/${MK_PATH}/g;s/MK_CURDIR/${MK_CURDIR}/g;s/MK_INCLUDE_LIB_MAKE_FILE/${MK_INCLUDE_LIB_MAKE_FILE}/g" Makefile.generic 
