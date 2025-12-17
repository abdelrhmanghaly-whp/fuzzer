import struct
import os

def create_seed(filename, n, edges, source=0):
    with open(filename, 'wb') as f:
        f.write(struct.pack('<i', n))  # 4 byte: number of nodes
        f.write(struct.pack('<i', len(edges)))  # 4 bytes: number of edges
        for u, v, w in edges:
            f.write(struct.pack('<i', u))  # 4 bytes: from
            f.write(struct.pack('<i', v))  # 4 bytes: to
            f.write(struct.pack('<i', w))  # 4 bytes: w
        f.write(struct.pack('i', source))  # 4 byte: src node

os.makedirs('corpora/seeds', exist_ok=True)
create_seed('corpora/seeds/seed1.bin', 3, [(0,1,10), (1,2,20), (0,2,50)]) # triangle 3ady
create_seed('corpora/seeds/seed2.bin', 4, [(0,1,5), (1,2,-3), (2,3,2)]) # neg weights
create_seed('corpora/seeds/seed3.bin', 5, [(0,1,1), (3,4,1)]) # disconnected type
print("done")