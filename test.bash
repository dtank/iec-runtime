#!/bin/bash

EXE=./iec-runtime
OBJ=plc.bin
NFSDIR=~/nfs
GENOBJ=./generate_obj

# Step1: generate obj file
${GENOBJ} "$1"

# Step2: move executor & obj file to NFS directory
cp ${EXE} ${NFSDIR}
mv ${OBJ} ${NFSDIR}

