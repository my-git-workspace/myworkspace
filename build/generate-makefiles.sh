#!/bin/sh
#set -x
if [ ! $# -eq 1 ];then 
	echo "Usage:" 
	echo `basename $0`" <dir path>"
	echo "Here <dir path>=\"Dir from where want to generate Makefiles\""
	exit 0
fi
MAKE_FILES_PATH=`dirname $0`
generic_make_file_list=`find $1 -name Makefile.generic`
if [ ! $? -eq 0 ] || [ ! -n "${generic_make_file_list}" ];then
	echo "None Makefile.generic found."
	exit 0
fi
os_arch=`uname`  #Check current os 
platform=$os_arch
echo "Generating makefiles for *******$platform******* platform."
echo 
if  [ ${platform} = 'Linux' ];then
	MK_PATH='VPATH+='
	MK_CURDIR='$(PWD)'
	MK_INCLUDE_LINUX_COMMON_MK_FILE="include ${MK_CURDIR}\/RELATIVE_MAKE_FILES_PATH\/linux.common.mk"
	MK_INCLUDE_LIB_MK_FILE="${MK_INCLUDE_LINUX_COMMON_MK_FILE}\\\ninclude ${MK_CURDIR}\/RELATIVE_MAKE_FILES_PATH\/linux.lib.mk"
	MK_INCLUDE_SRC_OPTS_MK_FILE='#MK_INCLUDE_SRC_OPTS_MK_FILE'
	MK_ENDIF='endif'
	MK_INCLUDE_SUBDIR_MK_FILE="${MK_INCLUDE_LINUX_COMMON_MK_FILE}\\\ninclude ${MK_CURDIR}\/RELATIVE_MAKE_FILES_PATH\/linux.subdir.mk"
	MK_NOT_EQUAL_OPERATOR=","
	MK_SHELLCMD_NOT_EQUAL_OPERATOR='!='
	MK_IF_NOT_EQ='ifneq ('
	MK_IFNOTEQ_BRACKET_END=')'
	MK_IF_EQ='ifeq ( '
	MK_EXECUTE_SHEL_IF_CMD='$(shell if ['
	MK_END_OF_SQ_BRACKET=']'
	MK_START_OF_SQ_BRACKET='['
	MK_EQUAL_COND='='
	MK_SHELL_IF_CMD_END='];then echo true;else echo false;fi ), true)'
	MK_INCLUDE_KMOD_MK_FILE="${MK_INCLUDE_LINUX_COMMON_MK_FILE}\\\ninclude ${MK_CURDIR}\/RELATIVE_MAKE_FILES_PATH\/linux.kmod.mk"
	MK_KERNEL_EXTRA_CFLAGS='EXTRA_CFLAGS'
	MK_INCLUDE_PROG_MK_FILE="${MK_INCLUDE_LINUX_COMMON_MK_FILE}\\\ninclude ${MK_CURDIR}\/RELATIVE_MAKE_FILES_PATH\/linux.prog.mk"
	MK_ELSE='else'
	MK_ELIF_FILE_EXISTS='else ifeq ($(shell [ -f "'
	MK_IF_FILE_EXISTS='ifeq ($(shell [ -f "'	 
	MK_EOF_IF_FILE_EXISTS='" ] \&\& echo 1),1)' 
	MK_INCLUDEFILE='includeADDSPACE'
	MK_EOFINCLUDEFILE=''
	MK_IFEQUAL_LOGICAL_OPERATOR=','
	MK_IF_DEFINED='ifdef'
	MK_EOF_IF_DEFINED=''
	MK_INCLUDE_OBJ_MK_FILE='#MK_INCLUDE_OBJ_MK_FILE'
	MK_INCLUDE_PORT_PRE_MK_FILE='#MK_INCLUDE_PORT_PRE_MK_FILE'
	MK_ELIFEQ='else ifeq ('
	MK_FOR='#for need to define'
	MK_ENDFOR='#endfor need to define'
	MK_INCLUDE_BUILD_MK_FILE="include ${MK_CURDIR}\/RELATIVE_MAKE_FILES_PATH\/linux.build.mk"

elif [ ${platform} = 'FreeBSD' ]; then
	MK_PATH='.PATH:'
	MK_CURDIR='${.CURDIR}'
	MK_INCLUDE_LIB_MK_FILE='.include <bsd.lib.mk>'
	MK_INCLUDE_SRC_OPTS_MK_FILE='.include <src.opts.mk>'
	MK_ENDIF='.endif'
	MK_INCLUDE_SUBDIR_MK_FILE='.include <bsd.subdir.mk>'
	MK_NOT_EQUAL_OPERATOR="!="
	MK_SHELLCMD_NOT_EQUAL_OPERATOR='!='
	MK_IF_NOT_EQ='.if '
	MK_IFNOTEQ_BRACKET_END=''
	MK_IF_EQ='.if '
	MK_EXECUTE_SHEL_IF_CMD=''
	MK_END_OF_SQ_BRACKET=''
	MK_START_OF_SQ_BRACKET=''
	MK_EQUAL_COND='=='
	MK_SHELL_IF_CMD_END=''
	MK_INCLUDE_KMOD_MK_FILE='.include <bsd.kmod.mk>'
	MK_KERNEL_EXTRA_CFLAGS='CFLAGS'
	MK_INCLUDE_PROG_MK_FILE='.include <bsd.prog.mk>'
	MK_ELSE='.else'
	MK_ELIF_FILE_EXISTS='.elif exists('
	MK_IF_FILE_EXISTS='.if exists('
	MK_EOF_IF_FILE_EXISTS=')'
	MK_INCLUDEFILE='.include "'
	MK_EOFINCLUDEFILE='"'
	MK_IFEQUAL_LOGICAL_OPERATOR='=='
	MK_IF_DEFINED='.if defined('
	MK_EOF_IF_DEFINED=')'
	MK_INCLUDE_OBJ_MK_FILE='.include <bsd.obj.mk>'
	MK_INCLUDE_PORT_PRE_MK_FILE='.include <bsd.port.pre.mk>'
	MK_ELIFEQ='.elif'
	MK_FOR='.for'
	MK_ENDFOR='.endfor'
	MK_INCLUDE_BUILD_MK_FILE='#MK_INCLUDE_BUILD_MK_FILE'
else
	echo "Invalid platform."
	echo "Platform should be [ Linux | FreeBSD ]"	
	echo "for more details check uname."
	exit 0
fi

GENERIC_VARIABLES="MK_PATH MK_CURDIR MK_INCLUDE_LIB_MK_FILE MK_INCLUDE_SRC_OPTS_MK_FILE MK_IF_NOT_EQ MK_ENDIF MK_NOT_EQUAL_OPERATOR MK_INCLUDE_SUBDIR_MK_FILE MK_IF_EQ MK_IFNOTEQ_BRACKET_END MK_EXECUTE_SHEL_IF_CMD MK_END_OF_SQ_BRACKET MK_START_OF_SQ_BRACKET MK_EQUAL_COND MK_SHELL_IF_CMD_END MK_INCLUDE_KMOD_MK_FILE MK_KERNEL_EXTRA_CFLAGS MK_INCLUDE_PROG_MK_FILE MK_IF_DEFINED MK_EOF_IF_DEFINED MK_IF_FILE_EXISTS MK_EOF_IF_FILE_EXISTS MK_ELSE MK_ELIF_FILE_EXISTS MK_IF_FILE_EXISTS MK_EOF_IF_FILE_EXISTS MK_INCLUDEFILE MK_IFEQUAL_LOGICAL_OPERATOR MK_INCLUDE_OBJ_MK_FILE MK_INCLUDE_PORT_PRE_MK_FILE MK_ELIFEQ MK_ENDFOR MK_FOR MK_EOFINCLUDEFILE MK_SHELLCMD_NOT_EQUAL_OPERATOR MK_INCLUDE_BUILD_MK_FILE"

SED_PATTERN=''
FLAG=''
for gen_var in $GENERIC_VARIABLES;do
        if [ -z ${FLAG} ];then
                SED_PATTERN="s/${gen_var}/$(eval echo \$$gen_var)/g"
		FLAG="TRUE"
        else
                SED_PATTERN=$SED_PATTERN";s/${gen_var}/$(eval echo \$$gen_var)/g"
        fi
done

SUB_PATTERN=$SED_PATTERN

for gmake_file in $generic_make_file_list
do
	dir=`dirname $gmake_file`
	realpath=""
	if [ ${platform} = 'Linux' ];then
  		realpath=`realpath --relative-to=${dir} ${MAKE_FILES_PATH}`
	else
  		realpath=`realpath ${dir} ${MAKE_FILES_PATH} | head -1`
	fi
	sed  "$SUB_PATTERN" $gmake_file > $dir/Makefile.1
	sed  "s/RELATIVE_MAKE_FILES_PATH/$(echo $realpath | sed 's/\([[\./]\)/\\\1/g')/g" $dir/Makefile.1 > $dir/Makefile
	if [ $?  -gt 0 ];then
		echo "Error occurred"
	fi
	rm -f $dir/Makefile.1
	if [ ${platform} = 'Linux' ];then
		sed  -i "2 i\include \$\(PWD\)\/$(echo $realpath | sed 's/\([[\./]\)/\\\1/g')\/linux\.config\.mk" $dir/Makefile 
		#Add space
		sed -i 's/ADDSPACE/ /g' $dir/Makefile	
		sed -i 's/REMOVESINGLESPACE//g' $dir/Makefile #need to remove single space for linux for ifeq syntax
	fi
	if [ ${platform} = 'FreeBSD' ];then
	    sed   -i -e  's/REMOVESINGLESPACE/ /g' $dir/Makefile #need to add space for freebsd for ifeq syntax
	    find $dir -name 'Makefile-e' | xargs rm -f
	fi
	echo $dir "Makefile generated..."
done
