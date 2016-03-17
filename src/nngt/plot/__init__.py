#!/usr/bin/env python
#-*- coding:utf-8 -*-

"""
Functions for plotting graphs and graph properties.

note ::
    For now, graph plotting is only supported when using the
    `graph_tool <https://graph-tool.skewed.de>`_ library.

Content
=======
"""

import sys
import matplotlib
try:
    matplotlib.use('Qt5Agg')
except:
    try:
        matplotlib.use('Qt4Agg')
    except:
        try:
            matplotlib.use('GTK3Agg')
        except:
            pass
import warnings
warnings.filterwarnings("ignore", module="matplotlib")

from nngt.globals import glib_data


# module import

from .custom_plt import palette
from .plt_properties import degree_distribution, betweenness_distribution
from .plt_activity import spike_raster

__all__ = [ "degree_distribution", "betweenness_distribution", 'spike_raster' ]

if glib_data["name"] == 'graph_tool':
    from .plt_networks import draw_network
    __all__.append("draw_network")
else:
    warnings.warn("Graph drawing is only available with graph_tool at the \
moment. As {} is currently being used, all graph drawing functions will be \
disabled.".format(glib_data["name"]))
