#!/usr/bin/python
import sys;
import struct;

# OBJ File Format
objfile = {
        # OBJ Header
        'header_magic':   {'format': '5s', 'cast': str, 'is_macro': True},
        'header_type':    {'format': 'B', 'cast': int,  'is_macro': True},
        'header_order':   {'format': 'B', 'cast': int,  'is_macro': True},
        'header_version': {'format': 'B', 'cast': int,  'is_macro': False},
        'header_machine': {'format': 'B', 'cast': int,  'is_macro': True},
        # OBJ I/O Configuration Segment
        'iocs_update_interval': {'format': 'I', 'cast': int, 'is_macro': False},
        'iocs_ldi_count': {'format': 'B', 'cast': int, 'is_macro': False},
        'iocs_ldo_count': {'format': 'B', 'cast': int, 'is_macro': False},
        'iocs_lai_count': {'format': 'B', 'cast': int, 'is_macro': False},
        'iocs_lao_count': {'format': 'B', 'cast': int, 'is_macro': False},
        'iocs_rdi_count': {'format': 'B', 'cast': int, 'is_macro': False},
        'iocs_rdo_count': {'format': 'B', 'cast': int, 'is_macro': False},
        'iocs_rai_count': {'format': 'B', 'cast': int, 'is_macro': False},
        'iocs_rao_count': {'format': 'B', 'cast': int, 'is_macro': False},
        # OBJ Servo Configuration Segment
        'scs_axis_count':      {'format': 'B', 'cast': int, 'is_macro': False},
        'scs_update_interval': {'format': 'I', 'cast': int, 'is_macro': False},
        # OBJ Axis Configuration Segment
        'acs_name':     {'format': '16s', 'cast': str, 'is_macro': False},
        'acs_id':       {'format': 'B', 'cast': int, 'is_macro': False},
        'acs_type':     {'format': 'B', 'cast': int, 'is_macro': True},
        'acs_combined': {'format': 'B', 'cast': int, 'is_macro': True},
        'acs_opmode':   {'format': 'B', 'cast': int, 'is_macro': True},
        'acs_min_pos':  {'format': 'd', 'cast': float, 'is_macro': False},
        'acs_max_pos':  {'format': 'd', 'cast': float, 'is_macro': False},
        'acs_max_vel':  {'format': 'd', 'cast': float, 'is_macro': False},
        'acs_max_acc':  {'format': 'd', 'cast': float, 'is_macro': False},
        'acs_max_dec':  {'format': 'd', 'cast': float, 'is_macro': False},
        'acs_max_jerk': {'format': 'd', 'cast': float, 'is_macro': False},
        # OBJ PLC Task List Segment
        'plc_task_count':   {'format': 'B', 'cast': int, 'is_macro': False},
        # OBJ PLC Task Description Segment
        'tds_name':         {'format': '16s', 'cast': str, 'is_macro': False},
        'tds_priority':     {'format': 'B', 'cast': int, 'is_macro': False},
        'tds_type':         {'format': 'B', 'cast': int, 'is_macro': True},
        'tds_signal':       {'format': 'B', 'cast': int, 'is_macro': False},
        'tds_interval':     {'format': 'I', 'cast': int, 'is_macro': False},
        'tds_sp_size':      {'format': 'I', 'cast': int, 'is_macro': False},
        'tds_cs_size':      {'format': 'H', 'cast': int, 'is_macro': False},
        'tds_pou_count':    {'format': 'H', 'cast': int, 'is_macro': False},
        'tds_const_count':  {'format': 'H', 'cast': int, 'is_macro': False},
        'tds_global_count': {'format': 'H', 'cast': int, 'is_macro': False},
        'tds_inst_count':   {'format': 'I', 'cast': int, 'is_macro': False},
        # OBJ PLC Task User-level POU Description Segment
        'pds_name':         {'format': '20s', 'cast': str, 'is_macro': False},
        'pds_input_count':  {'format': 'B', 'cast': int, 'is_macro': False},
        'pds_inout_count':  {'format': 'B', 'cast': int, 'is_macro': False},
        'pds_output_count': {'format': 'B', 'cast': int, 'is_macro': False},
        'pds_local_count':  {'format': 'B', 'cast': int, 'is_macro': False},
        'pds_entry':        {'format': 'I', 'cast': int, 'is_macro': False},
}
# Macros defined in iec-runtime
objmacro = { # MUST be equal to iec-runtime
        # OBJ Header
        'MAGIC': "\x7fPLC\0",
        'SYS_TYPE_32': 1,
        'SYS_TYPE_64': 2,
        'BYTE_ORDER_LIT': 1,
        'BYTE_ORDER_BIT': 2,
        'MACH_CORTEX_A8': 1,
        # OBJ Servo Configuration Segment
        'AXIS_TYPE_FINITE': 1,
        'AXIS_TYPE_MODULO': 2,
        'AXIS_INDEPENDENT': 1,
        'AXIS_COMBINED': 2,
        'OPMODE_POS': 1,
        'OPMODE_VEL': 2,
        'OPMODE_TOR': 3,
        # OBJ PLC Task Segment
        'TASK_TYPE_SIGNAL': 1,
        'TASK_TYPE_INTERVAL': 2,
        # OBJ PLC Task Constant/Global Value Type
        'TINT': 1,
        'TUINT': 2,
        'TDOUBLE': 3,
        'TSTRING': 4,
        # System-level POU
        'SFUN_ABS':  0,
        'SFUN_SQRT': 1,
        'SFUN_MOD': 2,
        'SFUN_EXPT': 3,
}

