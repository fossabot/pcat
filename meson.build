project(
	'pcat',
	['cpp'],
	default_options: [
		'buildtype=release',
		'cpp_std=c++17',
		'warning_level=3',
		'b_ndebug=if-release',
		'b_lto=true',
		'strip=true'
	],
	license: 'GPL3+',
	version: '0.0.1',
	meson_version: '>= 0.52'
)

cxx = meson.get_compiler('cpp')
sanitizer = get_option('b_sanitize')
substrate = include_directories('substrate')
threading = dependency('threads')

fPIC = []
if cxx.has_argument('-fPIC')
	fPIC += ['-fPIC']
endif

pcatSrcs = [
	'src/pcat.cxx', 'src/chunking.cxx', 'src/args.cxx', 'src/args/types.cxx',
	'src/args/tokenizer.cxx', 'substrate/impl/console.cxx'
]

subdir('src')
pcat = executable(
	'pcat',
	pcatSrcs + [versionHeader],
	cpp_args: ['-D_GNU_SOURCE'] + fPIC,
	include_directories: [substrate, include_directories('src')],
	dependencies: [threading],
	gnu_symbol_visibility: 'inlineshidden',
	implicit_include_directories: false,
	install: true,
	pie: true
)

crunchMake = find_program('crunchMake', version: ['>= 1.0.0', '< 2.0.0'], required: false)
subdir('test', if_found: crunchMake)
