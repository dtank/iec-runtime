#!/bin/bash

EXE=./bin/iec-runtime
OBJ=plc.bin
NFSDIR=~/nfs

./bin/generate_obj arithmetic
cp ${EXE} ${NFSDIR}
mv ${OBJ} ${NFSDIR}

