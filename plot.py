import networkx as nx
import matplotlib.pyplot as plt
import sys

def parse_rna_file(fileobj):
    lines = [line.strip() for line in fileobj if line.strip()]
    
    structures = []
    i = 0
    while i < len(lines):
        sequence = lines[i]
        i += 1
        pairs = []
        while i < len(lines) and ' ' in lines[i] and lines[i].replace(' ', '').isdigit():
            a, b = map(int, lines[i].split())
            pairs.append((a, b))
            i += 1
        score = float(lines[i])
        i += 1
        structures.append((sequence, pairs, score))
    
    return structures

def plot_rna_graph(sequence, pairs, score, ax=None):
    G = nx.Graph()
    n = len(sequence)

    for i, base in enumerate(sequence):
        G.add_node(i, label=f"{base}")

    for i in range(n - 1):
        G.add_edge(i, i+1, type='backbone')

    for i, j in pairs:
        G.add_edge(i, j, type='pair')

    pos = nx.kamada_kawai_layout(G)

    labels = nx.get_node_attributes(G, 'label')
    nx.draw_networkx_nodes(G, pos, node_color='lightblue', ax=ax)
    nx.draw_networkx_labels(G, pos, labels=labels, font_size=10, ax=ax)

    backbone_edges = [(u, v) for u, v, d in G.edges(data=True) if d['type'] == 'backbone']
    pair_edges = [(u, v) for u, v, d in G.edges(data=True) if d['type'] == 'pair']

    nx.draw_networkx_edges(G, pos, edgelist=backbone_edges, edge_color='gray', style='solid', ax=ax)
    nx.draw_networkx_edges(G, pos, edgelist=pair_edges, edge_color='red', style='dashed', width=2, ax=ax)

    if ax:
        ax.set_title(f"Score: {score}")
        ax.axis('off')

rna_structures = parse_rna_file(sys.stdin)

fig, axes = plt.subplots(len(rna_structures), 1, figsize=(6, len(rna_structures)*3))

if len(rna_structures) == 1:
    axes = [axes]

for ax, (seq, pairs, score) in zip(axes, rna_structures):
    plot_rna_graph(seq, pairs, score, ax)

plt.tight_layout()
plt.show()
