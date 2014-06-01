from distutils.core import setup, Extension
import os


# Locate the re2 module
_re2_prefixes = [
    '/usr',
    '/usr/local',
    '/opt/',
]

def find_prefix(package):

    for re2_prefix in _re2_prefixes:
        if os.path.exists(os.path.join(re2_prefix, "include", package)):
            break
    else:
        re2_prefix = ""

    return re2_prefix


# files = ['src/%s'%k for k in os.listdir('src') if k.endswith('.c') and 'gvc' not in k]

# r3_prefix = find_prefix("r3")
# pcre_prefix = '/user/local'
# import pdb; pdb.set_trace()


# files = []
module1 = Extension('pyr3',
    sources = ['pyr3.c'],
    # include_dirs=['include', '.'],
    # library_dirs=['/usr/lib', '/usr/local/lib'],
    libraries=["pcre", "r3"],
    include_dirs=['/usr/local/include/r3', '/usr/local/include', 'include', '.'],
    library_dirs=['/usr/local/lib'],
    runtime_library_dirs=['/usr/local/lib']
)

setup (name = 'PackageName',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [module1])
