def convert_to_c_structure(data):
    lines = data.split('\n')
    width = max(len(line) for line in lines)

    c_structure = "t_block map[{}][{}] = {{\n".format(len(lines), width)
    for line in lines:
        row = ""
        for char in line:
            if char == '1':
                row += "WALL , "
            elif char == '0':
                row += "FLOOR, "
            elif char == 'E':
                row += "FLOOR  , "
            elif char == ' ':
                row += "EMPTY, "
        row += "END "
        c_structure += "\t\t{{ {} }},\n".format(row)
    c_structure += "};"
    return c_structure

data = '''
1111111111111111111111111111111111111111111111111111111111111111111111111
1E00000000000000000000000000000000000000000000000000000000000000000000001
1111111111111111111111111111111111111000000000000000000000000000000000001
                                    1000000000000000000000000000000000001
                                    1000000000000000000000000000000000001
                                    1000000000000000000000000000000000001
                                    1000000000000000000000000000000000001
      1111111111111111111111111111111000000000000000000000000000000000001
      1000000000000000000000000000000000000000000000000000000000000000001
      1000000000000000000000000000000000001111111111111111111111111111111
      1000000000000000000000000000000000001
      1000000000000000000000000000000000001
      1000000000000000000000000000000000001
      1000000000000000000000000000000000001
      1111011111111111100011111111111111111
         101          10001
         101          10001
    11111101          10001
    10000001          10001
    10111111    11111110001111111
    101         10000000000000001
    101         10000000000000001
    101         10010011111001001
    101         10010010001001001
    101         10010010001001001
    101         10010010001001001
    10111111111110010000001001001
    10000000000000010000001000001
    11111111111111111111111111111
'''

print(convert_to_c_structure(data))