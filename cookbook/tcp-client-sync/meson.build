project('cookbook-tcpclient', 'cpp', default_options: ['cpp_std=gnu++17'])

add_project_arguments('-DASIO_STANDALONE', language: 'cpp')

src = [
    'CookbookTCPClient.cpp',
]

threads = dependency('threads')

executable('cookbook-tcpclient',
    src,
    dependencies: [threads],
)
