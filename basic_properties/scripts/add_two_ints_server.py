#!/usr/bin/env python
# -*- coding: utf-8 -*-

from basic_properties.srv import *
import rospy

# the parmeters a, b, sum are given by the original defination of the service file "AddTwoInts"
def handle_add_two_ints(req):
    print "Return [%s + %s = %s]" % (req.a, req.b, (req.a + req.b))
    return AddTwoIntsResponse(req.a + req.b)

def add_two_ints_server():
    rospy.init_node('add_two_ints_server')
    s = rospy.Service('add_two_ints', AddTwoInts, handle_add_two_ints)
    print "Ready to add two ints."
    rospy.spin()


if __name__ == "__main__":
    add_two_ints_server()
