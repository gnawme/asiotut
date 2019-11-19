project('asio-udpclient', 'cpp', default_options: ['cpp_std=gnu++17'])

add_project_arguments('-DASIO_STANDALONE', language: 'cpp')

src = [
    'AsioUDPClient.cpp',
]

threads = dependency('threads')

executable('asio-udpclient',
    src,
    dependencies: [threads],
)
