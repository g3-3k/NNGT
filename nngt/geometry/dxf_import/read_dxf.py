#!/usr/bin/python
# -*- coding: utf-8 -*-
'''
Read dxf graphic file of growth region boundaries

:requires: `dxfgrabber <http://pypi.python.org/pypi/dxfgrabber/>`

Input
=====
link path to dxf 2D graphic file to read

Output
======
Shapes in as shapely objects.

Lists DX and DY of  x and y homcoord.nates of vectors to draw the graph
i.e. for a square defined by extermities :
top_left:  (x_tl,y_tl)
top_right: (x_tr,y_tr)
bottom_left: (x_bl,y_bl)
bottom_right: (x_br,y_br)
DX= [[x_tl,x_tlr],[x_tr,x_br],[x_br,x_bl],[x_bl,x_tl]]
DY= [[y_tl,y_tlr],[y_tr,y_br],[y_br,y_bl],[y_bl,y_tl]]

'''

__author__ = "Samuel Bottani"
__copyright__ = "Copyright 2015, PSamuel Bottani"
__credits__ = ['http://pydoc.net/Python/Goulib/1.5.0/Goulib.dxf2img/']
__license__ = "LGPL"


def rint(x):return int(round(x))

# - - - - -   I m p o r t s
import dxfgrabber
import numpy as np
import homcoord
import itertools
import operator
import Image, ImageDraw, ImageFont #PIL
from shapely.wkt import loads
from shapely.geometry import Polygon as shapelyPolygon
from shapely.geometry import Point as shapelyPoint
import matplotlib.pyplot as plt
import logging
# from plot_shapely import Plot_shapely




class BBox:
    """bounding box"""
    __author__ = "Philippe Guglielmetti"
    __copyright__ = "Copyright 2013, Philippe Guglielmetti"
    __credits__ = ['http://effbot.org/imagingbook/imagedraw.htm']
    __license__ = "LGPL"

    def __init__(self,pt1=None,pt2=None):
        self._corner1=None
        self._corner2=None
        if pt1: self+=pt1
        if pt2: self+=pt2

    def __iadd__(self,pt):
        if isinstance(pt,BBox):
            self+=pt._corner1
            self+=pt._corner2
        else:
            if not self._corner1:
                self._corner1=pt
            else:
                self._corner1=homcoord.Pt(map(min,zip(self._corner1.xy,pt.xy)))
            if not self._corner2:
                self._corner2=pt
            else:
                self._corner2=homcoord.Pt(map(max,zip(self._corner2.xy,pt.xy)))
        return self

    def __repr__(self):
        return "BBox(%s,%s)"%(self._corner1,self._corner2)

    def __call__(self):
        """:return: list of flatten corners"""
        l=list(self._corner1.xy)
        l.extend(list(self._corner2.xy))
        return l

    def size(self):
        """:return: Pt with xy sizes"""
        return self._corner2-self._corner1

    def center(self):
        """:return: Pt center"""
        res=self._corner2+self._corner1
        return res/2

    def trans(self,trans):
        """
        :param trans: Xform
        :return: BBox = self transformed by trans
        """
        return BBox(trans(self._corner1),trans(self._corner2))


def cbox(c,r):
    """ bounding box of a circle
    :param c: Pt center
    :param r: float radius
    :return: BBox
    """
    __author__ = "Philippe Guglielmetti"
    __copyright__ = "Copyright 2013, Philippe Guglielmetti"
    __credits__ = ['http://effbot.org/imagingbook/imagedraw.htm']
    __license__ = "LGPL"

    rr=homcoord.Pt(r,r)
    return BBox(c+rr,c-rr)

def Trans(scale=1, offset=[0,0], rotation=0):
    __author__ = "Philippe Guglielmetti"
    __copyright__ = "Copyright 2013, Philippe Guglielmetti"
    __credits__ = ['http://effbot.org/imagingbook/imagedraw.htm']
    __license__ = "LGPL"
    res=homcoord.Xform([[scale,0,offset[0]],[0,scale,offset[1]],[0,0,1]])
    if rotation:
        res=homcoord.Xrotate(rotation*pi/180.)*res
    return res

