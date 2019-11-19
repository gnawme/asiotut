project('asio-combo-server', 'cpp', default_options: ['cpp_std=gnu++17'])

add_project_arguments('-DASIO_STANDALONE', language: 'cpp')

src = [
    'AsioComboServer.cpp',
]

ainclude = include_directories('../', '../tcp-server-async', '../udp-server-async')

threads = dependency('threads')

executable('asio-combo-server',
    src,
    include_directories: [ainclude],
    dependencies: [threads],
)
