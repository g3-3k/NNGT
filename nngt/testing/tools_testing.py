#!/usr/bin/env python
#-*- coding:utf-8 -*-

# base_test.py

# This file is part of the NNGT module
# Distributed as a free software, in the hope that it will be useful, under the
# terms of the GNU General Public License.

import xml.etree.ElementTree as xmlet
import unittest
import nngt

#-----------------------------------------------------------------------------#
# Xml tools
#------------------------
#   

def _bool_from_string(string):
    return True if (string.lower() == "true") else False


def _list_from_string(string, elt_type, di_convert):
    lst = string[1:-1].split(", ")
    return [ di_convert[elt_type](elt) for elt in lst ]


def _xml_to_dict(xml_elt, di_types):
    di_result = {}
    for child in xml_elt:
        str_type = child.tag
        if len(child):
            name = str_type
            elt = child.find("start")
            if elt is not None:
                start = di_types[str_type](child.find("start").text)
                stop = di_types[str_type](child.find("stop").text)
                step = di_types[str_type](child.find("step").text)
                di_result[name] = np.arange(start,stop,step)
            else:
                di_result[child.tag] = _xml_to_dict(child, di_types)
        else:
            name = child.attrib["name"]
            if child.tag in ("string", "str"):
                text = child.text.replace("\\t","\t")
                di_result[name] = di_types[str_type](text)
            elif child.tag == "list":
                elt_type = child.attrib["type"]
                di_result[name] = _list_from_string( child.text,
                                                     elt_type, di_types )
            else:
                di_result[name] = di_types[str_type](child.text)
    return di_result


#-----------------------------------------------------------------------------#
# Decorator: repeat test for each graph
#------------------------
#

def foreach_graph(func):
    '''
    Decorator that automatically does the test for all graph instructions
    provided in the argument.
    '''
    def wrapper(*args, **kwargs):
        self = args[0]
        nx = nngt.get_config("graph_library") == "networkx"
        for graph_name in self.graphs:
            if nx and "corr" in graph_name:
                print("Skipping correlated attributes with networkx")
            else:
                g, di = self.gen_graph(graph_name)
                func(self, g, instructions=di, **kwargs)
    return wrapper