class DXF:
    def __init__(self, file, layers=None, ignore=[]):
        """reads a .dxf file
        :param file: string path to .dxf file to read
        :param layers: list or dictionary of layers to handle. Empty = all layers
        :param ignore: list of strings of entity types to ignore
        """
        self.dxf=dxfgrabber.readfile(file)
        self.layers=layers
        self.ignore=ignore

    def entities(self,ent=None):
        """iterator over dxf or block entities"""
        if not ent:
            ent=self.dxf.entities
        for e in ent:
            if self.layers and e.layer not in self.layers:
                continue
            elif e.dxftype in self.ignore:
                continue
            else:
                yield e

    def points(self,ent=None)  :
        '''Lists of segments defining the drawing of the boundaries
            for LINES entities these are the extremal points of segments
            for CIRCLE entities these are extramal points of the sides of a polygon approximating the circle
            with 180 sides (180 is an arbitrary choice).
        '''
        segments_list=[]
        for e in self.entities():
            if e.dxftype=='LINE':
                segments_list.append(homcoord.segment(homcoord.Pt(e.start[:2]),homcoord.Pt(e.end[:2])))
                logging.warning('entity %s in dxf file'%e)

            elif e.dxftype == 'CIRCLE':

                c=homcoord.Pt(e.center[:2])
                rayon=e.radius
                the_angles=np.linspace(-np.pi,np.pi,180)
                logging.warning('entity %s in dxf file'%e)

                for angle,following_angle in itertools.izip(the_angles,the_angles[1:]):
                    Pt1=c+homcoord.Pt(rayon*np.cos(angle),rayon*np.sin(angle))
                    Pt2=c+homcoord.Pt(rayon*np.cos(following_angle),rayon*np.sin(following_angle))
                    segments_list.append(homcoord.Segment(Pt1,Pt2))
            else :
                logging.warning('Unknown entity %s in dxf file'%e)

        return segments_list


    def shapes(self, ent=None):
        '''
        Translates drawing into dictionary of shapely objects
        '''

        shapes_list=[]

        def homcoord_2_shapely(point):
            '''
            Convert homcoord point to shapely point
            Input: homcoord point datastructure
            Output: point converted in shapely data structure
            '''
            return shapelyPoint(point.x,point.y)

        for e in self.entities():
            if e.dxftype=='LINE':

                shapes_list.append(["LineString",loads("LineString",(homcoord_2_shapely(homcoord.Pt(e.start[:2])),homcoord_2_shapely(homcoord.Pt(e.end[:2]))))])

            elif e.dxftype == 'CIRCLE':
                c=homcoord.Pt(e.center[:2])
                rayon=e.radius
                the_angles=np.linspace(-np.pi,np.pi,180)

                pts_polygon=[]
                for angle in the_angles:
                    Pt1=c+homcoord.Pt(rayon*np.cos(angle),rayon*np.sin(angle))
                    pts_polygon.append((Pt1.x,Pt1.y))

                shapes_list.append(["polygon",shapelyPolygon(pts_polygon)])
            elif e.dxftype == 'POLYLINE':

                pts_polygon=[]
                for vertex in e.vertices:
                    point =homcoord.Pt(vertex.location[:2])
                    pts_polygon.append((point.x,point.y))
                shapes_list.append(["polyline",shapelyPolygon(pts_polygon)])

            else :
                logging.warning('Unknown entity %s in dxf shapes file'%e)

        return shapes_list

    # def draw_shapes(self):
        # '''
        # Draws drawing as shapely objects
        # '''
        # fig =plt.figure()
        # ax  =fig.add_subplot(111)
        # ax
        # for shape in self.shapes():
            # a  = Plot_shapely(shape[1], ax,'b', 0.1)
            # a.plot

        # fig.show()

    def bbox(self):
        """:return: :class:BBox dwg enclosing bounding box"""
        __author__ = "Philippe Guglielmetti"
        __copyright__ = "Copyright 2013, Philippe Guglielmetti"
        __credits__ = ['http://effbot.org/imagingbook/imagedraw.htm']
        __license__ = "LGPL"
        box=BBox()
        for e in self.entities():
            if e.dxftype=='LINE':
                box+=homcoord.Pt(e.start[:2])
                box+=homcoord.Pt(e.end[:2])
            elif e.dxftype == 'CIRCLE':
                box+=cbox(homcoord.Pt(e.center[:2]),e.radius)
            elif e.dxftype == 'ARC':
                c=homcoord.Pt(e.center[:2])
                a=e.endangle-e.startangle
                if a>0:
                    start=e.startangle
                else: #arc goes clockwise (step will be negative)
                    start=e.endangle
                n=rint(abs(a)/10.) # number of points each 10Â° approximately
                n=max(n,1)
                step=a/n #angle between 2 points, might be negative
                for i in range(n+1):
                    box+=c.radial(e.radius,radians(start+i*step))
            elif e.dxftype=='POLYLINE':
                for v in e.vertices:
                    box+=homcoord.Pt(v.location[:2])
            elif e.dxftype=='BLOCK':
                pass #TODO ...
            elif e.dxftype in ['TEXT','INSERT']:
                box+=homcoord.Pt(e.insert[:2])
            else:
                logging.warning('Unknown entity %s'%e)
        return box

    def _draw(self,draw,entities,trans,pen="black"):
        for e in entities:
            if e.dxftype=='LINE':
                b=list(trans(homcoord.Pt(e.start[:2])).xy)
                b.extend(list(trans(homcoord.Pt(e.end[:2])).xy))
                draw.line(b,fill=pen)
            elif e.dxftype=='CIRCLE':
                b=cbox(homcoord.Pt(e.center[:2]),e.radius)
                b=b.trans(trans)
                draw.ellipse(b(),outline=pen)
            elif e.dxftype=='ARC':
                c=homcoord.Pt(e.center[:2])
                b=cbox(c,e.radius)
                b=b.trans(trans)
                b=map(rint,b())
                startangle=degrees(trans.angle(radians(e.startangle)))
                endangle=degrees(trans.angle(radians(e.endangle)))
                startangle,endangle=endangle,startangle #swap start/end because of Y symmetry
                draw.arc(b,int(startangle),int(endangle),fill=pen)
            elif e.dxftype=='POLYLINE':
                b=[]
                for v in e.vertices:
                    b.extend(list(trans(homcoord.Pt(v.location[:2])).xy))
                draw.line(b,fill=pen)
            elif e.dxftype=='TEXT':
                h=e.height*trans.mag()
                pt=homcoord.Pt(e.insert[:2])+homcoord.Pt(0,e.height) #ACAD places texts by top left point...
                font=None
                try:
                    font = ImageFont.truetype("c:/windows/fonts/Courier New.ttf", rint(h))
                except:
                    pass
                if not font:
                    h=h*1.4 #magic factor ...
                    fh=[8,10,12,14,16,18,20,22,24,26,28,30,36,40,48,60]
                    i,h=min(enumerate(fh), key=lambda x: abs(x[1]-h)) #http://stackoverflow.com/questions/9706041/finding-index-of-an-item-closest-to-the-value-in-a-list-thats-not-entirely-sort
                    import os
                    path=os.path.realpath(__file__)
                    path=os.path.dirname(path)
                    font = ImageFont.load(path+'\\base_pil\\72\\Courier New_%s_72.pil'%h)
                draw.text(trans(pt).xy,e.text,font=font,fill=pen)
            elif e.dxftype=='INSERT':
                t2=Trans(1,e.insert,e.rotation).compose(trans)

                self._draw(draw,self.entities(self.dxf.blocks[e.name]._entities),t2,pen)
            elif e.dxftype=='BLOCK':
                pass # block definition is automatically stored in dxf.blocks dictionary
            else:
                logging.warning('Unknown entity %s'%e)

    def img(self,size=[256,256],back="white",pen="black",border=5,antialias=1):
        """:result: :class:`PIL:Image` rasterized image"""
        box=self.bbox()
        from math2 import product
        if not product(box.size().xy): # either x or y ==0
            return None

        s=map(operator.div,[float(x-border)*antialias if x else 1E9 for x in size ],box.size().xy)
        trans=Trans(scale=min(s))
        size=trans(box.size())+homcoord.Pt(2*antialias*border,2*antialias*border) #add borders as an offset
        offset=size/2-trans(box.center()) #offset in pixel coordinates
        trans=trans*Trans(offset=offset.xy)
        trans=trans*homcoord.Xscale(1,-1) #invert y axis
        trans=trans*homcoord.Xlate(0,size.y) #origin is lower left corner

        img = Image.new("RGB", map(rint,size.xy), back)
        self._draw(ImageDraw.Draw(img), self.entities(), trans, pen)
        if antialias>1:
            size=size/antialias
            img=img.resize(map(rint,size.xy), Image.ANTIALIAS)
        return img

    def image2pixelarray(self,size=[1000,1000],back="white",pen="black",border=100,antialias=1):
        """
        Conversion of the drawing in a greyscale 8 bits matrix

        Input
        ----------
        output image specifications

        Returns
        -------
        list
            A list of lists which make it simple to access the greyscale value by
            im[y][x]

        Credits
        -------
        http://stackoverflow.com/questions/13550376/pil-image-to-array-numpy-array-to-array-python
        """
        im=self.img(size=[1280,None],border=50)
        im = im.convert('L')
        (width, height) = im.size

        greyscale_map = np.fromiter(iter(im.getdata()), np.uint8)
        greyscale_map.resize(height, width)

        greyscale_map ^= 0xFF  # invert
        inverted_im = Image.fromarray(greyscale_map, mode='L')
        inverted_im.show()
        return greyscale_map


# if __name__ == '__main__':
    # dxf=DXF("./tests/example_renaud.dxf")
    # img=dxf.img(size=[1280,None],border=50)
    # dxf.draw_shapes()
    # #img.save('./out2.png')
    # #img.show()

def shapes_from_dxf(filename):
    dxf=DXF(filename)
    return dxf.shapes()
