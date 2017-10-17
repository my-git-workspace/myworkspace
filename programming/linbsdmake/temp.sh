
SUBDIR_M=(${_drti} 'libavl' 'libctf' ${_libdtrace} 'libnvpair' 'libumem' 'libuutil' ${_libzfs_core} ${_libzfs} ${_libzpool}) 

SUBDIR=(${_drti} \
        libavl \
        libctf \
        ${_libdtrace} \
        libnvpair \
        libumem \
        libuutil \
        ${_libzfs_core} \
        ${_libzfs} \
        ${_libzpool})


echo ${SUBDIR[@]}
for dir in ${SUBDIR[@]}
do 
	echo "---"$dir "---------"
done

