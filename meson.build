# -*- mode: meson -*-
# SPDX-License-Identifier: LGPL-2.1-or-later

# STANDALONE NOTE
# ===============
# This file has been derived from the official systemd meson.build file (snapshot shortly after v249 release),
# but has been reduced to the parts that were considered necessary to build
# systemd's EFI stub as a standalone component without intrusive source code changes.
# - Alexander Schreiber (schreiberstein) - 2021-10-08

project('systemd-efi-stub', 'c',
        version : '249',
        license : 'LGPLv2+',
        default_options: [
                'c_std=gnu99',
                'prefix=/usr',
                'sysconfdir=/etc',
                'localstatedir=/var',
                'warning_level=2',
        ],
        meson_version : '>= 0.53.2',
       )

conf = configuration_data()
conf.set('PROJECT_VERSION',    meson.project_version(),
         description : 'Numerical project version (used where a simple number is expected)')

# This is to be used instead of meson.source_root(), as the latter will return
# the wrong result when systemd is being built as a meson subproject
project_source_root = meson.current_source_dir()
project_build_root = meson.current_build_dir()
relative_source_path = run_command('realpath',
                                   '--relative-to=@0@'.format(project_build_root),
                                   project_source_root).stdout().strip()
conf.set_quoted('RELATIVE_SOURCE_PATH', relative_source_path)

# STANDALONE NOTE: Enable all tests globally (Only performs an undefined symbol check via shellscript anyway)
want_tests = 'true'

# STANDALONE NOTE: Install all efi files directory directly to [/], since we only need the file, not a directory structure!
rootprefixdir = '/'
prefixdir = rootprefixdir
bootlibdir = rootprefixdir

# STANDALONE NOTE: Set version to project version
vcs_data = configuration_data()
vcs_data.set('VCS_TAG', meson.project_version())
version_h = configure_file(configuration : vcs_data, input : 'src/version.h.in', output : 'version.h')
versiondep = declare_dependency(sources: version_h)


if get_option('efi')
        efi_arch = host_machine.cpu_family()

        if efi_arch == 'x86'
                EFI_MACHINE_TYPE_NAME = 'ia32'
                gnu_efi_arch = 'ia32'
        elif efi_arch == 'x86_64'
                EFI_MACHINE_TYPE_NAME = 'x64'
                gnu_efi_arch = 'x86_64'
        elif efi_arch == 'arm'
                EFI_MACHINE_TYPE_NAME = 'arm'
                gnu_efi_arch = 'arm'
        elif efi_arch == 'aarch64'
                EFI_MACHINE_TYPE_NAME = 'aa64'
                gnu_efi_arch = 'aarch64'
        elif efi_arch == 'riscv64'
                EFI_MACHINE_TYPE_NAME = 'riscv64'
                gnu_efi_arch = 'riscv64'
        else
                EFI_MACHINE_TYPE_NAME = ''
                gnu_efi_arch = ''
        endif

        have = true
        conf.set_quoted('EFI_MACHINE_TYPE_NAME', EFI_MACHINE_TYPE_NAME)
else
        have = false
endif

conf.set10('ENABLE_EFI', have)


cc = meson.get_compiler('c')
pkgconfig = import('pkgconfig')
test = find_program('test')
env = find_program('env')

# Those generate many false positives, and we do not want to change the code to
# avoid them.
basic_disabled_warnings = [
        '-Wno-format-signedness',
        '-Wno-missing-field-initializers',
        '-Wno-unused-parameter',
]

possible_common_cc_flags = [
        '-Wdate-time',
        '-Wendif-labels',
        '-Werror=format=2',
        '-Werror=implicit-function-declaration',
        '-Werror=incompatible-pointer-types',
        '-Werror=int-conversion',
        '-Werror=overflow',
        '-Werror=return-type',
        '-Werror=shift-count-overflow',
        '-Werror=shift-overflow=2',
        '-Werror=undef',
        '-Werror=unused-function',
        '-Wfloat-equal',
        '-Wimplicit-fallthrough=5',
        '-Winit-self',
        '-Wlogical-op',
        '-Wmissing-include-dirs',
        '-Wmissing-noreturn',
        '-Wnested-externs',
        '-Wold-style-definition',
        '-Wpointer-arith',
        '-Wredundant-decls',
        '-Wshadow',
        '-Wstrict-aliasing=2',
        '-Wstrict-prototypes',
        '-Wsuggest-attribute=noreturn',
        '-Wwrite-strings',

        # negative arguments are correctly detected starting with meson 0.46.
        '-Wno-error=#warnings',  # clang
        '-Wno-string-plus-int',  # clang
]

# Disable -Wmaybe-unitialized when compiling with -Os/-O1/-O3/etc. There are
# too many false positives with gcc >= 8. Effectively, we only test with -O0
# and -O2; this should be enough to catch most important cases without too much
# busywork. See https://github.com/systemd/systemd/pull/19226.
if cc.get_id() == 'gcc' and (not '02'.contains(get_option('optimization')) or
                             cc.version().version_compare('<10'))
        possible_common_cc_flags += '-Wno-maybe-uninitialized'
endif

# Disable -Wno-unused-result with gcc, see
# https://gcc.gnu.org/bugzilla/show_bug.cgi?id=66425.
if cc.get_id() == 'gcc'
        possible_common_cc_flags += '-Wno-unused-result'
endif

# --as-needed and --no-undefined are provided by meson by default,
# run 'meson configure' to see what is enabled
possible_link_flags = [
        '-Wl,-z,relro',
        '-Wl,-z,now',
        '-fstack-protector',
]
if cc.get_id() == 'clang'
        possible_common_cc_flags += [
                '-Wno-typedef-redefinition',
                '-Wno-gnu-variable-sized-type-not-at-end',
        ]
endif

possible_cc_flags = possible_common_cc_flags + [
        '-Werror=missing-declarations',
        '-Werror=missing-prototypes',
        '-fdiagnostics-show-option',
        '-ffast-math',
        '-fno-common',
        '-fno-strict-aliasing',
        '-fstack-protector',
        '-fstack-protector-strong',
        '-fvisibility=hidden',
        '--param=ssp-buffer-size=4',
]

if get_option('buildtype') != 'debug'
        possible_cc_flags += [
                '-ffunction-sections',
                '-fdata-sections',
        ]

        possible_link_flags += '-Wl,--gc-sections'
endif

add_project_arguments(cc.get_supported_arguments(basic_disabled_warnings), language : 'c')
add_project_arguments(cc.get_supported_arguments(possible_cc_flags), language : 'c')
add_project_link_arguments(cc.get_supported_link_arguments(possible_link_flags), language : 'c')

have = cc.has_argument('-Wzero-length-bounds')
conf.set10('HAVE_ZERO_LENGTH_BOUNDS', have)

# STANDALONE NOTE: Required source code files from [src/boot/efi], [src/fundamental], [src/version] have been moved to [src] - and systemd-boot has been removed
subdir('src')