# VM Instruction Encoding (MUST be equal to iec-runtime)
SIZE_OP  = 8
SIZE_A   = 8
SIZE_B   = 8
SIZE_C   = 8
SIZE_Bx  = (SIZE_B+SIZE_C)
SIZE_sAx = (SIZE_A+SIZE_B+SIZE_C)

POS_C   = 0
POS_B   = (POS_C+SIZE_C)
POS_A   = (POS_B+SIZE_B)
POS_OP  = (POS_A+SIZE_A)
POS_Bx  = POS_C
POS_sAx = POS_C

BIAS_sAx = (1<<(SIZE_sAx-1))

# Original Instruction Encoder
def create_ABC(operand):
    return opcode[operand[1]]['id'] << POS_OP \
            | int(operand[2]) << POS_A \
            | int(operand[3]) << POS_B \
            | int(operand[4]) << POS_C;

def create_ABx(operand):
    return opcode[operand[1]]['id'] << POS_OP \
            | int(operand[2]) << POS_A \
            | int(operand[3]) << POS_Bx

def create_sAx(operand):
    return opcode[operand[1]]['id'] << POS_OP \
            | int(operand[2])+BIAS_sAx << POS_sAx

# Helper Instruction Encoder
def create_DX(operand):
    new_operand = operand;
    new_operand[3] = int(operand[3]) * 8 + int(operand[4]);
    new_operand[4] = 1;
    return create_ABC(new_operand);

def create_DB(operand):
    new_operand = operand;
    new_operand[3] = int(operand[3]) * 8;
    new_operand[4] = 8;
    return create_ABC(new_operand);

def create_DW(operand):
    new_operand = operand;
    new_operand[3] = int(operand[3]) * 16;
    new_operand[4] = 16;
    return create_ABC(new_operand);

def create_DD(operand):
    new_operand = operand;
    new_operand[3] = int(operand[3]) * 32;
    new_operand[4] = 32;
    return create_ABC(new_operand);

def create_scall(operand):
    new_operand = operand;
    new_operand[3] = objmacro[operand[3]];
    return create_ABx(new_operand);

