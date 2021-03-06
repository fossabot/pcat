crunchpp = find_program('crunch++', version: ['>= 1.0.0', '< 2.0.0'])
libcrunchpp = dependency('crunch++', version: ['>= 1.0.0', '< 2.0.0'])

commandExtra = ['-I../substrate', '-std=' + get_option('cpp_std')]
if get_option('b_coverage')
	commandExtra += ['--coverage']
endif
if get_option('debug')
	commandExtra += ['--debug']
endif
if cxx.get_id() != 'msvc'
	commandExtra += ['-z', 'defs']
endif

if sanitizer != 'none'
	commandExtra += ['-fsanitize=' + sanitizer]
endif

pcatTests = [
	'testFD', 'testConsole', 'testArgsTokenizer', 'testArgsParser'
]

testHelpers = static_library(
	'testHelpers',
	[
		'fd.cxx', 'console.cxx', '../substrate/impl/pty.cxx', 'tokenizer.cxx',
		'argsParser.cxx'
	],
	pic: true,
	dependencies: [libcrunchpp],
	include_directories: [include_directories('../src'), substrate],
	install: false,
	build_by_default: true
)

testObjectMap = {
	'testFD': {'test': ['fd.cxx']},
	'testConsole': {
		'test': ['console.cxx', '../substrate/impl/pty.cxx'],
		'pcat': ['substrate/impl/console.cxx']
	},
	'testArgsTokenizer': {'test': ['tokenizer.cxx'], 'pcat': ['src/args/tokenizer.cxx']},
	'testArgsParser': {
		'test': ['argsParser.cxx'],
		'pcat': [
			'src/args.cxx', 'src/args/tokenizer.cxx', 'src/args/types.cxx',
			'substrate/impl/console.cxx'
		]
	}
}

foreach test : pcatTests
	map = testObjectMap.get(test, {})
	pcatObjs = map.has_key('pcat') ? [pcat.extract_objects(map['pcat'])] : []
	testObjs = map.has_key('test') ? [testHelpers.extract_objects(map['test'])] : []
	testLibs = map.get('libs', [])
	custom_target(
		test,
		command: [
			crunchMake, '-s', '@INPUT@', '-o', '@OUTPUT@', '-I../src'
		] + commandExtra + testLibs,
		input: [test + '.cxx'] + pcatObjs + testObjs,
		output: test + '.so',
		build_by_default: true
	)

	test(
		test,
		crunchpp,
		args: [test],
		workdir: meson.current_build_dir()
	)
endforeach
