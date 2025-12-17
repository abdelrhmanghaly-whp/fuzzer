import struct
import os
from pathlib import Path

def get(filename):
    with open(filename, 'rb') as f:
        data=f.read()

    res = []
    res.append(f"File:{os.path.basename(filename)}")

    try:
        id=0
        n=struct.unpack('<i',data[id:id+4])[0]
        id+=4
        m=struct.unpack('<i',data[id:id+4])[0]
        id+=4
        for i in range(m):
            if id+12>len(data):
                break
            u=struct.unpack('<i',data[id:id+4])[0]; id+=4
            v=struct.unpack('<i',data[id:id+4])[0]; id+=4
            w=struct.unpack('<i',data[id:id+4])[0]; id+=4
            res.append(f"{u}->{v}:weight={w}")

        if id+4 <=len(data):
            src = struct.unpack('<i',data[id:id+4])[0]
            res.append(f"\nSource:{src}")
    except:
        res.append("Err")

    return "\n".join(res)


def execute():
    crash_dir=Path("findings/default/crashes")
    output_dir=Path("analysis")
    output_dir.mkdir(exist_ok=True)

    files=[f for f in crash_dir.iterdir() if f.is_file() and f.name.startswith("id:")]
    combined=[]
    for crash in sorted(files):
        decoded = get(crash)
        output_file = output_dir/f"{crash.name}.txt"
        with open(output_file, 'w') as f:
            f.write(decoded)

        combined.append(decoded)
        combined.append("\n"+"-"*50+"\n")

    with open(output_dir/"All_Crashes.txt", 'w') as f:
        f.write("\n".join(combined))
    print(f"Saved {len(files)}")

execute()