opcode = {
        # data move
        'OP_GLOAD':  {'id': 1, 'creator': create_ABx},
        'OP_GSTORE': {'id': 2, 'creator': create_ABx},
        'OP_KLOAD':  {'id': 3, 'creator': create_ABx},
        'OP_DLOAD':  {'id': 4, 'creator': create_ABC},
        'OP_DSTORE': {'id': 5, 'creator': create_ABC},
        'OP_ALOAD':  {'id': 6, 'creator': create_ABC},
        'OP_ASTORE': {'id': 7, 'creator': create_ABC},
        'OP_MOV':    {'id': 8, 'creator': create_ABC},
        # arithmetic
        'OP_ADD': {'id': 9, 'creator': create_ABC},
        'OP_SUB': {'id': 10, 'creator': create_ABC},
        'OP_MUL': {'id': 11, 'creator': create_ABC},
        'OP_DIV': {'id': 12, 'creator': create_ABC},
        # bit operation
        'OP_SHL': {'id': 13, 'creator': create_ABC},
        'OP_SHR': {'id': 14, 'creator': create_ABC},
        'OP_AND': {'id': 15, 'creator': create_ABC},
        'OP_OR':  {'id': 16, 'creator': create_ABC},
        'OP_XOR': {'id': 17, 'creator': create_ABC},
        'OP_NOT': {'id': 18, 'creator': create_ABC},
        # logic operation
        'OP_LAND': {'id': 19, 'creator': create_ABC},
        'OP_LOR':  {'id': 20, 'creator': create_ABC},
        'OP_LXOR': {'id': 21, 'creator': create_ABC},
        'OP_LNOT': {'id': 22, 'creator': create_ABC},
        # comparison
        'OP_LT':  {'id': 23, 'creator': create_ABC},
        'OP_LE':  {'id': 24, 'creator': create_ABC},
        'OP_GT':  {'id': 25, 'creator': create_ABC},
        'OP_GE':  {'id': 26, 'creator': create_ABC},
        'OP_EQ':  {'id': 27, 'creator': create_ABC},
        'OP_NE':  {'id': 28, 'creator': create_ABC},
        # flow control
        'OP_EQJ':  {'id': 29, 'creator': create_ABC},
        'OP_LTJ':  {'id': 30, 'creator': create_ABC},
        'OP_LEJ':  {'id': 31, 'creator': create_ABC},
        'OP_JMP':  {'id': 32, 'creator': create_sAx},
        'OP_HALT': {'id': 33, 'creator': create_ABC},
        # call
        'OP_SCALL': {'id': 34, 'creator': create_scall},
        'OP_UCALL': {'id': 35, 'creator': create_ABx},
        'OP_RET':   {'id': 36, 'creator': create_ABx},
        # helper
        'OP_DIX':   {'id': 4, 'creator': create_DX},
        'OP_DIB':   {'id': 4, 'creator': create_DB},
        'OP_DIW':   {'id': 4, 'creator': create_DW},
        'OP_DID':   {'id': 4, 'creator': create_DD},
        'OP_DOX':   {'id': 5, 'creator': create_DX},
        'OP_DOB':   {'id': 5, 'creator': create_DB},
        'OP_DOW':   {'id': 5, 'creator': create_DW},
        'OP_DOD':   {'id': 5, 'creator': create_DD},
}

def dump_inst(obj, words):
    obj.write(struct.pack('I', opcode[words[1]]['creator'](words)));

def dump_value(obj, words):
    obj.write(struct.pack('B', objmacro[words[1]]));
    if words[1] == 'TINT':
        obj.write(struct.pack('q', int(words[2]))); # int64_t
    if words[1] == 'TUINT':
        obj.write(struct.pack('Q', int(words[2]))); # uint64_t
    if words[1] == 'TDOUBLE':
        obj.write(struct.pack('d', float(words[2])));
    if words[1] == 'TSTRING':
        length = len(words[2]) + 1;
        obj.write(struct.pack('I', length));
        obj.write(struct.pack(str(length) + 's', words[2]));

def dump_obj(obj, words):
    if words[0] == 'K' or words[0] == 'G':
        dump_value(obj, words);
    elif words[0] == 'I':
        dump_inst(obj, words);
    else :
        field = objfile[words[0]];
        if field['is_macro']:
            value = objmacro[words[1]];
        else :
            value = field['cast'](words[1]);
        obj.write(struct.pack(field['format'], value));

# translator
obj = open('./plc.bin', 'wb');
for line in sys.stdin:
    words = line.strip('\n').split();
    if words and (words[0] != '#'):
        dump_obj(obj, words);
