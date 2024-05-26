project('plutoprint', 'c', 'cpp', version: '0.0.1', license: 'MIT')

python = import('python').find_installation(pure: false)

deps = [python.dependency()]
if not get_option('sdist')
    deps += dependency('plutobook', required: true)
endif

sources = [
    'plutoprint/__init__.py'
]

python.install_sources(sources, subdir: 'plutoprint')
python.extension_module(
    '_plutoprint',
    'plutoprint/module.c',
    dependencies: deps,
    subdir: 'plutoprint',
    install: true
)
