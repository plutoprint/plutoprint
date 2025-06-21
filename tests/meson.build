test_sources = [
    'test_book.py',
    'test_canvas.py',
    'test_enums.py',
    'test_pagemargins.py',
    'test_pagesize.py',
    'test_resourcedata.py',
    'test_resourcefetcher.py',
    'test_units.py',
]

fs = import('fs')
foreach source : test_sources
    fs.copyfile(source)
endforeach

test(
    'tests', python,
    workdir: meson.project_build_root(),
    args: ['-m', 'pytest']
)
