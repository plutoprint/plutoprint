# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'PlutoPrint'
copyright = '2025, Samuel Ugochukwu'
author = 'Samuel Ugochukwu'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = []

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']



# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']

autodoc_member_order = "bysource"
autodoc_preserve_defaults = True

import os
import sys

BASE_DIR = os.path.dirname(os.path.realpath(__file__))

def exec_module(path):
    import importlib.machinery
    loader = importlib.machinery.SourceFileLoader("plutoprint", path)
    return loader.load_module()

sys.modules["plutoprint"] = exec_module(os.path.join(BASE_DIR, "..", "plutoprint", "__init__.pyi"))

extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.viewcode',
    'sphinx.ext.intersphinx'
]

intersphinx_mapping = {
    'python': ('https://docs.python.org/3/', None)
}
