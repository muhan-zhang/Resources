#!/usr/bin/env python
# -*- coding: utf-8 -*-

import example2

print("\nSetting a to '10'\n")
a = example2.A(10);



#print(a.sqr())

print(repr(a))
print(str(a))

mylist = []
for i in range(10):
    mylist.append(example2.A(i))

print(" - ".join([str(a) for a in mylist]))

mylist[0].set(9)
print(" - ".join([str(a) for a in mylist]))


