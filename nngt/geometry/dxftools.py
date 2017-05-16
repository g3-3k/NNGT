#!/usr/bin/env python
#-*- coding:utf-8 -*-

from xml.dom.minidom import parse
from itertools import chain
from dxf_import import DXF

import shapely
from shapely.affinity import scale
from shapely.geometry import Point, Polygon

import numpy as np

from nngt.geometry import Shape


'''
Shape generation from SVG files.
'''


__all__ = [
    "shapes_from_dxf",
    "culture_from_dxf",
]


# predefined svg shapes and their parameters
def shapes_from_dxf(filename, interpolate_curve=50, parent=None,
                    return_points=False):
    '''
    Generate :class:`shapely.geometry.Polygon` objects from an SVG file.
    '''
    ## The dirty job is don in dxf import submodule
    dxf = DXF(filename)
    shapes = dxf.shapes()
    return shapes


def culture_from_dxf(filename, min_x=-5000., max_x=5000., unit='um',
                     parent=None, interpolate_curve=50):
    '''
    Generate a culture from an SVG file.

    Valid file needs to contain only closed objects among:
    rectangles, circles, ellipses, polygons, and closed curves.
    The objects do not have to be simply connected.
    '''
    shapes, points = shapes_from_dxf(
        filename, parent=parent, interpolate_curve=interpolate_curve,
        return_points=True)
    idx_main_container = 0
    idx_local = 0
    type_main_container = ''
    count = 0
    min_x_val = np.inf

    # the main container must own the smallest x value
    for elt_type, elements in points.items():
        for i, elt_points in enumerate(elements):
            min_x_tmp = elt_points[:, 0].min()
            if min_x_tmp < min_x_val:
                min_x_val = min_x_tmp
                idx_main_container = count
                idx_local = i
                type_main_container = elt_type
            count += 1

    # make sure that the main container contains all other shapes
    main_container = shapes.pop(idx_main_container)
    exterior = points[type_main_container].pop(idx_local)
    for shape in shapes:
        assert main_container.contains(shape), "Some shapes are not " +\
            "contained in the main container."

    # all remaining shapes are considered as boundaries for the interior
    interiors = [item.coords for item in main_container.interiors]
    for _, elements in points.items():
        for elt_points in elements:
            interiors.append(elt_points)

    # scale the shape
    if None not in (min_x, max_x):
        exterior = np.array(main_container.exterior.coords)
        leftmost = np.min(exterior[:, 0])
        rightmost = np.max(exterior[:, 0])
        scaling = (max_x - min_x) / (rightmost - leftmost)
        exterior *= scaling
        interiors = [np.multiply(l, scaling) for l in interiors]

    culture = Shape(exterior, interiors, unit=unit, parent=parent)
    return culture


# ----- #
# Tools #
# ----- #


