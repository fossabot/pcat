config = configuration_data()
config.set('AUTOGEN_HEADER', '/* THIS FILE IS AUTOGENERATED, DO NOT EDIT */')
config.set('VERSION', '@VERSION@')
config.set('COMPILER', cxx.get_id())
config.set('COMPILER_VERSION', cxx.version())
config.set('TARGET_SYS', target_machine.system())
config.set('TARGET_ARCH', target_machine.cpu())

versionHeaderSrc = configure_file(
	configuration: config,
	input: 'version.hxx.in',
	output: 'version.hxx.in'
)

versionHeader = vcs_tag(
	input: versionHeaderSrc,
	output: 'version.hxx',
	replace_string: '@VERSION@',
	fallback: meson.project_version()
)
