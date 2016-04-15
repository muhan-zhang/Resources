#!/usr/bin/env python
# This Python file uses the following encoding: utf-8

import os
import sys
import re
import subprocess
import readline
import math
import numpy as np
from codecs import decode

input_bib = sys.argv[1]
def multigsub(subs,str):
    for k,v in subs.items():
        str = re.sub(k,v,str)
    return str

k = open("%s" %input_bib, "r").read()
output = open("edited_%s" %input_bib, "w+")

spec_char = {"à": "{\\`a}","è": "{\\`e}" ,"ì": "{\\`\\i}" , "ò": "{\\`o}" , "ù": "{\\`u}" , "ỳ": "{\\`y}" , "À": "{\\`A}","È": "{\\`E}" , "Ì": "{\\`\\I}" ,"Ò": "{\\`O}" ,"Ù": "{\\`U}" ,"Ỳ": "{\\`Y}" ,"á": "{\\'a}" ,"é": "{\\'e}" ,"í": "{\\'\\i}" ,"ó": "{\\'o}" ,"ú": "{\\'u}" ,"ý": "{\\'y}" ,"Á": "{\\'A}" ,"É": "{\\'E}" ,"Í": "{\\'\\I}" ,"Ó": "{\\'O}" ,"Ú": "{\\'U}" ,"Ý": "{\\'Y}" ,"â": "{\\^a}" , "ê": "{\\^e}" ,"î": "{\\^\\i}" ,"ô": "{\\^o}" ,"û": "{\\^u}" ,"ŷ": "{\\^y}" ,"Â": "{\\^A}" ,"Ê": "{\\^E}" ,"Î": "{\\^\\I}" ,"Ô": "{\\^O}" ,"Û": "{\\^U}" ,"Ŷ": "{\\^Y}" ,"ä": "{\\\"a}" ,"ë": "{\\\"e}" ,"ï": "{\\\"\\i}" ,"ö": "{\\\"o}" ,"ü": "{\\\"u}" ,"ÿ": "{\\\"y}" ,"Ä": "{\\\"A}" ,"Ë": "{\\\"E}" ,"Ï": "{\\\"\\I}" ,"Ö": "{\\\"O}" ,"Ü": "{\\\"U}" ,"Ÿ": "{\\\"Y}" ,"ç": "{\\c{c}" ,"Ç": "{\\c{C}" ,"œ": "{\\oe}" ,"Œ": "{\\OE}" ,"æ": "{\\ae}" ,"Æ": "{\\AE}" ,"å": "{\\aa}" ,"Å": "{\\AA}" ,"ø": "{\\o}" , "Ø": "{\\O}" ,"ß": "{\\ss}"}

output_text = multigsub(spec_char,k)
output.write(output_text)
