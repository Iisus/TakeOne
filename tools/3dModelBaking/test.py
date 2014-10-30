#!/usr/bin/env python
#-*- coding: UTF-8 -*-

"""
This module demonstrates the functionality of PyAssimp.
"""

import os
import logging
logging.basicConfig(level=logging.INFO)

import pyassimp
import pyassimp.postprocess
from array import array


def write_file(file_name, v_format, v_count, i_count, v_array, i_array):
    f = open(file_name, 'wb')
    l = array('I', v_format + [v_count, i_count])
    m = array('f', v_array)
    n = array('I', i_array)
    l.tofile(f)
    m.tofile(f)
    n.tofile(f)


def parse_mesh(file_name, mesh):

    v_count = len(mesh.vertices)

    v_format = []
    v_format += [1 if v_count > 0 else 0]
    v_format += [1 if len(mesh.normals) == v_count else 0]
    v_format += [1 if len(mesh.colors) == v_count else 0]
    v_format += [1 if len(mesh.texturecoords) == v_count else 0]

    vbo = []
    for index in range(0, v_count):
        vbo += mesh.vertices[index].tolist() if len(mesh.vertices) > index else [0, 0, 0]
        vbo += mesh.normals[index].tolist() if len(mesh.normals) > index else [0, 0, 0]
        vbo += mesh.colors[index].tolist() if len(mesh.colors) > index else [0, 0, 0]
        vbo += mesh.texturecoords[index].tolist() if len(mesh.texturecoords) > index else [0, 0]
    v_no = len(mesh.vertices.tolist())

    ibo = []
    for face in mesh.faces:
        ibo += face.tolist()
    i_no = len(ibo)

    write_file(file_name, v_format, v_no, i_no, vbo, ibo)


def main(filename=None):

    scene = pyassimp.load(filename, pyassimp.postprocess.aiProcess_Triangulate)

    file_name = os.path.splitext(os.path.basename(filename))[0] + ".t1o"
    for index, mesh in enumerate(scene.meshes):
        parse_mesh(str(index) + "_" + file_name, mesh)
   
    # Finally release the model
    pyassimp.release(scene)


def usage():
    print("Usage: sample.py <3d model>")

if __name__ == "__main__":

    #if len(sys.argv) != 2:
    #    usage()
    #else:
    #    main(sys.argv[1])
    main("models/OBJ/box.obj")
