# GDB commands to parse the debug informations of an ELF executable
set pagination off

python

# Convert a gdb.Type to a Octave/Matlab's fread precision
def mtype(gdbtype):
    if   gdbtype.code == gdb.TYPE_CODE_FLT:
        return "1, 'float" + str(8*gdbtype.sizeof) + "'"
    elif gdbtype.code == gdb.TYPE_CODE_INT:
        return "1, 'int" + str(8*gdbtype.sizeof) + "'"
    elif gdbtype.code == gdb.TYPE_CODE_ARRAY:
        return str(gdbtype.range()[1]-gdbtype.range()[0]+1) + ", 'float64'"
    return "none"

# Generate Octave/Matlab statements to read a C-struct gdbtype
def print_struct (gdbtype):
    print(str(gdbtype))
    if gdbtype.code != gdb.TYPE_CODE_STRUCT : 
        raise gdb.GdbError (str(gdbtype) + "is not a struct")
    name = gdbtype.unqualified().strip_typedefs().tag
    file = open('sread_' + name + '.m', 'w')
    file.write('function [s] = sread_' + name + '(fid)\n')
    for f in gdbtype.fields():
        file.write('  s.' + f.name + ' = fread(fid, ' + mtype(f.type) + ');\n')
    file.write('end\n')
    file.close()

for t in ['struct unused', 'nonexistent', 'struct internal']:
    try:
        print_struct(gdb.lookup_type(t))
    except Exception as e:
        print("ERROR: \"" + str(e) + "\"")
        pass

# End of embedded python source
end

quit
