project('TicTacToe', 'cpp', version: '0.1', default_options: ['cpp_std=c++17'])

gtk_dep = dependency('gtkmm-3.0', required: true)

TicTacToe = executable('TicTacToe', 'main.cpp', dependencies: gtk_dep)

install_targets = [TicTacToe]
