
#!/usr/bin/env python

from distutils.core import setup
import os

packages = ['frontend' ]

# Allow the version to be replaced by the ant build script; but, if nothing
# replaces it (i.e. a developer does a command-line build), use 1.X.X
version='__VERSION__'
if version.find('__') == 0:
    version = '2.2.0'

setup(
        name='frontend',
        version=version,
        description='Python Classes for REDHAWK FRONTEND Interfaces',
        packages=packages,
        package_dir = { 'frontend' : 'python' }
    )
