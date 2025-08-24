project('plutoprint', 'c', 'cpp', version: '0.6.0', license: 'MIT')

version_info = meson.project_version().split('.')
version_major = version_info[0].to_int()
version_minor = version_info[1].to_int()
version_micro = version_info[2].to_int()

add_project_arguments('-DPLUTOPRINT_VERSION_MAJOR=@0@'.format(version_major), language: ['cpp', 'c'])
add_project_arguments('-DPLUTOPRINT_VERSION_MINOR=@0@'.format(version_minor), language: ['cpp', 'c'])
add_project_arguments('-DPLUTOPRINT_VERSION_MICRO=@0@'.format(version_micro), language: ['cpp', 'c'])

python = import('python').find_installation(pure: false)

plutoprint_deps = [python.dependency()]
if not get_option('sdist')
    plutoprint_deps += dependency('plutobook', required: true)
endif

sources = [
    'plutoprint/__init__.py',
    'plutoprint/__init__.pyi',
    'plutoprint/__main__.py',
    'plutoprint/py.typed'
]

python.install_sources(sources, subdir: 'plutoprint')
python.extension_module(
    '_plutoprint',
    'plutoprint/module.c',
    dependencies: plutoprint_deps,
    subdir: 'plutoprint',
    install: true
)

if get_option('tests')
    subdir('tests')
endif
