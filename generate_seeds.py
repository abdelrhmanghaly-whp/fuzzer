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
        f.write(struct.pack('<i', source))  # 4 byte: src node

os.makedirs('corpora/seeds', exist_ok=True)
create_seed('corpora/seeds/seed1.bin', 3, [(0,1,10), (1,2,20), (0,2,50)]) # triangle 3ady
create_seed('corpora/seeds/seed2.bin', 4, [(0,1,5), (1,2,-3), (2,3,2)]) # neg weights
create_seed('corpora/seeds/seed3.bin', 5, [(0,1,1), (3,4,1)]) # disconnected type

create_seed('corpora/seeds/seed4.bin', 1, []) # single node
create_seed('corpora/seeds/seed5.bin', 2, [(0,0,5)]) # self looped
create_seed('corpora/seeds/seed6.bin', 4, [(0,1,-100000),(1,2,100000)]) # wa7da kbera

# chains, multiple paths, negative cycles w shwyt weight trigger
graph = [(i,j,i*10+j) for i in range(5) for j in range(5) if i!=j]
create_seed('corpora/seeds/seed7.bin', 10, graph)
create_seed('corpora/seeds/seed8.bin', 3, [(0,1,-5),(1,2,-5),(2,0,-5)])
create_seed('corpora/seeds/seed9.bin', 10, [(i, i+1, i) for i in range(9)]) # chained
create_seed('corpora/seeds/seed10.bin', 3, [(0,1,2000000000),(1,2,1)])

print("done")