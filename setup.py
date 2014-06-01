from distutils.core import setup, Extension

module1 = Extension('r3',
                    sources = ['pyr3.c'],
                    include_dirs=['include', '.'])

setup (name = 'PackageName',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [module1])
