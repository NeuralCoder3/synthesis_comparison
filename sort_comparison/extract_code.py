import sys

# python extract_code.py out/clang.debug.make/test_correct.cpp.s | xclip -sel clip

time_file = sys.argv[1]

with open(time_file, 'r') as f:
    lines = f.readlines()
    
# extract lines between sort3_[...]: and retq

functions = []
function = []
inFunction = False
for line in lines:
    if line.strip().startswith("sort3_"):
        if inFunction:
            print("Still in function "+function[0].strip()+", but found new function "+line.strip())
        assert not inFunction
        function = []
        inFunction = True
    if inFunction:
        function.append(line)
    if (line.strip().startswith("ret") or line.strip().startswith(".cfi_endproc")) and inFunction:
        inFunction = False
        if function:
            functions.append(function)
        
loc_map = {}
names = [
    'sort3_alphadev', 
    
    'sort3_cassioneri_14', 
    'sort3_cassioneri_15', 
    'sort3_cassioneri_15_v2', 
    'sort3_cassioneri_faster', 
    
    'sort3_default', 
    'sort3_default_size', 
    'sort3_std', 
    'sort3_branchless', 
    'sort3_branchless_size', 
    'sort3_swap', 
    'sort3_swap_inline',
    
    'sort3_mimicry_ms', 
    'sort3_mimicry_mv', 
    'sort3_mimicry_std', 
]
names = [
    'sort3_rust_std',
    'sort3_rust_swap_inline_annotated',
    'sort3_rust_swap_inline_raw',
    'sort3_rust_branchless_min_annotated', 
    'sort3_rust_branchless_annotated',
]
for f in functions:
    name = f[0].strip().split()[0].strip(":")
    lines = [line.strip() for line in f[1:]]
    lines = [line for line in lines if line]
    lines = [line for line in lines if not line.startswith(".")]
    lines = [line for line in lines if not line.startswith("#")]
    lines = [line for line in lines if line[-1] != ":"]
    lines = [line for line in lines if line!="nop"]
    loc_map[name] = len(lines)

print("\t".join([str(loc_map[name]) for name in names]))