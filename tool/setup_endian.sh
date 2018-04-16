#/bin/bash
SCP_DIR=$(cd $(dirname $0);pwd);
CNV_BASE="#define __PIA_BYTEORDER__ "
CNV_DST_TXT=""


error () {
    echo "ERROR : $1"
    echo "script is failed"
    exit -1
}

if [[ "" == $1 ]] || [ "LITTLE" == $1 ]; then
    # Little Endian
    CNV_DST_TXT=${CNV_BASE}"PIA_BYOR_LITED"
elif [ "BIG" == $1 ]; then
    # Big Endian
    CNV_DST_TXT=${CNV_BASE}"PIA_BYOR_BIGED"
else
    error "unknown endian(please specify 'LITTLE' or 'BIG')"
fi

CNV_SRC_TXT=${CNV_BASE}"PIA_BYOR_LITED"
GRPCHK=$(grep -l "${CNV_SRC_TXT}" $SCP_DIR/../hdr/pia/com.h)
if [[ "" == $GRPCHK ]]; then
    CNV_SRC_TXT=${CNV_BASE}"PIA_BYOR_BIGED"
    GRPCHK=$(grep -l "${CNV_SRC_TXT}" $SCP_DIR/../hdr/pia/com.h)
    if [[ "" == $GRPCHK ]]; then
        error "replace string was failed"
    fi
fi

grep -l "${CNV_SRC_TXT}" $SCP_DIR/../hdr/pia/com.h | xargs sed -i.bak -e "s/${CNV_SRC_TXT}/${CNV_DST_TXT}/g"
if [ $? != 0 ]; then
    error "replace string was failed"
fi
sudo rm $SCP_DIR/../hdr/pia/com.h.bak

