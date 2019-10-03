#!/usr/bin/env python
import os
from distutils.core import setup, Extension
from mymodulegen import generate

try:
    os.mkdir("build")
except OSError:
    pass
module_fname = os.path.join("build", "twitter-binding.cc")
with open(module_fname, "wt") as file_:
    print("Generating file {}".format(module_fname))
    generate(file_)

mymodule = Extension('twitter',
                     sources = [module_fname, '../src/twitter.cc'],
                     include_dirs=['.'])

setup(name='PyBindGen-example',
      version="0.0",
      description='PyBindGen example',
      author='xxx',
      author_email='yyy@zz',
      ext_modules=[mymodule],
     )

