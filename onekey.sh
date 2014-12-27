#!/bin/bash

EXE=./iec-runtime
OBJ=./plc.bin
NFSDIR=~/nfs
TESTDIR=./test/
GENOBJ=./translator.py

# Step1: rebuild iec-runtime
make rebuild
# Step2: generate obj file
${GENOBJ} < ${TESTDIR}"$1".test
# Step3: move iec-runtime & obj file to NFS directory
mv ${EXE} ${NFSDIR}
mv ${OBJ} ${NFSDIR}
