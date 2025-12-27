project('plutoprint', 'c', 'cpp', version: '0.15.0', license: 'MIT')

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
    cc = meson.get_compiler('c')

    plutobook_libdir = get_option('plutobook-libdir')
    plutobook_incdir = get_option('plutobook-incdir')

    plutobook_libdirs = []
    if plutobook_libdir != ''
        plutobook_libdirs += plutobook_libdir
    else
        plutobook_libdirs += ['/opt/homebrew/lib', '/usr/local/lib/x86_64-linux-gnu', '/usr/local/lib', '/usr/lib/x86_64-linux-gnu', '/usr/lib']
    endif

    plutobook_incdirs = []
    if plutobook_incdir != ''
        plutobook_incdirs += plutobook_incdir
    else
        plutobook_incdirs += ['/opt/homebrew/include/plutobook', '/usr/local/include/plutobook', '/usr/include/plutobook']
    endif

    plutobook_lib = cc.find_library('plutobook', dirs: plutobook_libdirs, required: plutobook_libdir != '')
    if not plutobook_lib.found()
        plutoprint_deps += dependency('plutobook', required: true)
    else
        foreach inc_dir : plutobook_incdirs
            if cc.has_header(inc_dir / 'plutobook.h', required: plutobook_incdir != '')
                plutoprint_deps += declare_dependency(dependencies: plutobook_lib, include_directories: inc_dir)
                break
            endif
        endforeach
    endif
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

subdir('fontconfig')

if get_option('tests')
    subdir('tests')
endif
