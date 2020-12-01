#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os

def gen_edge(file, file_path, now_name):
    all_file = os.listdir(file_path)
    for f in all_file:
        if f.find('.git') != -1:
            continue
        if os.path.isdir( os.path.join(file_path, f) ):
            file.write('\t' + now_name + ' --> ' + f + '\n')
            gen_edge(file, os.path.join(file_path, f), f)

def do():
    f = open('AlgorithmGraph.md', 'w')
    if f:
        f.write( "```mermaid\n\tgraph LR;\n" )
        gen_edge(f, ".", "Algorithm")
        f.write( "```\n" )

do()
